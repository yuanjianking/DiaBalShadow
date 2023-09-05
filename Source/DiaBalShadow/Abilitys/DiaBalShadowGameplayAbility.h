// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "DiaBalShadowGameplayAbility.generated.h"

class UDiaBalShadowAbilityComponent;

/**
 * 
 */
UCLASS()
class DIABALSHADOW_API UDiaBalShadowGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()


public:

		/** Applies a gameplay effect container, by creating and then applying the spec */
		UFUNCTION(BlueprintCallable, Category = Ability)
		void ApplyEffectContainer(TSubclassOf<UGameplayEffect>  Effect, UAbilitySystemComponent* AbilityComponent);
	
};
