// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "../DiaBalShadowPrimaryDataAsset.h"
#include "../DiaBalShadowTypes.h"
#include "CellBase.generated.h"

DECLARE_DELEGATE_OneParam(ThrowEventDelegate, UCellBase*);
DECLARE_DELEGATE_TwoParams(DropTargetEventDelegate, UCellBase*, UCellBase*);
DECLARE_DELEGATE_OneParam(DropSourceEventDelegate, UCellBase*);
DECLARE_DELEGATE_ThreeParams(RemoveEventDelegate, UCellBase*, UDiaBalShadowPrimaryDataAsset*, FString);
DECLARE_DELEGATE_OneParam(UpDateEventDelegate, UCellBase*);

/**
 * 
 */
UCLASS()
class DIABALSHADOW_API UCellBase : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UImage* ImagePreview;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Item)
	UDiaBalShadowPrimaryDataAsset* Item;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Item)
	FString GUID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Item)
	int32 ItemCount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Cell)
	bool IsMoved;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Cell)
	UObject* DefaultResourceObject;

public:
	ThrowEventDelegate ThrowEvent;
	DropTargetEventDelegate DropTargetEvent;
	DropSourceEventDelegate DropSourceEvent;
	RemoveEventDelegate RemoveEvent;
	UpDateEventDelegate UpDateEvent;

public:
	UFUNCTION(BlueprintCallable, Category = Cell)
	void DragEnter(UCellBase * OperationCell);

	UFUNCTION(BlueprintCallable, Category = Cell)
	void DragLeave();

	UFUNCTION(BlueprintCallable, Category = Cell)
	void DragCancelled();

	UFUNCTION(BlueprintCallable, Category = Cell)
	bool DragDetected();

	UFUNCTION(BlueprintCallable, Category = Cell)
	void Drop(UCellBase* OperationCell);

	UFUNCTION(BlueprintCallable, Category = Cell)
	void AddItemCount();

	UFUNCTION(BlueprintCallable, Category = Cell)
	void RemoveItem();

	UFUNCTION(BlueprintCallable, Category = Cell)
	void UpdateImage();

	UFUNCTION(BlueprintCallable, Category = Slot)
	UObject* GetResourceObject() const;
	
	UFUNCTION(BlueprintCallable, Category = Slot)
	float RowSpan() const;

	UFUNCTION(BlueprintCallable, Category = Slot)
	float ColumnSpan() const;

	UFUNCTION(BlueprintCallable, Category = Slot)
	float RowSize() const;

	UFUNCTION(BlueprintCallable, Category = Slot)
	float ColumnSize() const;

private:
	bool IsAvailable;
public:
	bool SetItem(UDiaBalShadowPrimaryDataAsset* NewItem, FString NewGUID, int32 Count = 1);
	void Clear();
	void SetAvailable(bool NewAvailable);
	bool GetAvailable();

};
