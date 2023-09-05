// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "DiaBalShadowCharacterBase.h"
#include "DiaBalShadowEnemyCharacter.generated.h"

UCLASS()
class DIABALSHADOW_API ADiaBalShadowEnemyCharacter : public ADiaBalShadowCharacterBase
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ADiaBalShadowEnemyCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void PossessedBy(AController* NewController) override;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
