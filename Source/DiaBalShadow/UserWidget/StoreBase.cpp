// Fill out your copyright notice in the Description page of Project Settings.


#include "StoreBase.h"

int32 UStoreBase::GetMaxBoxRow() const
{
    return MaxBoxRow;
}

int32 UStoreBase::GetMaxBoxColumn() const
{
    return MaxBoxColumn;
}

void UStoreBase::CreateCell(const FString& Path)
{
    Super::CreateCell(Path, MaxBoxRow, MaxBoxColumn);
}
