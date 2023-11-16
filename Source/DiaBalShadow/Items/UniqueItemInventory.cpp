// Fill out your copyright notice in the Description page of Project Settings.


#include "UniqueItemInventory.h"

UUniqueItemInventory::UUniqueItemInventory()
{
}



bool UUniqueItemInventory::AddUniqueItem(FUniqueData Item, bool bAutoSlot)
{
	FUniqueData* OldItem = UniqueItemData.Find(Item.GUID);
	if (OldItem == nullptr)
	{
		UniqueItemData.Add(Item.GUID, Item);
		return true;
	}
	else
	{
		return false;
	}
}

FUniqueData UUniqueItemInventory::GetUniqueItem(FString GUID)
{
	FUniqueData* OldItem = UniqueItemData.Find(GUID);
	if (OldItem)
		return *OldItem;
	else
		return FUniqueData();
}

void UUniqueItemInventory::GetUniqueItems(TArray<FUniqueData>& Items)
{
	for (const TPair<FString, FUniqueData>& Pair : UniqueItemData)
	{
		Items.Add(Pair.Value);
	}
}

bool UUniqueItemInventory::RemoveUniqueItem(FString GUID)
{
	FUniqueData* Weapon = UniqueItemData.Find(GUID);
	if (Weapon != nullptr)
	{
		UniqueItemData.Remove(GUID);
		return true;
	}
	else
	{
		return false;
	}
}
