// Fill out your copyright notice in the Description page of Project Settings.


#include "DiaBalShadowAttributeSet.h"
#include "Net/UnrealNetwork.h"
#include "GameplayEffect.h"
#include "GameplayEffectExtension.h"
#include "../DiaBalShadowCharacterBase.h"

void UDiaBalShadowAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UDiaBalShadowAttributeSet, Health);
}

void UDiaBalShadowAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	const FGameplayTagContainer& SourceTags = *Data.EffectSpec.CapturedSourceTags.GetAggregatedTags();

	float DeltaValue = 0;

	if (Data.EvaluatedData.ModifierOp == EGameplayModOp::Type::Additive)
	{
		// If this was additive, store the raw delta value to be passed along later
		DeltaValue = Data.EvaluatedData.Magnitude;
	}

	AActor* TargetActor = nullptr;
	AController* TargetController = nullptr;
	ADiaBalShadowCharacterBase* TargetCharacter = nullptr;
	if (Data.Target.AbilityActorInfo.IsValid() && Data.Target.AbilityActorInfo->AvatarActor.IsValid())
	{
		TargetActor = Data.Target.AbilityActorInfo->AvatarActor.Get();
		TargetController = Data.Target.AbilityActorInfo->PlayerController.Get();
		TargetCharacter = Cast<ADiaBalShadowCharacterBase>(TargetActor);
	}
	if (TargetCharacter)
	{
		// Call for all health changes
		TargetCharacter->HandleHealthChanged(DeltaValue, SourceTags);
	}
}

void UDiaBalShadowAttributeSet::OnRep_Health(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UDiaBalShadowAttributeSet, Health, OldValue);
}
