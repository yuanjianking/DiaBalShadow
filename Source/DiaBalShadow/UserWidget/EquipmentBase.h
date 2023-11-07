// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BoxBase.h"
#include "EquipmentBase.generated.h"


#ifdef MaxBoxRow
#undef MaxBoxRow
#endif // MaxBoxRow
#ifdef MaxBoxColumn
#undef MaxBoxColumn
#endif // MaxBoxColumn

#define MaxBoxRow 8
#define MaxBoxColumn 10


/**
 * 
 */
UCLASS()
class DIABALSHADOW_API UEquipmentBase : public UBoxBase
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UCellBase* WeaponSlot;

public:
	UFUNCTION(BlueprintImplementableEvent)
	void OnWeaponDroped(const FString& OldGUID);

public:
	UFUNCTION(BlueprintCallable)
	int32  GetMaxBoxRow() const;

	UFUNCTION(BlueprintCallable)
	int32  GetMaxBoxColumn() const;

	UFUNCTION(BlueprintCallable)
	void CreateCell(const FString& Path);

private:
	void WeaponDroped(UCellBase* Cell, UCellBase* OprationCell);
};
