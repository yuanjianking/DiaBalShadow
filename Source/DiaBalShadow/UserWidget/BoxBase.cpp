// Fill out your copyright notice in the Description page of Project Settings.


#include "BoxBase.h"
#include "Components/GridPanel.h"
#include "Kismet/GameplayStatics.h"
#include "../DiaBalShadowAssetManager.h"
#include "../DiaBalShadowPlayerController.h"

UCellBase* UBoxBase::GetCell(int32 X, int32 Y) const
{
	return BoxCellWidget[X][Y];
}

void UBoxBase::AddCell(int32 X, int32 Y, UCellBase* Cell)
{
	Cell->SetAvailable(true);
	BoxCellWidget[X][Y] = Cell;	
}

bool UBoxBase::GetCellPostion(UCellBase* Cell, int32& OutX, int32& OutY)
{
	for (int X = 0; X < MaxBoxRow; X++)
	{
		for (int Y = 0; Y < MaxBoxColumn; Y++)
		{
			if(BoxCellWidget[X][Y] == Cell)
			{
				OutX = X;
				OutY = Y;
				return true;
			}
		}
	}
	return false;
}

bool UBoxBase::IsAvailableCell(int32 X, int32 Y, UDiaBalShadowPrimaryDataAsset* Item)
{
	int32 MaxX = X + Item->RowSpan;
	int32 MaxY = Y + Item->ColumnSpan;
	for (int32 M = X; M < MaxX; M++)
	{
		for (int32 N = Y; N < MaxY; N++)
		{
			if (BoxCellWidget[M][N] == nullptr)
				return false;
			if (!BoxCellWidget[M][N]->GetAvailable()) {

				if (BoxCellWidget[M][N]->Item == Item && (Item->ItemType == UDiaBalShadowAssetManager::PotionItemType ||
					Item->ItemType == UDiaBalShadowAssetManager::RunestoneItemType) && BoxCellWidget[M][N]->ItemCount < Item->MaxCount) {
					continue;
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
			BoxCellWidget[M][N]->SetAvailable(false);
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
			BoxCellWidget[M][N]->SetAvailable(true);
		}
	}
}

void UBoxBase::CreateCell(const FString& Path, const int32 MaxX, const int32 MaxY)
{
	for (int32 X = 0; X < MaxX; X++) 
	{
		for (int32 Y = 0; Y < MaxY; Y++)
		{
			UClass* CellClass = LoadClass<UCellBase>(nullptr, *Path);
			if(CellClass)
			{
				UCellBase* Cell = CreateWidget<UCellBase>(GetWorld(), CellClass);
				GridPanel->AddChildToGrid(Cell, X, Y);
				AddCell(X, Y, Cell);
				Cell->RemoveEvent.BindUObject(this, &ThisClass::ItemRemoved);
				Cell->UpDateEvent.BindUObject(this, &ThisClass::ItemUpdated);
				Cell->DropEvent.BindUObject(this, &ThisClass::ItemDroped);
				Cell->ThrowEvent.BindUObject(this, &ThisClass::ItemThrowed);
			}
		}
	}	
}

void UBoxBase::ItemRemoved(UCellBase* Cell, UDiaBalShadowPrimaryDataAsset* OldItem, FString OldGUID)
{
	int32 X = 0, Y = 0;
	if(GetCellPostion(Cell, X, Y))
		ShowCell(X, Y, Cell->Item);

	OnItemRemoved(OldItem, OldGUID);
}

void UBoxBase::ItemUpdated(UCellBase* Cell)
{
	OnItemUpdated(Cell->Item, Cell->GUID);
}

void UBoxBase::ItemDroped(UCellBase* Cell, UCellBase* OprationCell)
{	
	int32 X = 0, Y = 0;
	if(GetCellPostion(Cell, X, Y))
	{
		if (IsAvailableCell(X, Y, OprationCell->Item))
		{
			Cell->SetItem(OprationCell->Item, OprationCell->GUID, OprationCell->ItemCount);
			HideCell(X, Y, Cell->Item);

			if(GetCellPostion(OprationCell, X, Y))			
				ShowCell(X, Y, Cell->Item);
			OprationCell->Clear();

			OnItemDroped(Cell, OprationCell);
		}
		OprationCell->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
	}
}

void UBoxBase::ItemThrowed(UCellBase* Cell)
{
	//Cell->GUID;
	//Cell->ItemCount;
	//Cell->Item;
	int32 X = 0, Y = 0;
	if(GetCellPostion(Cell, X, Y))
		ShowCell(X, Y, Cell->Item);
	Cell->Clear();

}

void UBoxBase::AddItem(UDiaBalShadowPrimaryDataAsset* Item, FString GUID)
{
	if (GUID.IsEmpty())
	{
		if (Item)
		{
			int32 X = 0, Y = 0;
			UCellBase* Cell = FindAvailableCell(Item, X, Y);
			if (Cell)
			{
				Cell->SetItem(Item, GUID);
				HideCell(X, Y, Item);
			}
		}
	}
	else
	{
		APlayerController* FirstController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
		if(FirstController){
			ADiaBalShadowPlayerController* PlayerController = Cast<ADiaBalShadowPlayerController>(FirstController);
			if(PlayerController){
				FUniqueData UniqueData = PlayerController->itemManager->GetUniqueItem(GUID);
				int32 X = 0, Y = 0;
				UCellBase* Cell = FindAvailableCell(UniqueData.Item, X, Y);
				if (Cell)
				{
					Cell->SetItem(UniqueData.Item, GUID);
					HideCell(X, Y, UniqueData.Item);
				}
			}
		}
	}
}

void UBoxBase::ShowCell(int32 X, int32 Y, UDiaBalShadowPrimaryDataAsset* Item)
{
	if(Item)
	{
		int32 MaxX = X + Item->RowSpan;
		int32 MaxY = Y + Item->ColumnSpan;
		for (; X < MaxX; X++)
		{
			for (; Y < MaxY; Y++)
			{
				BoxCellWidget[X][Y]->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
				BoxCellWidget[X][Y]->SetAvailable(true);
			}
		}
	}
}

void UBoxBase::HideCell(int32 X, int32 Y, UDiaBalShadowPrimaryDataAsset* Item)
{
	if (Item)
	{
		int32 MaxX = X + Item->RowSpan;
		int32 MaxY = Y + Item->ColumnSpan;
		for (; X < MaxX; X++)
		{
			for (; Y < MaxY; Y++)
			{
				if (BoxCellWidget[X][Y]->Item == nullptr)
					BoxCellWidget[X][Y]->SetVisibility(ESlateVisibility::Hidden);
				BoxCellWidget[X][Y]->SetAvailable(false);
			}
		}
	}
}


