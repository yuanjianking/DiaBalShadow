// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../DiaBalShadowPrimaryDataAsset.h"
#include "../DiaBalShadowTypes.h"

class DIABALSHADOW_API UComplexItemInventory
{

public:
	UComplexItemInventory();

private:
	TMap<UDiaBalShadowPrimaryDataAsset*, FComplexData> ComplexItemData;

public:
	void AddItem(UDiaBalShadowPrimaryDataAsset* Item,int32 Count);

	void RemoveItem(UDiaBalShadowPrimaryDataAsset* Item, int32 Count);

	int32 GetCount(UDiaBalShadowPrimaryDataAsset* Item) const;

	int32 GetGroup(UDiaBalShadowPrimaryDataAsset* Item, int32 GroupSum) const;
};
