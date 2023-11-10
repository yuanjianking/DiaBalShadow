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
    WeaponSlot->DropTargetEvent.BindUObject(this, &ThisClass::WeaponTargetDroped);
    WeaponSlot->DropSourceEvent.BindUObject(this, &ThisClass::WeaponSourceDroped);
}

void UEquipmentBase::WeaponTargetDroped(UCellBase* Cell, UCellBase* OperationCell)
{
    if (OperationCell->Item->ItemType == UDiaBalShadowAssetManager::WeaponItemType)
    {
		Cell->SetItem(OperationCell->Item, OperationCell->GUID, OperationCell->ItemCount);
        OnWeaponDroped(OperationCell->GUID);

        OperationCell->DropSourceEvent.ExecuteIfBound(OperationCell);
    }
    OperationCell->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
}

void UEquipmentBase::WeaponSourceDroped(UCellBase* OperationCell)
{
    OperationCell->Clear();
}
