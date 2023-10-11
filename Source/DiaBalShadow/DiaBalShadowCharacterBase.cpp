// Fill out your copyright notice in the Description page of Project Settings.


#include "DiaBalShadowCharacterBase.h"

// Sets default values
ADiaBalShadowCharacterBase::ADiaBalShadowCharacterBase()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AbilitySystemComponent = CreateDefaultSubobject<UDiaBalShadowAbilityComponent>(TEXT("AbilitySystemComponent"));
	AbilitySystemComponent->SetIsReplicated(true);

	// Create the attribute set, this replicates by default
	AttributeSet = CreateDefaultSubobject<UDiaBalShadowAttributeSet>(TEXT("AttributeSet"));
}

// Called when the game starts or when spawned
void ADiaBalShadowCharacterBase::BeginPlay()
{
	Super::BeginPlay();

}

void ADiaBalShadowCharacterBase::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	// Initialize our abilities
	if (AbilitySystemComponent)
	{
		AbilitySystemComponent->InitAbilityActorInfo(this, this);
		AddStartupGameplayAbilities();
	}
}

// Called every frame
void ADiaBalShadowCharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ADiaBalShadowCharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ADiaBalShadowCharacterBase::AddStartupGameplayAbilities()
{
	// Grant abilities, but only on the server	
	for (TSubclassOf<UDiaBalShadowGameplayAbility>& StartupAbility : GameplayAbilities)
	{
		AbilitySystemComponent->GiveAbility(FGameplayAbilitySpec(StartupAbility, 1, INDEX_NONE, this));
	}

	// Now apply passives
	for (TSubclassOf<UGameplayEffect>& GameplayEffect : PassiveGameplayEffects)
	{
		FGameplayEffectContextHandle EffectContext = AbilitySystemComponent->MakeEffectContext();
		EffectContext.AddSourceObject(this);

		FGameplayEffectSpecHandle NewHandle = AbilitySystemComponent->MakeOutgoingSpec(GameplayEffect, 1, EffectContext);
		if (NewHandle.IsValid())
		{
			FActiveGameplayEffectHandle ActiveGEHandle = AbilitySystemComponent->ApplyGameplayEffectSpecToTarget(*NewHandle.Data.Get(), AbilitySystemComponent);
		}
	}
}

UAbilitySystemComponent* ADiaBalShadowCharacterBase::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

float ADiaBalShadowCharacterBase::GetHealth() const
{
	if (!AttributeSet)
		return 1.f;

	return AttributeSet->GetHealth();
}

float ADiaBalShadowCharacterBase::GetMaxHealth() const
{
	if (!AttributeSet)
		return 1.f;

	return AttributeSet->GetMaxHealth();
}


float ADiaBalShadowCharacterBase::GetMana() const
{
	if (!AttributeSet)
		return 1.f;

	return AttributeSet->GetMana();
}

float ADiaBalShadowCharacterBase::GetMaxMana() const
{
	if (!AttributeSet)
		return 1.f;

	return AttributeSet->GetMaxMana();
}

float ADiaBalShadowCharacterBase::GetAttackPower() const
{
	if (!AttributeSet)
		return 1.f;

	return AttributeSet->GetAttackPower();
}

float ADiaBalShadowCharacterBase::GetMagicPower() const
{
	if (!AttributeSet)
		return 1.f;

	return AttributeSet->GetMagicPower();
}

float ADiaBalShadowCharacterBase::GetDefensePower() const
{
	if (!AttributeSet)
		return 1.f;

	return AttributeSet->GetDefensePower();
}

float ADiaBalShadowCharacterBase::GetMoveSpeed() const
{
	if (!AttributeSet)
		return 1.f;

	return AttributeSet->GetMoveSpeed();
}

float ADiaBalShadowCharacterBase::GetAttackSpeed() const
{
	if (!AttributeSet)
		return 1.f;

	return AttributeSet->GetAttackSpeed();
}

float ADiaBalShadowCharacterBase::GetPower() const
{
	if (!AttributeSet)
		return 1.f;

	return AttributeSet->GetPower();
}

float ADiaBalShadowCharacterBase::GetStrength() const
{
	if (!AttributeSet)
		return 1.f;

	return AttributeSet->GetStrength();
}

float ADiaBalShadowCharacterBase::GetIntelligence() const
{
	if (!AttributeSet)
		return 1.f;

	return AttributeSet->GetIntelligence();
}

float ADiaBalShadowCharacterBase::GetAgility() const
{
	if (!AttributeSet)
		return 1.f;

	return AttributeSet->GetAgility();
}

void ADiaBalShadowCharacterBase::HandleHealthChanged(float DeltaValue, const FGameplayTagContainer& EventTags)
{
	OnHealthChanged(DeltaValue, EventTags);
}
void ADiaBalShadowCharacterBase::HandleManaChanged(float DeltaValue, const FGameplayTagContainer& EventTags)
{
	OnManaChanged(DeltaValue, EventTags);
}

