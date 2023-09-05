// Fill out your copyright notice in the Description page of Project Settings.


#include "DiaBalShadowGameplayAbility.h"
#include "DiaBalShadowAbilityComponent.h"

void UDiaBalShadowGameplayAbility::ApplyEffectContainer(TSubclassOf<UGameplayEffect>  Effect, UAbilitySystemComponent* AbilityComponent)
{
	FGameplayEffectContextHandle EffectContext = AbilityComponent->MakeEffectContext();
	EffectContext.AddSourceObject(AbilityComponent->GetOwnerActor());


	FGameplayEffectSpecHandle EffectSpecHandle = AbilityComponent->MakeOutgoingSpec(Effect,
		1, EffectContext);

	if (EffectSpecHandle.IsValid())
	{

		AbilityComponent->ApplyGameplayEffectSpecToTarget(*EffectSpecHandle.Data.Get(),
			AbilityComponent);
	}
}
