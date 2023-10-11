// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "Abilitys/DiaBalShadowAbilityComponent.h"
#include "Abilitys/DiaBalShadowAttributeSet.h"
#include "Abilitys/DiaBalShadowGameplayAbility.h"
#include "DiaBalShadowCharacterBase.generated.h"

UCLASS()
class DIABALSHADOW_API ADiaBalShadowCharacterBase : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ADiaBalShadowCharacterBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void PossessedBy(AController* NewController) override;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:

	/** The component used to handle ability system interactions */
	UPROPERTY()
	UDiaBalShadowAbilityComponent* AbilitySystemComponent;

	/** List of attributes modified by the ability system */
	UPROPERTY()
	UDiaBalShadowAttributeSet* AttributeSet;

	/** Abilities to grant to this character on creation. These will be activated by tag or event and are not bound to specific inputs */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Abilities)
	TArray<TSubclassOf<UDiaBalShadowGameplayAbility>> GameplayAbilities;

	/** Passive gameplay effects applied on creation */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Abilities)
	TArray<TSubclassOf<UGameplayEffect>> PassiveGameplayEffects;

public:
	/** Apply the startup gameplay abilities and effects */
	void AddStartupGameplayAbilities();

	// Implement IAbilitySystemInterface
	UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	UFUNCTION(BlueprintCallable)
	virtual float GetHealth() const;

	UFUNCTION(BlueprintCallable)
	virtual float GetMaxHealth() const;

	UFUNCTION(BlueprintCallable)
	virtual float GetMana() const;

	UFUNCTION(BlueprintCallable)
	virtual float GetMaxMana() const;

	UFUNCTION(BlueprintCallable)
	virtual float GetAttackPower() const;

	UFUNCTION(BlueprintCallable)
	virtual float GetMagicPower() const;

	UFUNCTION(BlueprintCallable)
	virtual float GetDefensePower() const;

	UFUNCTION(BlueprintCallable)
	virtual float GetMoveSpeed() const;

	UFUNCTION(BlueprintCallable)
	virtual float GetAttackSpeed() const;

	UFUNCTION(BlueprintCallable)
	virtual float GetPower() const;

	UFUNCTION(BlueprintCallable)
	virtual float GetStrength() const;

	UFUNCTION(BlueprintCallable)
	virtual float GetIntelligence() const;

	UFUNCTION(BlueprintCallable)
	virtual float GetAgility() const;

public:
	virtual void HandleHealthChanged(float DeltaValue, const struct FGameplayTagContainer& EventTags);
	UFUNCTION(BlueprintImplementableEvent)
	void OnHealthChanged(float DeltaValue, const struct FGameplayTagContainer& EventTags);

	virtual void HandleManaChanged(float DeltaValue, const struct FGameplayTagContainer& EventTags);
	UFUNCTION(BlueprintImplementableEvent)
	void OnManaChanged(float DeltaValue, const struct FGameplayTagContainer& EventTags);
};
