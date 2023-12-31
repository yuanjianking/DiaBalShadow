// Copyright Epic Games, Inc. All Rights Reserved.

#include "DiaBalShadowPlayerController.h"
#include "GameFramework/Pawn.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "NiagaraSystem.h"
#include "NiagaraFunctionLibrary.h"
#include "Engine/World.h"
#include "UObject/Class.h"
#include "Blueprint/UserWidget.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "DiaBalShadowPlayerCharacter.h"
#include "DiaBalShadowEnemyCharacter.h"

ADiaBalShadowPlayerController::ADiaBalShadowPlayerController()
{
	bShowMouseCursor = true;
	bEnableClickEvents = true;
	bEnableTouchEvents = true;
	bEnableMouseOverEvents = true;
	EnableInput(this);
	
	CachedDestination = FVector::ZeroVector;
	FollowTime = 0.f;

	itemManager = CreateDefaultSubobject<UDiaBalShadowItemManagerComponent>(TEXT("UDiaBalShadowItemManagerComponent"));
}

void ADiaBalShadowPlayerController::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	//Add Input Mapping Context
	if(DefaultMappingContext)
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
	UClass* CursorClass = LoadClass<UUserWidget>(nullptr, TEXT("Blueprint'/Game/Blueprints/WidgetBP/Menu/Cursor.Cursor_C'"));
	if (CursorClass)
	{
		UUserWidget* Cursor = CreateWidget<UUserWidget>(GetWorld(), CursorClass);
		SetMouseCursorWidget(EMouseCursor::Default, Cursor);
	}
}

void ADiaBalShadowPlayerController::SetupInputComponent()
{
	// set up gameplay key bindings
	Super::SetupInputComponent();

	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent))
	{
		// Setup mouse input events
		if(SetDestinationClickAction)
		{
			EnhancedInputComponent->BindAction(SetDestinationClickAction, ETriggerEvent::Started, this, &ADiaBalShadowPlayerController::OnInputStarted);
			EnhancedInputComponent->BindAction(SetDestinationClickAction, ETriggerEvent::Triggered, this, &ADiaBalShadowPlayerController::OnSetDestinationTriggered);
			EnhancedInputComponent->BindAction(SetDestinationClickAction, ETriggerEvent::Completed, this, &ADiaBalShadowPlayerController::OnSetDestinationReleased);
			EnhancedInputComponent->BindAction(SetDestinationClickAction, ETriggerEvent::Canceled, this, &ADiaBalShadowPlayerController::OnSetDestinationReleased);
		}
		// Setup touch input events
		if(SetDestinationTouchAction)
		{
		EnhancedInputComponent->BindAction(SetDestinationTouchAction, ETriggerEvent::Started, this, &ADiaBalShadowPlayerController::OnInputStarted);
		EnhancedInputComponent->BindAction(SetDestinationTouchAction, ETriggerEvent::Triggered, this, &ADiaBalShadowPlayerController::OnTouchTriggered);
		EnhancedInputComponent->BindAction(SetDestinationTouchAction, ETriggerEvent::Completed, this, &ADiaBalShadowPlayerController::OnTouchReleased);
		EnhancedInputComponent->BindAction(SetDestinationTouchAction, ETriggerEvent::Canceled, this, &ADiaBalShadowPlayerController::OnTouchReleased);
		}
	}
}

void ADiaBalShadowPlayerController::OnInputStarted()
{
//	StopMovement();
}

// Triggered every frame when the input is held down
void ADiaBalShadowPlayerController::OnSetDestinationTriggered()
{
	// We flag that the input is being pressed
	FollowTime += GetWorld()->GetDeltaSeconds();
	
	// We look for the location in the world where the player has pressed the input
	FHitResult Hit;
	bool bHitSuccessful = false;
	if (bIsTouch)
	{
		bHitSuccessful = GetHitResultUnderFinger(ETouchIndex::Touch1, ECollisionChannel::ECC_Visibility, true, Hit);
	}
	else
	{
		bHitSuccessful = GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, true, Hit);
	}

	// If we hit a surface, cache the location
	if (bHitSuccessful)
	{
		CachedDestination = Hit.Location;
	}

	if(Hit.GetActor() && Hit.GetActor()->IsA<ADiaBalShadowEnemyCharacter>())
	{ 
		ADiaBalShadowEnemyCharacter* EnemyCharacter = Cast<ADiaBalShadowEnemyCharacter>(Hit.GetActor());
		ADiaBalShadowPlayerCharacter* ControlledCharacter = Cast<ADiaBalShadowPlayerCharacter>(GetCharacter());
		FGameplayTagContainer TagContainer(FGameplayTag::RequestGameplayTag(FName("Attack.Melee")));
		if(!EnemyCharacter->IsDead)
		{
			ControlledCharacter->GetAbilitySystemComponent()->TryActivateAbilitiesByTag(TagContainer, true);			
		}
		else
		{

			
		}
		return;
	}

	// Move towards mouse pointer or touch
	APawn* ControlledPawn = GetPawn();
	if (ControlledPawn != nullptr)
	{
		FVector WorldDirection = (CachedDestination - ControlledPawn->GetActorLocation()).GetSafeNormal();
		ControlledPawn->AddMovementInput(WorldDirection, 1.0, false);
	}
}

void ADiaBalShadowPlayerController::OnSetDestinationReleased()
{
	// If it was a short press
	if (FollowTime <= ShortPressThreshold)
	{
		// We move there and spawn some particles
		UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, CachedDestination);
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, FXCursor, CachedDestination, FRotator::ZeroRotator, FVector(1.f, 1.f, 1.f), true, true, ENCPoolMethod::None, true);
	}

	FollowTime = 0.f;
}

// Triggered every frame when the input is held down
void ADiaBalShadowPlayerController::OnTouchTriggered()
{
	bIsTouch = true;

	OnSetDestinationTriggered();
}

void ADiaBalShadowPlayerController::OnTouchReleased()
{
	bIsTouch = false;

	OnSetDestinationReleased();
}
