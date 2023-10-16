// Fill out your copyright notice in the Description page of Project Settings.


#include "DiaBalShadowBlueprintFunction.h"

const int32 UDiaBalShadowBlueprintFunction::Box[8][10] = {{0,0,0,0,0,0,0,0,0,0},
														{0,0,0,0,0,0,0,0,0,0},
														{0,0,0,0,0,0,0,0,0,0},
														{0,0,0,0,0,0,0,0,0,0},
														{0,0,0,0,0,0,0,0,0,0},
														{0,0,0,0,0,0,0,0,0,0},
														{0,0,0,0,0,0,0,0,0,0},
														{0,0,0,0,0,0,0,0,0,0}};

void UDiaBalShadowBlueprintFunction::Printf(FString msg)
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, msg);
	}
}

bool UDiaBalShadowBlueprintFunction::IsAvailable(int32 x, int32 y)
{
	int32 value = Box[x][y];
	if (value == 0)
		return true;
	else
		return false;
}

void UDiaBalShadowBlueprintFunction::UpdateBox(int32 x, int32 y, int32 Value)
{

}
