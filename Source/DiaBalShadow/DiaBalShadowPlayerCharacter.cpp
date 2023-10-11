// Copyright Epic Games, Inc. All Rights Reserved.

#include "DiaBalShadowPlayerCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Net/UnrealNetwork.h"
#include "Camera/CameraComponent.h"
#include "Components/DecalComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/SpringArmComponent.h"
#include "Materials/Material.h"
#include "Engine/World.h"

ADiaBalShadowPlayerCharacter::ADiaBalShadowPlayerCharacter()
{
	// Set size for player capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate character to camera direction
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Rotate character to moving direction
	GetCharacterMovement()->RotationRate = FRotator(0.f, 640.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	// Create a camera boom...
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->SetUsingAbsoluteRotation(true); // Don't want arm to rotate when character does
	CameraBoom->TargetArmLength = 800.f;
	CameraBoom->SetRelativeRotation(FRotator(-60.f, 0.f, 0.f));
	CameraBoom->bDoCollisionTest = false; // Don't want to pull camera in when it collides with level

	// Create a camera...
	TopDownCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
	TopDownCameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	TopDownCameraComponent->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Activate ticking in order to update the cursor every frame.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;

	CharacterGold = 0.0f;
	CharacterLevel = 1;
}

void ADiaBalShadowPlayerCharacter::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);
}

void ADiaBalShadowPlayerCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
}


void ADiaBalShadowPlayerCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ADiaBalShadowPlayerCharacter, CharacterGold);
	DOREPLIFETIME(ADiaBalShadowPlayerCharacter, CharacterLevel);
	DOREPLIFETIME(ADiaBalShadowPlayerCharacter, CharacterExperience);
	DOREPLIFETIME(ADiaBalShadowPlayerCharacter, MaxCharacterExperience);
}


float ADiaBalShadowPlayerCharacter::GetGold() const
{
	return CharacterGold;
}

float ADiaBalShadowPlayerCharacter::AddGold(float Gold)
{
	CharacterGold = FMath::Clamp((Gold + Gold), 0.0f, 99999.0f);
	return CharacterGold;
}

int32 ADiaBalShadowPlayerCharacter::GetCharacterLevel() const
{
	return CharacterLevel;
}

int32 ADiaBalShadowPlayerCharacter::SetCharacterLevel(int32 NewLevel)
{
	if (CharacterLevel != NewLevel && NewLevel > 0)
	{
		//RemoveStartupGameplayAbilities();
		CharacterLevel = NewLevel;
		//AddStartupGameplayAbilities();
	}
	return CharacterLevel;
}

int32 ADiaBalShadowPlayerCharacter::GetCharacterExperience() const
{
	return CharacterExperience;
}

int32 ADiaBalShadowPlayerCharacter::SetCharacterExperience(int32 NewExperience)
{
	CharacterExperience = FMath::Clamp((CharacterExperience - NewExperience), 0, MaxCharacterExperience);
	return CharacterExperience;
}

int32 ADiaBalShadowPlayerCharacter::GetMaxCharacterExperience() const
{
	return MaxCharacterExperience;
}

int32 ADiaBalShadowPlayerCharacter::SetMaxCharacterExperience(int32 NewMaxExperience)
{
	MaxCharacterExperience = NewMaxExperience;
	return MaxCharacterExperience;
}
