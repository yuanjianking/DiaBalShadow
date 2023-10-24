// Fill out your copyright notice in the Description page of Project Settings.

#include "DiaBalShadowItemManagerComponent.h"
#include "../DiaBalShadow.h"
#include "../DiaBalShadowGameInstance.h"
#include "../DiaBalShadowSaveGame.h"
#include "../DiaBalShadowAssetManager.h"


// Sets default values for this component's properties
UDiaBalShadowItemManagerComponent::UDiaBalShadowItemManagerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UDiaBalShadowItemManagerComponent::BeginPlay()
{
	Super::BeginPlay();
	
}


// Called every frame
void UDiaBalShadowItemManagerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

int32 UDiaBalShadowItemManagerComponent::GetCount(UDiaBalShadowPrimaryDataAsset* Item) const
{
	if (Item->ItemType == UDiaBalShadowAssetManager::WeaponItemType || Item->ItemType == UDiaBalShadowAssetManager::SkillItemType)
		return 1;
	else
		return GetComplexCount(Item);
}

bool UDiaBalShadowItemManagerComponent::AddComplexItem(UDiaBalShadowPrimaryDataAsset* Item, int32 Count)
{
	bool bResult = true;
	int32 ItemCount = ComplexItem.GetCount(Item);
	if ((ItemCount % Item->MaxCount) != 0)
	{
		ComplexItem.AddItem(Item, Count);
	}
	else
	{		
		ComplexItem.AddItem(Item, Count);
	}
	return bResult;
}
 
int32 UDiaBalShadowItemManagerComponent::GetComplexCount(UDiaBalShadowPrimaryDataAsset* Item) const
{
	return ComplexItem.GetCount(Item);
}

int32 UDiaBalShadowItemManagerComponent::GetComplexGroup(UDiaBalShadowPrimaryDataAsset* Item) const
{
	return ComplexItem.GetGroup(Item, Item->MaxCount);
}

bool UDiaBalShadowItemManagerComponent::AddUniqueItem(FUniqueData Item, bool bAutoSlot)
{
	bool bResult = true;
	
	bResult = UniqueItem.AddUniqueItem(Item);
	
	if (bResult)
	{
		//自动添加武器插槽
		if (bAutoSlot) {
			//FillEmptySlotWithItem(NewItem);
		}
		//即时存档
		//SaveInventory();	
	}
	return bResult;
}

void UDiaBalShadowItemManagerComponent::GetUniqueItems(TArray<FUniqueData>& Items)
{
	UniqueItem.GetUniqueItems(Items);
}

void UDiaBalShadowItemManagerComponent::RemoveUniqueItem(FString GUID)
{
	if(UniqueItem.RemoveUniqueItem(GUID))
	{
		
	}
}
