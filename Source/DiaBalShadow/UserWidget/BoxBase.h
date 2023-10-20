// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CellBase.h"
#include "BoxBase.generated.h"

#define MaxBoxRow 10
#define MaxBoxColumn 10

/**
 * 
 */
UCLASS()
class DIABALSHADOW_API UBoxBase : public UUserWidget
{
	GENERATED_BODY()

protected:
	int32 BoxCell[MaxBoxRow][MaxBoxColumn] = { };
	UCellBase* BoxCellWidget[MaxBoxRow][MaxBoxRow] = { };

public:
	UFUNCTION(BlueprintCallable)
	UCellBase* GetCell(int32 X, int32 Y) const;
	UFUNCTION(BlueprintCallable)
	void AddCell(int32 X, int32 Y, UCellBase* Cell);

	UFUNCTION(BlueprintCallable)
	void GetCellPostion(UCellBase* Cell, int32& OutX, int32& OutY);

	UFUNCTION(BlueprintCallable)
	bool IsAvailableCell(int32 X, int32 Y, UDiaBalShadowPrimaryDataAsset* Item);

	UFUNCTION(BlueprintCallable)
	UCellBase* FindAvailableCell(UDiaBalShadowPrimaryDataAsset* Item, int32& OutX, int32& OutY);

	UFUNCTION(BlueprintCallable)
	void UnavailableCell(int32 X, int32 Y, int32 RowSpan, int32 ColumnSpan);

	UFUNCTION(BlueprintCallable)
	void AvailableCell(int32 X, int32 Y, int32 RowSpan, int32 ColumnSpan);
};
