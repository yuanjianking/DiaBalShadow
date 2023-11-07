// Fill out your copyright notice in the Description page of Project Settings.


#include "DiaBalShadowGameInstance.h"
#include "DiaBalShadowSaveGame.h"
#include "Kismet/GameplayStatics.h"


UDiaBalShadowSaveGame* UDiaBalShadowGameInstance::GetCurrentSaveGame()
{
    return CurrentSaveGame;
}

bool UDiaBalShadowGameInstance::SaveGame()
{
	if (bSavingEnabled)
	{
		if (bCurrentlySaving)
		{
			// Schedule another save to happen after current one finishes. We only queue one save
			bPendingSaveRequested = true;
			return true;
		}

		// Indicate that we're currently doing an async save
		bCurrentlySaving = true;

		// This goes off in the background
		UGameplayStatics::AsyncSaveGameToSlot(GetCurrentSaveGame(), SaveSlot, SaveUserIndex, FAsyncSaveGameToSlotDelegate::CreateUObject(this, &UDiaBalShadowGameInstance::HandleAsyncSave));
		return true;
	}
	return false;
}

bool UDiaBalShadowGameInstance::LoadGame()
{
	UDiaBalShadowSaveGame* LoadedSave = nullptr;

	if (UGameplayStatics::DoesSaveGameExist(SaveSlot, SaveUserIndex) && bSavingEnabled)
	{
		LoadedSave = Cast<UDiaBalShadowSaveGame>(UGameplayStatics::LoadGameFromSlot(SaveSlot, SaveUserIndex));
	}

	return HandleSaveGameLoaded(LoadedSave);
}

bool UDiaBalShadowGameInstance::HandleSaveGameLoaded(USaveGame* SaveGameObject)
{
	bool bLoaded = false;

	if (!bSavingEnabled)
	{
		// If saving is disabled, ignore passed in object
		SaveGameObject = nullptr;
	}

	// Replace current save, old object will GC out
	CurrentSaveGame = Cast<UDiaBalShadowSaveGame>(SaveGameObject);

	if (CurrentSaveGame)
	{
		// Make sure it has any newly added default inventory
		AddDefaultInventory(CurrentSaveGame, false);
		bLoaded = true;
	}
	else
	{
		// This creates it on demand
		CurrentSaveGame = Cast<UDiaBalShadowSaveGame>(UGameplayStatics::CreateSaveGameObject(UDiaBalShadowSaveGame::StaticClass()));

		AddDefaultInventory(CurrentSaveGame, true);
	}

	OnSaveGameLoaded.Broadcast(CurrentSaveGame);

	return bLoaded;
}

void UDiaBalShadowGameInstance::GetSaveSlotInfo(FString& SlotName, int32& UserIndex) const
{
	SlotName = SaveSlot;
	UserIndex = SaveUserIndex;
}

void UDiaBalShadowGameInstance::AddDefaultInventory(UDiaBalShadowSaveGame* SaveGame, bool bRemoveExtra)
{
	// If we want to remove extra, clear out the existing inventory
	if (bRemoveExtra)
	{
		SaveGame->InventoryData.Reset();
	}

	// Now add the default inventory, this only adds if not already in hte inventory
	for (const TPair<FPrimaryAssetId, FItemData>& Pair : DefaultInventory)
	{
		if (!SaveGame->InventoryData.Contains(Pair.Key))
		{
			SaveGame->InventoryData.Add(Pair.Key, Pair.Value);
		}
	}
}

bool UDiaBalShadowGameInstance::IsValidItemSlot(FItemSlot ItemSlot) const
{
	if (ItemSlot.IsValid())
	{
		const int32* FoundCount = ItemSlotsPerType.Find(ItemSlot.ItemType);

		if (FoundCount)
		{
			return ItemSlot.SlotNumber < *FoundCount;
		}
	}
	return false;
}

void UDiaBalShadowGameInstance::HandleAsyncSave(const FString& SlotName, const int32 UserIndex, bool bSuccess)
{
	bCurrentlySaving = false;

	if (bPendingSaveRequested)
	{
		// Start another save as we got a request while saving
		bPendingSaveRequested = false;
		SaveGame();
	}
}

bool UDiaBalShadowGameInstance::AddCharacter(FCharacterData Character)
{
	if (Character.PlayerName.IsEmpty())
		return false;

	for (const FCharacterData& Data : CharacterList)
	{
		if (Data.PlayerName.Equals(Character.PlayerName))
		{
			return false;
		}
	}
	
	CharacterList.Add(Character);
	DefaultCharacter = Character;
	return true;
}

FCharacterData UDiaBalShadowGameInstance::GetCharacter(FString PlayerName)
{
	for (const FCharacterData & Data : CharacterList)
	{
		if (Data.PlayerName.Equals(PlayerName))
		{
			return Data;
		}
	}
	return FCharacterData();	
}

FCharacterData UDiaBalShadowGameInstance::GetDefaultCharacter()
{
	return DefaultCharacter;
}

FCharacterData UDiaBalShadowGameInstance::RemoveCharacter(FString PlayerName)
{
	FCharacterData OldData;

	for (const FCharacterData& Data : CharacterList)
	{
		if (Data.PlayerName.Equals(PlayerName))
		{
			OldData = Data;
			break;
		}
	}	
	if(OldData != FCharacterData())
		CharacterList.Remove(OldData);

	if (CharacterList.IsEmpty())
	{
		DefaultCharacter = FCharacterData();
	}
	else
	{
		DefaultCharacter = CharacterList.Top();
	}

	return GetDefaultCharacter();
}

FCharacterData UDiaBalShadowGameInstance::SetDefaultCharacter(FString PlayerName)
{
	for (const FCharacterData& Data : CharacterList)
	{
		if (Data.PlayerName.Equals(PlayerName))
		{
			DefaultCharacter = Data;
			break;
		}
	}
	return GetDefaultCharacter();
}
