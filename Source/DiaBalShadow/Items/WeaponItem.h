// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../DiaBalShadowPrimaryDataAsset.h"
#include "WeaponItem.generated.h"

/**
 * 
 */
UCLASS()
class DIABALSHADOW_API UWeaponItem : public UDiaBalShadowPrimaryDataAsset
{
	GENERATED_BODY()
	
public:
	UWeaponItem()
	{
		ItemType = UDiaBalShadowAssetManager::WeaponItemType;
	}

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Weapon)
	float MaxDamage;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Weapon)
	float MinDamage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Weapon)
	float Speed;
};
