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
	DOREPLIFETIME(UDiaBalShadowAttributeSet, MaxHealth);
	DOREPLIFETIME(UDiaBalShadowAttributeSet, Mana);
	DOREPLIFETIME(UDiaBalShadowAttributeSet, MaxMana);

	DOREPLIFETIME(UDiaBalShadowAttributeSet, AttackPower);
	DOREPLIFETIME(UDiaBalShadowAttributeSet, MagicPower);
	DOREPLIFETIME(UDiaBalShadowAttributeSet, DefensePower);
	DOREPLIFETIME(UDiaBalShadowAttributeSet, MoveSpeed);
	DOREPLIFETIME(UDiaBalShadowAttributeSet, AttackSpeed);

	DOREPLIFETIME(UDiaBalShadowAttributeSet, Power);
	DOREPLIFETIME(UDiaBalShadowAttributeSet, Strength);
	DOREPLIFETIME(UDiaBalShadowAttributeSet, Intelligence);
	DOREPLIFETIME(UDiaBalShadowAttributeSet, Agility);
}

void UDiaBalShadowAttributeSet::OnRep_Health(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UDiaBalShadowAttributeSet, Health, OldValue);
}

void UDiaBalShadowAttributeSet::OnRep_MaxHealth(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UDiaBalShadowAttributeSet, MaxHealth, OldValue);
}

void UDiaBalShadowAttributeSet::OnRep_Mana(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UDiaBalShadowAttributeSet, Mana, OldValue);
}

void UDiaBalShadowAttributeSet::OnRep_MaxMana(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UDiaBalShadowAttributeSet, MaxMana, OldValue);
}

void UDiaBalShadowAttributeSet::OnRep_AttackPower(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UDiaBalShadowAttributeSet, AttackPower, OldValue);
}

void UDiaBalShadowAttributeSet::OnRep_MagicPower(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UDiaBalShadowAttributeSet, MagicPower, OldValue);
}

void UDiaBalShadowAttributeSet::OnRep_DefensePower(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UDiaBalShadowAttributeSet, DefensePower, OldValue);
}

void UDiaBalShadowAttributeSet::OnRep_MoveSpeed(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UDiaBalShadowAttributeSet, MoveSpeed, OldValue);
}

void UDiaBalShadowAttributeSet::OnRep_AttackSpeed(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UDiaBalShadowAttributeSet, AttackSpeed, OldValue);
}

void UDiaBalShadowAttributeSet::OnRep_Power(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UDiaBalShadowAttributeSet, Power, OldValue);
}

void UDiaBalShadowAttributeSet::OnRep_Strength(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UDiaBalShadowAttributeSet, Strength, OldValue);
}

void UDiaBalShadowAttributeSet::OnRep_Intelligence(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UDiaBalShadowAttributeSet, Intelligence, OldValue);
}

void UDiaBalShadowAttributeSet::OnRep_Agility(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UDiaBalShadowAttributeSet, Agility, OldValue);
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

	if (Data.EvaluatedData.Attribute == GetHealthAttribute())
	{
		// Handle other health changes such as from healing or direct modifiers
		// First clamp it
		//SetHealth(FMath::Clamp(GetHealth(), 0.0f, GetMaxHealth()));

		if (TargetCharacter)
		{
			// Call for all health changes
			TargetCharacter->HandleHealthChanged(DeltaValue, SourceTags);
		}
	}
	else if (Data.EvaluatedData.Attribute == GetManaAttribute())
	{
		// Clamp mana
		//SetMana(FMath::Clamp(GetMana(), 0.0f, GetMaxMana()));

		if (TargetCharacter)
		{
			// Call for all mana changes
			TargetCharacter->HandleManaChanged(DeltaValue, SourceTags);
		}
	}
}
