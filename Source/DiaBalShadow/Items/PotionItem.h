// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../DiaBalShadowPrimaryDataAsset.h"
#include "PotionItem.generated.h"

/**
 * 
 */
UCLASS()
class DIABALSHADOW_API UPotionItem : public UDiaBalShadowPrimaryDataAsset
{
	GENERATED_BODY()
	
public:
	UPotionItem()
	{
		ItemType = UDiaBalShadowAssetManager::PotionItemType;
	}
};
