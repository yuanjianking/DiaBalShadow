// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "../DiaBalShadowPrimaryDataAsset.h"
#include "CellBase.generated.h"

/**
 * 
 */
UCLASS()
class DIABALSHADOW_API UCellBase : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Iyem)
	UDiaBalShadowPrimaryDataAsset* Item;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Iyem)
	int32 ItemCount;
};
