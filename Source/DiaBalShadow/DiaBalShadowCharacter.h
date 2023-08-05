// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "Abilitys/DiaBalShadowAbilityComponent.h"
#include "Abilitys/DiaBalShadowAttributeSet.h"
#include "Abilitys/DiaBalShadowGameplayAbility.h"
#include "DiaBalShadowCharacter.generated.h"

UCLASS(Blueprintable)
class ADiaBalShadowCharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	ADiaBalShadowCharacter();

	// Called every frame.
	virtual void Tick(float DeltaSeconds) override;

	virtual void PossessedBy(AController* NewController) override;

	/** Returns TopDownCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetTopDownCameraComponent() const { return TopDownCameraComponent; }
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }

private:
	/** Top down camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* TopDownCameraComponent;

	/** Camera boom positioning the camera above the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

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

	/** Returns current health, will be 0 if dead */
	UFUNCTION(BlueprintCallable)
	virtual float GetHealth() const;
};

