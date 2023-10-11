// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "DiaBalShadowCharacterBase.h"
#include "DiaBalShadowPlayerCharacter.generated.h"

UCLASS(Blueprintable)
class ADiaBalShadowPlayerCharacter : public ADiaBalShadowCharacterBase
{
	GENERATED_BODY()

public:
	ADiaBalShadowPlayerCharacter();

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

protected :
	UPROPERTY(EditAnywhere, Replicated, Category = Hero)
	float CharacterGold;
	
	UPROPERTY(EditAnywhere, Replicated, Category = Hero)
	int32 CharacterLevel;
	
	UPROPERTY(EditAnywhere, Replicated, Category = Hero)
	int32 CharacterExperience;

	UPROPERTY(EditAnywhere, Replicated, Category = Hero)
	int32 MaxCharacterExperience;
public:
	UFUNCTION(BlueprintCallable)
	virtual float GetGold() const;

	UFUNCTION(BlueprintCallable)
	virtual float AddGold(float Gold);

	UFUNCTION(BlueprintCallable)
	virtual int32 GetCharacterLevel() const;

	UFUNCTION(BlueprintCallable)
	virtual int32 SetCharacterLevel(int32 NewLevel);

	UFUNCTION(BlueprintCallable)
	virtual int32 GetCharacterExperience() const;

	UFUNCTION(BlueprintCallable)
	virtual int32 SetCharacterExperience(int32 NewExperience);

	UFUNCTION(BlueprintCallable)
	virtual int32 GetMaxCharacterExperience() const;

	UFUNCTION(BlueprintCallable)
	virtual int32 SetMaxCharacterExperience(int32 NewMaxExperience);
};

