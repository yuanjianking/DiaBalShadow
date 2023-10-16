// Fill out your copyright notice in the Description page of Project Settings.


#include "ComplexItemInventory.h"

UComplexItemInventory::UComplexItemInventory()
{
}


void UComplexItemInventory::AddItem(UDiaBalShadowPrimaryDataAsset* Item, int32 Count)
{
	FComplexData* OldData = ComplexItemData.Find(Item);
	if (OldData == nullptr)
	{
		ComplexItemData.Add(Item, FComplexData());
	}
	else
	{
		OldData->ItemCount = OldData->ItemCount + Count;
		OldData->Item
		ComplexItemData.Add(Item, *OldData);
	}
}

void UComplexItemInventory::RemoveItem(UDiaBalShadowPrimaryDataAsset* Item,int32 Count)
{
	FComplexData* OldData = ComplexItemData.Find(Item);
	if (OldData != nullptr)
	{
		OldData->ItemCount = OldData->ItemCount - Count;
		if (OldData->ItemCount <= 0)
		{
			ComplexItemData.Remove(Item);
		}
		else
		{
			ComplexItemData.Add(Item, *OldData);
		}
	}
}

int32 UComplexItemInventory::GetCount(UDiaBalShadowPrimaryDataAsset* Item)
{
	int32 Count = 0;
	FComplexData* OldData = ComplexItemData.Find(Item);
	if(OldData != nullptr)
	{
		Count = OldData->ItemCount;
	}
	return Count;
}

int32 UComplexItemInventory::GetGroup(UDiaBalShadowPrimaryDataAsset* Item, int32 GroupSum)
{
	int32 Group = 0;
	FComplexData* OldData = ComplexItemData.Find(Item);
	if (OldData != nullptr)
	{
		Group = OldData->ItemCount / GroupSum + 1;
	}
	return Group;
}

FComplexData UComplexItemInventory::GetComplex(UDiaBalShadowPrimaryDataAsset* Item)
{
	FComplexData* Data = ComplexItemData.Find(Item);
	if (Data != nullptr)
	{
		return *Data;
	}
	return FComplexData();
}
