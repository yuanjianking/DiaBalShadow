// Fill out your copyright notice in the Description page of Project Settings.


#include "DiaBalShadowEnemyCharacter.h"

// Sets default values
ADiaBalShadowEnemyCharacter::ADiaBalShadowEnemyCharacter()
{

}

// Called when the game starts or when spawned
void ADiaBalShadowEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void ADiaBalShadowEnemyCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
}

// Called every frame
void ADiaBalShadowEnemyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ADiaBalShadowEnemyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}
