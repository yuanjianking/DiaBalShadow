// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CellBase.h"
#include "EquipmentBase.generated.h"

/**
 * 
 */
UCLASS()
class DIABALSHADOW_API UEquipmentBase : public UUserWidget
{
	GENERATED_BODY()

private:
	int BoxCell[8][10] = { {0,0,0,0,0,0,0,0,0,0},
							{0,0,0,0,0,0,0,0,0,0},
							{0,0,0,0,0,0,0,0,0,0},
							{0,0,0,0,0,0,0,0,0,0},
							{0,0,0,0,0,0,0,0,0,0},
							{0,0,0,0,0,0,0,0,0,0},
							{0,0,0,0,0,0,0,0,0,0},
							{0,0,0,0,0,0,0,0,0,0} };
	UCellBase* BoxCellWidget[8][10] = { };
public:
	UFUNCTION(BlueprintCallable)
	UCellBase* GetCell(int32 X, int32 Y) const;
	UFUNCTION(BlueprintCallable)
	void AddCell(int32 X, int32 Y, UCellBase* Cell);
	
	UFUNCTION(BlueprintCallable)
	bool IsAvailableCell(int32 X, int32 Y, UDiaBalShadowPrimaryDataAsset* Item) ;

	UFUNCTION(BlueprintCallable)
	UCellBase* FindAvailableCell(UDiaBalShadowPrimaryDataAsset* Item, int32& OutX, int32& OutY) ;

	UFUNCTION(BlueprintCallable)
	void UnavailableCell(int32 X, int32 Y, int32 RowSpan, int32 ColumnSpan) ;

	UFUNCTION(BlueprintCallable)
	void AvailableCell(int32 X, int32 Y, int32 RowSpan, int32 ColumnSpan);
};
