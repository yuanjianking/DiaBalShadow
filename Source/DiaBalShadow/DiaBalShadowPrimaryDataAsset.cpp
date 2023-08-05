// Fill out your copyright notice in the Description page of Project Settings.


#include "DiaBalShadowPrimaryDataAsset.h"

FPrimaryAssetId UDiaBalShadowPrimaryDataAsset::GetPrimaryAssetId() const
{
	return FPrimaryAssetId(ItemType, GetFName());
}

bool UDiaBalShadowPrimaryDataAsset::IsConsumable() const
{
	if (MaxCount <= 0)
	{
		return true;
	}
	return false;
}

FString UDiaBalShadowPrimaryDataAsset::GetIdentifierString() const
{
	return GetPrimaryAssetId().ToString();
}

