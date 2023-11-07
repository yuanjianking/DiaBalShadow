// Fill out your copyright notice in the Description page of Project Settings.


#include "EquipmentBase.h"
#include "../DiaBalShadowAssetManager.h"

int32 UEquipmentBase::GetMaxBoxRow() const
{
    return MaxBoxRow;
}

int32 UEquipmentBase::GetMaxBoxColumn() const
{
    return MaxBoxColumn;
}

void UEquipmentBase::CreateCell(const FString& Path)
{
    Super::CreateCell(Path, MaxBoxRow, MaxBoxColumn);
    WeaponSlot->DropEvent.BindUObject(this, &ThisClass::WeaponDroped);
}

void UEquipmentBase::WeaponDroped(UCellBase* Cell, UCellBase* OprationCell)
{
    if (OprationCell->Item->ItemType == UDiaBalShadowAssetManager::WeaponItemType)
    {
		Cell->SetItem(OprationCell->Item, OprationCell->GUID, OprationCell->ItemCount);
        OnWeaponDroped(OprationCell->GUID);

		int32 X = 0, Y = 0;
		if(GetCellPostion(OprationCell, X, Y))
            ShowCell(X, Y, Cell->Item);
		OprationCell->Clear();
    }
    OprationCell->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
}
