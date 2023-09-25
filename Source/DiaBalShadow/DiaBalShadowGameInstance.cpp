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

bool UDiaBalShadowGameInstance::AddCharacter(FString Name, FCharacterData Character)
{
	if (CharacterList.Contains(Name))
	{
		return false;
	}
	else
	{
		CharacterList.Add(Name, Character);
		DefaultCharacter = Name;
		return true;
	}
}

FCharacterData UDiaBalShadowGameInstance::GetCharacter(FString Name)
{
	FCharacterData* Data = CharacterList.Find(Name);

	if (Data != nullptr)
	{
		return (*Data);
	}
	else
	{
		return FCharacterData();
	}
}

FCharacterData UDiaBalShadowGameInstance::GetDefaultCharacter()
{
	FCharacterData* Data = CharacterList.Find(DefaultCharacter);

	if (Data != nullptr)
	{
		return (*Data);
	}
	else
	{
		return FCharacterData();
	}
}

FCharacterData UDiaBalShadowGameInstance::RemoveCharacter(FString Name)
{
	FCharacterData * Data =CharacterList.Find(Name);
	if (Data != nullptr)
	{
		CharacterList.Remove(Name);
		TArray<FString> Keys;
		CharacterList.GetKeys(Keys);
		if (Keys.IsEmpty())
		{
			DefaultCharacter = TEXT("");
		}
		else
		{
			DefaultCharacter = *Keys.GetData();			
		}	
	}
	return GetDefaultCharacter();
}
