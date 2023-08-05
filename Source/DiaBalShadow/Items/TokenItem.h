// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../DiaBalShadowPrimaryDataAsset.h"
#include "TokenItem.generated.h"

/**
 * 
 */
UCLASS()
class DIABALSHADOW_API UTokenItem : public UDiaBalShadowPrimaryDataAsset
{
	GENERATED_BODY()
	
public:
	UTokenItem()
	{
		ItemType = UDiaBalShadowAssetManager::TokenItemType;
	}
};
