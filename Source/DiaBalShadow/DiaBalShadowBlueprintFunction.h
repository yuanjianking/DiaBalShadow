// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "DiaBalShadowBlueprintFunction.generated.h"

/**
 * 
 */
UCLASS()
class DIABALSHADOW_API UDiaBalShadowBlueprintFunction : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "DiaBalShadow")
	static void Printf(FString msg);


};
