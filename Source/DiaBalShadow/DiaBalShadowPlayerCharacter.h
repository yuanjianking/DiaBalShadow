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

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

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
	int32 CharacterGold;
		
	UPROPERTY(EditAnywhere, Replicated, Category = Hero)
	int32 CharacterExperience;

	UPROPERTY(EditAnywhere, Replicated, Category = Hero)
	int32 MaxCharacterExperience;

public:
	UFUNCTION(BlueprintCallable)
	virtual int32 GetGold() const;

	UFUNCTION(BlueprintCallable)
	virtual int32 AddGold(int32 Gold);

	UFUNCTION(BlueprintCallable)
	virtual int32 GetCharacterExperience() const;

	UFUNCTION(BlueprintCallable)
	virtual int32 SetCharacterExperience(int32 NewExperience);

	UFUNCTION(BlueprintCallable)
	virtual int32 GetMaxCharacterExperience() const;

	UFUNCTION(BlueprintCallable)
	virtual int32 SetMaxCharacterExperience(int32 NewMaxExperience);

public:
	UFUNCTION(BlueprintCallable)
	void TestAttributeSet_Health(float NewHealth);
};

