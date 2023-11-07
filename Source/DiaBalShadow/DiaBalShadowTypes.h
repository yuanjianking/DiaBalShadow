// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DiaBalShadowPrimaryDataAsset.h"
#include "DiaBalShadowTypes.generated.h"

USTRUCT(BlueprintType)
struct DIABALSHADOW_API FItemSlot
{
	GENERATED_BODY()

	FItemSlot()
	: SlotNumber(-1)
	{}

	FItemSlot(const FPrimaryAssetType& InItemType, int32 InSlotNumber)
		: ItemType(InItemType)
		, SlotNumber(InSlotNumber)
	{}

	/** The type of items that can go in this slot */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Item)
	FPrimaryAssetType ItemType;

	/** The number of this slot, 0 indexed */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Item)
	int32 SlotNumber;


	bool operator==(const FItemSlot& Other) const
	{
		return ItemType == Other.ItemType && SlotNumber == Other.SlotNumber;
	}
	bool operator!=(const FItemSlot& Other) const
	{
		return !(*this == Other);
	}

	/** Implemented so it can be used in Maps/Sets */
	friend inline uint32 GetTypeHash(const FItemSlot& Key)
	{
		uint32 Hash = 0;

		Hash = HashCombine(Hash, GetTypeHash(Key.ItemType));
		Hash = HashCombine(Hash, (uint32)Key.SlotNumber);
		return Hash;
	}

	/** Returns true if slot is valid */
	bool IsValid() const
	{
		return ItemType.IsValid() && SlotNumber >= 0;
	}
};

USTRUCT(BlueprintType)
struct DIABALSHADOW_API FItemData {
	GENERATED_BODY()

	FItemData()
	: ItemCount(1)
	, ItemLevel(1)
	{}

	FItemData(int32 InItemCount, int32 InItemLevel)
		: ItemCount(InItemCount)
		, ItemLevel(InItemLevel)
	{}

	/** The number of instances of this item in the inventory, can never be below 1 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Item)
	int32 ItemCount;

	/** The level of this item. This level is shared for all instances, can never be below 1 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Item)
	int32 ItemLevel;


	/** Equality operators */
	bool operator==(const FItemData& Other) const
	{
		return ItemCount == Other.ItemCount && ItemLevel == Other.ItemLevel;
	}
	bool operator!=(const FItemData& Other) const
	{
		return !(*this == Other);
	}

	/** Returns true if count is greater than 0 */
	bool IsValid() const
	{
		return ItemCount > 0;
	}

	/** Append an item data, this adds the count and overrides everything else */
	void UpdateItemData(const FItemData& Other, int32 MaxCount, int32 MaxLevel)
	{
		if (MaxCount <= 0)
		{
			MaxCount = MAX_int32;
		}

		if (MaxLevel <= 0)
		{
			MaxLevel = MAX_int32;
		}

		ItemCount = FMath::Clamp(ItemCount + Other.ItemCount, 1, MaxCount);
		ItemLevel = FMath::Clamp(Other.ItemLevel, 1, MaxLevel);
	}
};


USTRUCT(BlueprintType)
struct DIABALSHADOW_API FComplexData {
	GENERATED_BODY()

		FComplexData()
		: ItemCount(1)
	{}

	FComplexData(int32 InItemCount)
		: ItemCount(InItemCount)
	{}

	/** The number of instances of this item in the inventory, can never be below 1 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Potion)
	int32 ItemCount;
};

USTRUCT(BlueprintType)
struct DIABALSHADOW_API FUniqueData {
	GENERATED_BODY()

		FUniqueData()
	{}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Weapon)
	FString GUID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Weapon)
	UDiaBalShadowPrimaryDataAsset* Item;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Weapon)
	float Health;

	/** User-visible long description */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Item)
	FText Description;
};

USTRUCT(BlueprintType)
struct DIABALSHADOW_API FCharacterData {
	GENERATED_BODY()
	FCharacterData()
	{}
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Character)
	FString PlayerName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Character)
	FString HeroName;

	bool operator==(const FCharacterData& Other) const
	{
		return PlayerName == Other.PlayerName && HeroName == Other.HeroName;
	}
	bool operator!=(const FCharacterData& Other) const
	{
		return !(*this == Other);
	}
};
