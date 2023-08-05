// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../DiaBalShadowPrimaryDataAsset.h"
#include "RunestoneItem.generated.h"

/**
 * 
 */
UCLASS()
class DIABALSHADOW_API URunestoneItem : public UDiaBalShadowPrimaryDataAsset
{
	GENERATED_BODY()

public:
	URunestoneItem()
	{
		ItemType = UDiaBalShadowAssetManager::RunestoneItemType;
	}
	
};
