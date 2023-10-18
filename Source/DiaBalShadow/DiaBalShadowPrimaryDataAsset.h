// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Styling/SlateBrush.h"
#include "DiaBalShadowAssetManager.h"
#include "DiaBalShadowPrimaryDataAsset.generated.h"

/**
 * 
 */
UCLASS(Abstract, BlueprintType)
class DIABALSHADOW_API UDiaBalShadowPrimaryDataAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	UDiaBalShadowPrimaryDataAsset() {}

public:
	/** Type of this item, set in native parent class */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Item)
	FPrimaryAssetType ItemType;

	/** User-visible short name */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Item)
	FText ItemName;

	/** User-visible long description */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Item)
	FText ItemDescription;

	/** Icon to display */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Item)
	FSlateBrush ItemIcon;

	/** Price in game */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Item)
	int32 Price;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Item)
	int32 PlaceHolder;

	/** Maximum level this item can be, <= 0 means infinite */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Item)
	int32 RowSpan;
	/** Maximum level this item can be, <= 0 means infinite */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Item)
	int32 ColumnSpan;

	/** Maximum number of instances that can be in inventory at once, <= 0 means infinite */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Max)
	int32 MaxCount;

	/** Maximum level this item can be, <= 0 means infinite */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Max)
	int32 MaxLevel;

	

public:
	/** Overridden to use saved type */
	virtual FPrimaryAssetId GetPrimaryAssetId() const override;

public:
	/** Returns the logical name, equivalent to the primary asset id */
	UFUNCTION(BlueprintCallable, Category = Item)
	FString GetIdentifierString() const;

	/** Returns if the item is consumable (MaxCount <= 0)*/
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = Max)
	bool IsConsumable() const;
	
};
