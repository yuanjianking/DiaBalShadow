// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/AssetManager.h"
#include "DiaBalShadowAssetManager.generated.h"


class UDiaBalShadowPrimaryDataAsset;

/**
 * 
 */
UCLASS()
class DIABALSHADOW_API UDiaBalShadowAssetManager : public UAssetManager
{
	GENERATED_BODY()

public:
	UDiaBalShadowAssetManager() {}

public:
	static const FPrimaryAssetType	PotionItemType;
	static const FPrimaryAssetType	SkillItemType;
	static const FPrimaryAssetType	TokenItemType;
	static const FPrimaryAssetType	WeaponItemType;
	static const FPrimaryAssetType	RunestoneItemType;

public:
	virtual void StartInitialLoading() override;
public:
	static UDiaBalShadowAssetManager& Get();
public:
	UDiaBalShadowPrimaryDataAsset* ForceLoadItem(const FPrimaryAssetId& PrimaryAssetId, bool bLogWarning = true);
};
