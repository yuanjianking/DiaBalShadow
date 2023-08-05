// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "DiaBalShadowTypes.h"
#include "DiaBalShadowGameInstance.generated.h"


class UDiaBalShadowSaveGame;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSaveGameLoaded, UDiaBalShadowSaveGame*, SaveGame);
/**
 * 
 */
UCLASS()
class DIABALSHADOW_API UDiaBalShadowGameInstance : public UGameInstance
{
	GENERATED_BODY()
	

public:
	UDiaBalShadowGameInstance()
		:SaveSlot(TEXT("TT"))
		, SaveUserIndex(0)
	{}

public:
	/** The slot name used for saving */
	UPROPERTY(BlueprintReadWrite, Category = Save)
	FString SaveSlot;

	/** The platform-specific user index */
	UPROPERTY(BlueprintReadWrite, Category = Save)
	int32 SaveUserIndex;

	/** List of inventory items to add to new players */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Inventory)
	TMap<FPrimaryAssetId, FItemData> DefaultInventory;

	/** Number of slots for each type of item */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Inventory)
	TMap<FPrimaryAssetType, int32> ItemSlotsPerType;

	UPROPERTY(BlueprintAssignable, Category = Inventory)
	FOnSaveGameLoaded OnSaveGameLoaded;

public:
	/** Returns the current save game, so it can be used to initialize state. Changes are not written until WriteSaveGame is called */
	UFUNCTION(BlueprintCallable, Category = Save)
	UDiaBalShadowSaveGame* GetCurrentSaveGame();

	UFUNCTION(BlueprintCallable, Category = Save)
	bool SaveGame();
	
	UFUNCTION(BlueprintCallable, Category = Save)
	bool LoadGame();

	/** Handle the final setup required after loading a USaveGame object using AsyncLoadGameFromSlot. Returns true if it loaded, false if it created one */
	UFUNCTION(BlueprintCallable, Category = Save)
	bool HandleSaveGameLoaded(USaveGame* SaveGameObject);

	/** Gets the save game slot and user index used for inventory saving, ready to pass to GameplayStatics save functions */
	UFUNCTION(BlueprintCallable, Category = Save)
	void GetSaveSlotInfo(FString& SlotName, int32& UserIndex) const;

	UFUNCTION(BlueprintCallable, Category = Inventory)
	void AddDefaultInventory(UDiaBalShadowSaveGame* SaveGame, bool bRemoveExtra = false);

	/** Returns true if this is a valid inventory slot */
	UFUNCTION(BlueprintCallable, Category = Inventory)
	bool IsValidItemSlot(FItemSlot ItemSlot) const;


protected:
	/** The current save game object */
	UPROPERTY()
	UDiaBalShadowSaveGame* CurrentSaveGame;

	/** Rather it will attempt to actually save to disk */
	UPROPERTY()
	bool bSavingEnabled;

	/** True if we are in the middle of doing a save */
	UPROPERTY()
	bool bCurrentlySaving;

	/** True if another save was requested during a save */
	UPROPERTY()
	bool bPendingSaveRequested;

	/** Called when the async save happens */
	virtual void HandleAsyncSave(const FString& SlotName, const int32 UserIndex, bool bSuccess);
};
