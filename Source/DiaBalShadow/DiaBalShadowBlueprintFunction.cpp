// Fill out your copyright notice in the Description page of Project Settings.


#include "DiaBalShadowBlueprintFunction.h"

void UDiaBalShadowBlueprintFunction::Printf(FString msg)
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, msg);
	}
}
