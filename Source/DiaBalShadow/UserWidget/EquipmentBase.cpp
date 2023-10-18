// Fill out your copyright notice in the Description page of Project Settings.


#include "EquipmentBase.h"
#include "../DiaBalShadowAssetManager.h"

UCellBase* UEquipmentBase::GetCell(int32 X, int32 Y) const
{
	return BoxCellWidget[X][Y];
}

void UEquipmentBase::AddCell(int32 X, int32 Y, UCellBase* Cell)
{
	BoxCellWidget[X][Y] = Cell;
}

bool UEquipmentBase::IsAvailableCell(int32 X, int32 Y, UDiaBalShadowPrimaryDataAsset* Item) 
{	
	int32 MaxX = X + Item->RowSpan;
	int32 MaxY = Y + Item->ColumnSpan;
	for (int32 M = X; M < MaxX; M++)
	{
		for (int32 N = Y; N < MaxY; N++)
		{
			if(BoxCell[M][N] == 1){
				
				if (BoxCellWidget[M][N]->Item == Item && (Item->ItemType == UDiaBalShadowAssetManager::PotionItemType ||
					Item->ItemType == UDiaBalShadowAssetManager::RunestoneItemType) && BoxCellWidget[M][N]->ItemCount < Item->MaxCount) {
					return true;
				}
				return false;
			}
		}
	}
	return true;
}

UCellBase* UEquipmentBase::FindAvailableCell(UDiaBalShadowPrimaryDataAsset* Item, int32& OutX, int32& OutY) 
{
	for (int X = 0; X < 8; X++)
	{
		for (int Y = 0; Y < 10; Y++)
		{
			if (IsAvailableCell(X, Y, Item))
			{
				OutX = X;
				OutY = Y;
				return BoxCellWidget[X][Y];
			}
		}
	}
	return nullptr;
}

void UEquipmentBase::UnavailableCell(int32 X, int32 Y, int32 RowSpan, int32 ColumnSpan)
{
	int32 MaxX = X + RowSpan;
	int32 MaxY = Y + ColumnSpan;
	for (int32 M = X; M < MaxX; M++)
	{
		for (int32 N = Y; N < MaxY; N++)
		{
			BoxCell[M][N] = 1;
		}
	}
}

void UEquipmentBase::AvailableCell(int32 X, int32 Y, int32 RowSpan, int32 ColumnSpan)
{
	int32 MaxX = X + RowSpan;
	int32 MaxY = Y + ColumnSpan;
	for (int32 M = X; M < MaxX; M++)
	{
		for (int32 N = Y; N < MaxY; N++)
		{
			BoxCell[M][N] = 0;
		}
	}
}
