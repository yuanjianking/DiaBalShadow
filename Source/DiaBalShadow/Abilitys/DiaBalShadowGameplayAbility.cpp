// Fill out your copyright notice in the Description page of Project Settings.


#include "DiaBalShadowGameplayAbility.h"
#include "DiaBalShadowAbilityComponent.h"
#include "../DiaBalShadowCharacter.h"
void UDiaBalShadowGameplayAbility::ApplyEffectContainer(TSubclassOf<UGameplayEffect>  Effect)
{
	AActor* OwningActor = GetOwningActorFromActorInfo();
	ADiaBalShadowCharacter* OwningCharacter = Cast<ADiaBalShadowCharacter>(OwningActor);
	UDiaBalShadowAbilityComponent* AbilityComponent = Cast<UDiaBalShadowAbilityComponent> (OwningCharacter->GetAbilitySystemComponent());


	FGameplayEffectContextHandle EffectContext = AbilityComponent->MakeEffectContext();
	EffectContext.AddSourceObject(OwningCharacter);


	FGameplayEffectSpecHandle EffectSpecHandle = AbilityComponent->MakeOutgoingSpec(Effect,
		1, EffectContext);

	if (EffectSpecHandle.IsValid())
	{

		AbilityComponent->ApplyGameplayEffectSpecToTarget(*EffectSpecHandle.Data.Get(),
			AbilityComponent);
	}
}
