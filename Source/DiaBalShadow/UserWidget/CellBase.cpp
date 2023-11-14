// Fill out your copyright notice in the Description page of Project Settings.


#include "CellBase.h"
#include "Components/GridSlot.h"
#include "Components/Image.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/LocalPlayer.h"
#include "../DiaBalShadowPlayerController.h"

void UCellBase::DragEnter(UCellBase* OperationCell)
{
	if(Item == nullptr && OperationCell != nullptr)
	{ 
		UGridSlot* GridSlot =  Cast<UGridSlot>(Slot);
		if(GridSlot)
		{
			GridSlot->SetRowSpan(OperationCell->Item->RowSpan);
			GridSlot->SetColumnSpan(OperationCell->Item->ColumnSpan);
		}
		IsMoved = true;
	}
}

void UCellBase::DragLeave()
{
	if (Item == nullptr)
	{
		UGridSlot* GridSlot = Cast<UGridSlot>(Slot);
		if(GridSlot)
		{
			GridSlot->SetRowSpan(0);
			GridSlot->SetRowSpan(0);
		}
		IsMoved = false;
	}
}

void UCellBase::DragCancelled()
{
	SetVisibility(ESlateVisibility::SelfHitTestInvisible);
	ThrowEvent.ExecuteIfBound(this);
	/*APlayerController* FirstController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if(FirstController)
	{
		ULocalPlayer* LocalPlayer = FirstController->GetLocalPlayer();
		if (LocalPlayer && LocalPlayer->ViewportClient)
		{
			FVector2D MousePosition;
			if (LocalPlayer->ViewportClient->GetMousePosition(MousePosition))
			{
				FVector2D ViewportSize;
				LocalPlayer->ViewportClient->GetViewportSize(ViewportSize);
				if ((ViewportSize.X / LocalPlayer->ViewportClient->GetDPIScale() - 500)< MousePosition.X)
				{
					ThrowEvent.ExecuteIfBound(this);
				}
			}
		}
	}*/
}

bool UCellBase::DragDetected()
{
	if (Item == nullptr)
		return false;

	SetVisibility(ESlateVisibility::Hidden);
	return true;;
}

void UCellBase::Drop(UCellBase* OperationCell)
{
	IsMoved = false;
	DropTargetEvent.ExecuteIfBound(this, OperationCell);
}

void UCellBase::AddItemCount()
{
	if (Item)
	{
		if(ItemCount < Item->MaxCount)
		{
			ItemCount++;
		}
	}
}

void UCellBase::RemoveItem()
{
	if (Item == nullptr)
		return;

	if (--ItemCount <= 0)
	{
		UDiaBalShadowPrimaryDataAsset* OldItem = Item;
		FString OldGUID = GUID;
		Clear();
		RemoveEvent.ExecuteIfBound(this, OldItem, OldGUID);
	}
	else
		UpDateEvent.ExecuteIfBound(this);

}

void UCellBase::UpdateImage()
{
	if (Item == nullptr)
	{
		ImagePreview->SetBrushResourceObject(DefaultResourceObject);
		UGridSlot* GridSlot = Cast<UGridSlot>(Slot);
		if (GridSlot)
		{
			GridSlot->SetRowSpan(0);
			GridSlot->SetRowSpan(0);
		}
	}
	else
	{
		ImagePreview->SetBrushResourceObject(Item->ItemIcon.GetResourceObject());
		UGridSlot* GridSlot = Cast<UGridSlot>(Slot);
		if(GridSlot)
		{
			GridSlot->SetRowSpan(Item->RowSpan);
			GridSlot->SetColumnSpan(Item->ColumnSpan);
		}
	}
}

UObject* UCellBase::GetResourceObject() const
{
	if (Item == nullptr)
		return DefaultResourceObject;
	else
		return Item->ItemIcon.GetResourceObject();
}

float UCellBase::RowSpan() const
{
	UGridSlot* GridSlot = Cast<UGridSlot>(Slot);
	if (GridSlot)
		return GridSlot->GetRowSpan();
	else if (Item)
		return Item->RowSpan;
	else
		return 0;

}

float UCellBase::ColumnSpan() const
{
	UGridSlot* GridSlot = Cast<UGridSlot>(Slot);
	if (GridSlot)
		return GridSlot->GetColumnSpan();
	else if (Item)
		return Item->ColumnSpan;
	else
		return 0;
}

float UCellBase::RowSize() const
{
	return RowSpan() * 50.0f;
}

float UCellBase::ColumnSize() const
{
	return ColumnSpan() * 50.0f;
}

bool UCellBase::SetItem(UDiaBalShadowPrimaryDataAsset* NewItem, FString NewGUID, int32 Count)
{
	Item = NewItem;
	GUID = NewGUID;
	ItemCount = ItemCount + Count;
	UpdateImage();
	return false;
}

void UCellBase::Clear()
{
	ItemCount = 0;
	Item = nullptr;
	GUID = TEXT("");
	UpdateImage();
}

void UCellBase::SetAvailable(bool NewAvailable)
{
	IsAvailable = NewAvailable;
}

bool UCellBase::GetAvailable()
{
	return IsAvailable;
}
