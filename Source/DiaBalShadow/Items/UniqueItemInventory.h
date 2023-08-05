// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../DiaBalShadowPrimaryDataAsset.h"
#include "../DiaBalShadowTypes.h"

class DIABALSHADOW_API UUniqueItemInventory
{
public:
	UUniqueItemInventory();

private:
	TMap<FString, FUniqueData> UniqueItemData;

public:
	bool AddUniqueItem(FUniqueData Item, bool bAutoSlot = true);

	FUniqueData GetUniqueItem(FString GUID);

	void GetUniqueItems(TArray<FUniqueData>& Items);

	bool RemoveUniqueItem(FString GUID);
};
