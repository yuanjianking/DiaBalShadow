// Fill out your copyright notice in the Description page of Project Settings.


#include "BoxBase.h"
#include "../DiaBalShadowAssetManager.h"

UCellBase* UBoxBase::GetCell(int32 X, int32 Y) const
{
	return BoxCellWidget[X][Y];
}

void UBoxBase::AddCell(int32 X, int32 Y, UCellBase* Cell)
{
	BoxCellWidget[X][Y] = Cell;
	BoxCell[X][Y] = 0;
}

void UBoxBase::GetCellPostion(UCellBase* Cell, int32& OutX, int32& OutY)
{

	for (int X = 0; X < MaxBoxRow; X++)
	{
		for (int Y = 0; Y < MaxBoxColumn; Y++)
		{
			if(BoxCellWidget[X][Y] == Cell)
			{
				OutX = X;
				OutY = Y;
				return;
			}
		}
	}
}

bool UBoxBase::IsAvailableCell(int32 X, int32 Y, UDiaBalShadowPrimaryDataAsset* Item)
{
	int32 MaxX = X + Item->RowSpan;
	int32 MaxY = Y + Item->ColumnSpan;
	for (int32 M = X; M < MaxX; M++)
	{
		for (int32 N = Y; N < MaxY; N++)
		{
			if (BoxCell[M][N] == 1) {

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

UCellBase* UBoxBase::FindAvailableCell(UDiaBalShadowPrimaryDataAsset* Item, int32& OutX, int32& OutY)
{
	for (int X = 0; X < MaxBoxRow; X++)
	{
		for (int Y = 0; Y < MaxBoxColumn; Y++)
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

void UBoxBase::UnavailableCell(int32 X, int32 Y, int32 RowSpan, int32 ColumnSpan)
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

void UBoxBase::AvailableCell(int32 X, int32 Y, int32 RowSpan, int32 ColumnSpan)
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
