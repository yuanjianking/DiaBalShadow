// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ComplexItemInventory.h"
#include "UniqueItemInventory.h"
#include "../DiaBalShadowPrimaryDataAsset.h"
#include "../DiaBalShadowTypes.h"
#include "DiaBalShadowItemManagerComponent.generated.h"



UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DIABALSHADOW_API UDiaBalShadowItemManagerComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UDiaBalShadowItemManagerComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	UComplexItemInventory ComplexItem;
	UUniqueItemInventory UniqueItem;

public:
	UFUNCTION(BlueprintCallable, Category = Item)
	int32 GetCount(UDiaBalShadowPrimaryDataAsset* Item)const;
public:
	UFUNCTION(BlueprintCallable, Category = Complex)
	bool AddComplexItem(UDiaBalShadowPrimaryDataAsset* Item, int32 Count);

	UFUNCTION(BlueprintCallable, Category = Complex)
	int32 GetComplexCount(UDiaBalShadowPrimaryDataAsset* Item) const;

	UFUNCTION(BlueprintCallable, Category = Complex)
	int32 GetComplexGroup(UDiaBalShadowPrimaryDataAsset* Item) const;
public:
	UFUNCTION(BlueprintCallable, Category = Unique)
	bool AddUniqueItem(FUniqueData Item, bool bAutoSlot = true);

	UFUNCTION(BlueprintCallable, Category = Unique)
	void GetUniqueItems(TArray<FUniqueData>& Items);

	UFUNCTION(BlueprintCallable, Category = Unique)
	void RemoveUniqueItem(FString GUID);
};
