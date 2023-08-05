// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "DiaBalShadowTypes.h"
#include "DiaBalShadowSaveGame.generated.h"

/**
 * 
 */
UCLASS()
class DIABALSHADOW_API UDiaBalShadowSaveGame : public USaveGame
{
	GENERATED_BODY()
	

public:
    UDiaBalShadowSaveGame()
    :PlayerName("TT")
    ,SaveSlotName("TT")
    ,UserIndex(0)
    ,Level(0)
    ,SavedDataVersion(1)
    {}

public:
    UPROPERTY(VisibleAnywhere, Category = Basic)
    FString PlayerName;

    UPROPERTY(VisibleAnywhere, Category = Basic)
    FString SaveSlotName;

    UPROPERTY(VisibleAnywhere, Category = Basic)
    uint32 UserIndex;

    UPROPERTY(VisibleAnywhere, Category = Level)
    uint32 Level;

public:
    /** Map of items to item data */
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = SaveGame)
    TMap<FPrimaryAssetId, FItemData> InventoryData;

    /** Map of slotted items */
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = SaveGame)
    TMap<FItemSlot, FPrimaryAssetId> SlottedItems;

    /** User's unique id */
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = SaveGame)
    FString UserId;


protected:
    /** Deprecated way of storing items, this is read in but not saved out */
    UPROPERTY()
    TArray<FPrimaryAssetId> InventoryItems_DEPRECATED;

    /** What LatestVersion was when the archive was saved */
    UPROPERTY()
    int32 SavedDataVersion;

public:
    /** Overridden to allow version fixups */
    virtual void Serialize(FArchive& Ar) override;

};
