// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../DiaBalShadowPrimaryDataAsset.h"
#include "SkillItem.generated.h"

/**
 * 
 */
UCLASS()
class DIABALSHADOW_API USkillItem : public UDiaBalShadowPrimaryDataAsset
{
	GENERATED_BODY()
	
public:
	USkillItem()
	{
		ItemType = UDiaBalShadowAssetManager::SkillItemType;
	}
};
