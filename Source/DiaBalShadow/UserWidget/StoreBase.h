// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CellBase.h"
#include "BoxBase.h"
#include "StoreBase.generated.h"

#ifdef MaxBoxRow
#undef MaxBoxRow
#endif // MaxBoxRow
#ifdef MaxBoxColumn
#undef MaxBoxColumn
#endif // MaxBoxColumn

#define MaxBoxRow 10
#define MaxBoxColumn 10

/**
 * 
 */
UCLASS()
class DIABALSHADOW_API UStoreBase : public UBoxBase
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable)
	int32  GetMaxBoxRow() const;

	UFUNCTION(BlueprintCallable)
	int32  GetMaxBoxColumn() const;

	UFUNCTION(BlueprintCallable)
	void CreateCell(const FString& Path);
};
