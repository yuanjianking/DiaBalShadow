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

public:
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UGridPanel* GridPanel;


protected:
	UCellBase* BoxCellWidget[MaxBoxRow][MaxBoxRow] = { };

public:
	UCellBase* GetCell(int32 X, int32 Y) const;
	void AddCell(int32 X, int32 Y, UCellBase* Cell);
	bool GetCellPostion(UCellBase* Cell, int32& OutX, int32& OutY);
	bool IsAvailableCell(int32 X, int32 Y, UDiaBalShadowPrimaryDataAsset* Item);
	UCellBase* FindAvailableCell(UDiaBalShadowPrimaryDataAsset* Item, int32& OutX, int32& OutY);
	void UnavailableCell(int32 X, int32 Y, int32 RowSpan, int32 ColumnSpan);
	void AvailableCell(int32 X, int32 Y, int32 RowSpan, int32 ColumnSpan);

protected:
	void CreateCell(const FString& Path, const int32 MaxX, const int32 MaxY);

protected:
	void ShowCell(int32 X, int32 Y, UDiaBalShadowPrimaryDataAsset* Item);
	void HideCell(int32 X, int32 Y, UDiaBalShadowPrimaryDataAsset* Item);

private:
	void ItemRemoved(UCellBase* Cell, UDiaBalShadowPrimaryDataAsset* OldItem, FString OldGUID);
	void ItemUpdated(UCellBase* Cell);
	void ItemDropedTarget(UCellBase* Cell, UCellBase* OperationCell);
	void ItemDropedSource(UCellBase* OperationCell);
	void ItemThrowed(UCellBase* Cell);

public:
	UFUNCTION(BlueprintImplementableEvent)
	void OnItemRemoved(const UDiaBalShadowPrimaryDataAsset* Item, const FString& OldGUID);

	UFUNCTION(BlueprintImplementableEvent)
	void OnItemUpdated(const UDiaBalShadowPrimaryDataAsset* Item, const FString& OldGUID);

	UFUNCTION(BlueprintImplementableEvent)
	void OnItemDropedTarget(const UCellBase* Cell, const UCellBase* OprationCell);

	UFUNCTION(BlueprintImplementableEvent)
	void OnItemDropedSource(const UCellBase* OprationCell);

	UFUNCTION(BlueprintImplementableEvent)
	void OnItemThrowed(const UCellBase* Cell);

public:
	UFUNCTION(BlueprintCallable, Category = Item)
	void AddItem(UDiaBalShadowPrimaryDataAsset* Item, FString GUID = TEXT(""));


};
