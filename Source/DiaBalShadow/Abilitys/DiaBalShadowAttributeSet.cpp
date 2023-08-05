// Fill out your copyright notice in the Description page of Project Settings.


#include "DiaBalShadowAttributeSet.h"
#include "Net/UnrealNetwork.h"

void UDiaBalShadowAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UDiaBalShadowAttributeSet, Health);
}

void UDiaBalShadowAttributeSet::OnRep_Health(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UDiaBalShadowAttributeSet, Health, OldValue);
}
