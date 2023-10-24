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

int32 UComplexItemInventory::GetCount(UDiaBalShadowPrimaryDataAsset* Item) const
{
	int32 Count = 0;
	for (const TPair<UDiaBalShadowPrimaryDataAsset*, FComplexData>& Pair : ComplexItemData)
	{		
		if (Pair.Key == Item)
		{
			Count = Pair.Value.ItemCount;
			break;
		}
	}
	return Count;
}

int32 UComplexItemInventory::GetGroup(UDiaBalShadowPrimaryDataAsset* Item, int32 GroupSum) const
{
	int32 Group = 0;
	for (const TPair<UDiaBalShadowPrimaryDataAsset*, FComplexData>& Pair : ComplexItemData)
	{
		if (Pair.Key == Item)
		{
			Group = Pair.Value.ItemCount / GroupSum + 1;
			break;
		}
	}
	return Group;
}
