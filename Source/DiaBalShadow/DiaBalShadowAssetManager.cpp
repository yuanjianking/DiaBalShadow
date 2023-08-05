// Fill out your copyright notice in the Description page of Project Settings.


#include "DiaBalShadowAssetManager.h"
#include "DiaBalShadow.h"
#include "DiaBalShadowPrimaryDataAsset.h"
#include "AbilitySystemGlobals.h"

const FPrimaryAssetType	UDiaBalShadowAssetManager::PotionItemType = TEXT("Potion");
const FPrimaryAssetType	UDiaBalShadowAssetManager::SkillItemType = TEXT("Skill");
const FPrimaryAssetType	UDiaBalShadowAssetManager::TokenItemType = TEXT("Token");
const FPrimaryAssetType	UDiaBalShadowAssetManager::WeaponItemType = TEXT("Weapon");
const FPrimaryAssetType	UDiaBalShadowAssetManager::RunestoneItemType = TEXT("Runestone");

void UDiaBalShadowAssetManager::StartInitialLoading()
{
	Super::StartInitialLoading();

	UAbilitySystemGlobals::Get().InitGlobalData();
}

UDiaBalShadowAssetManager& UDiaBalShadowAssetManager::Get()
{

	UDiaBalShadowAssetManager* This = Cast<UDiaBalShadowAssetManager>(GEngine->AssetManager);

	if (This)
	{
		return *This;
	}
	else
	{
		return *NewObject<UDiaBalShadowAssetManager>(); // never calls this
	}
}

UDiaBalShadowPrimaryDataAsset* UDiaBalShadowAssetManager::ForceLoadItem(const FPrimaryAssetId& PrimaryAssetId, bool bLogWarning)
{
	FSoftObjectPath ItemPath = GetPrimaryAssetPath(PrimaryAssetId);

	// This does a synchronous load and may hitch
	UDiaBalShadowPrimaryDataAsset* LoadedItem = Cast<UDiaBalShadowPrimaryDataAsset>(ItemPath.TryLoad());

	if (bLogWarning && LoadedItem == nullptr)
	{
		UE_LOG(LogDiaBalShadow, Warning, TEXT("Failed to load item for identifier %s!"), *PrimaryAssetId.ToString());
	}

	return LoadedItem;
}
