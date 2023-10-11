// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "DiaBalShadowAttributeSet.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)


/**
 * 
 */
UCLASS()
class DIABALSHADOW_API UDiaBalShadowAttributeSet : public UAttributeSet
{
	GENERATED_BODY()
public:
	/** Current Health, when 0 we expect owner to die. Capped by MaxHealth */
	UPROPERTY(BlueprintReadOnly, Category = "Health", ReplicatedUsing = OnRep_Health)
	FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS(UDiaBalShadowAttributeSet, Health)

	/** Current MaxHealth, when 0 we expect owner to die. Capped by MaxHealth */
	UPROPERTY(BlueprintReadOnly, Category = "Health", ReplicatedUsing = OnRep_MaxHealth)
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(UDiaBalShadowAttributeSet, MaxHealth)

	/** Current Mana, when 0 we expect owner to die. Capped by MaxMana */
	UPROPERTY(BlueprintReadOnly, Category = "Mana", ReplicatedUsing = OnRep_Mana)
	FGameplayAttributeData Mana;
	ATTRIBUTE_ACCESSORS(UDiaBalShadowAttributeSet, Mana)

	/** Current MaxMana, when 0 we expect owner to die. Capped by MaxMana */
	UPROPERTY(BlueprintReadOnly, Category = "Mana", ReplicatedUsing = OnRep_MaxMana)
	FGameplayAttributeData MaxMana;
	ATTRIBUTE_ACCESSORS(UDiaBalShadowAttributeSet, MaxMana)

	UPROPERTY(BlueprintReadOnly, Category = "Damage", ReplicatedUsing = OnRep_AttackPower)
	FGameplayAttributeData AttackPower;
	ATTRIBUTE_ACCESSORS(UDiaBalShadowAttributeSet, AttackPower)

	UPROPERTY(BlueprintReadOnly, Category = "Damage", ReplicatedUsing = OnRep_MagicPower)
	FGameplayAttributeData MagicPower;
	ATTRIBUTE_ACCESSORS(UDiaBalShadowAttributeSet, MagicPower)

	UPROPERTY(BlueprintReadOnly, Category = "Damage", ReplicatedUsing = OnRep_DefensePower)
	FGameplayAttributeData DefensePower;
	ATTRIBUTE_ACCESSORS(UDiaBalShadowAttributeSet, DefensePower)

	UPROPERTY(BlueprintReadOnly, Category = "Damage", ReplicatedUsing = OnRep_MoveSpeed)
	FGameplayAttributeData MoveSpeed;
	ATTRIBUTE_ACCESSORS(UDiaBalShadowAttributeSet, MoveSpeed)

	UPROPERTY(BlueprintReadOnly, Category = "Damage", ReplicatedUsing = OnRep_AttackSpeed)
	FGameplayAttributeData AttackSpeed;
	ATTRIBUTE_ACCESSORS(UDiaBalShadowAttributeSet, AttackSpeed)

	UPROPERTY(BlueprintReadOnly, Category = "Body", ReplicatedUsing = OnRep_Power)
	FGameplayAttributeData Power;
	ATTRIBUTE_ACCESSORS(UDiaBalShadowAttributeSet, Power)

	UPROPERTY(BlueprintReadOnly, Category = "Body", ReplicatedUsing = OnRep_Strength)
	FGameplayAttributeData Strength;
	ATTRIBUTE_ACCESSORS(UDiaBalShadowAttributeSet, Strength)

	UPROPERTY(BlueprintReadOnly, Category = "Body", ReplicatedUsing = OnRep_Intelligence)
	FGameplayAttributeData Intelligence;
	ATTRIBUTE_ACCESSORS(UDiaBalShadowAttributeSet, Intelligence)

	UPROPERTY(BlueprintReadOnly, Category = "Body", ReplicatedUsing = OnRep_Agility)
	FGameplayAttributeData Agility;
	ATTRIBUTE_ACCESSORS(UDiaBalShadowAttributeSet, Agility)

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;
protected:

	// These OnRep functions exist to make sure that the ability system internal representations are synchronized properly during replication
	UFUNCTION()
	virtual void OnRep_Health(const FGameplayAttributeData& OldValue);

	UFUNCTION()
	virtual void OnRep_MaxHealth(const FGameplayAttributeData& OldValue);

	UFUNCTION()
	virtual void OnRep_Mana(const FGameplayAttributeData& OldValue);

	UFUNCTION()
	virtual void OnRep_MaxMana(const FGameplayAttributeData& OldValue);

	UFUNCTION()
	virtual void OnRep_AttackPower(const FGameplayAttributeData& OldValue);

	UFUNCTION()
	virtual void OnRep_MagicPower(const FGameplayAttributeData& OldValue);

	UFUNCTION()
	virtual void OnRep_DefensePower(const FGameplayAttributeData& OldValue);

	UFUNCTION()
	virtual void OnRep_MoveSpeed(const FGameplayAttributeData& OldValue);

	UFUNCTION()
	virtual void OnRep_AttackSpeed(const FGameplayAttributeData& OldValue);

	UFUNCTION()
	virtual void OnRep_Power(const FGameplayAttributeData& OldValue);

	UFUNCTION()
	virtual void OnRep_Strength(const FGameplayAttributeData& OldValue);


	UFUNCTION()
	virtual void OnRep_Intelligence(const FGameplayAttributeData& OldValue);

	UFUNCTION()
	virtual void OnRep_Agility(const FGameplayAttributeData& OldValue);
};
