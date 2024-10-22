// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actor/Weapon/WeaponBase.h"
#include "RifleBase.generated.h"

USTRUCT()
struct LOCKONARENA_API FRifleTableRow : public FWeaponBaseTableRow
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	int32 MaxAmmo = 50;
	UPROPERTY(EditAnywhere)
	float FireRange = 3000.f;
};


UCLASS()
class LOCKONARENA_API ARifleBase : public AWeaponBase
{
	GENERATED_BODY()
	
public:
	ARifleBase();
public:
	virtual void SetData(const FDataTableRowHandle& InHandle) override;

	virtual void Attack() override;
	virtual void Fire(const FVector Start, const FRotator Rotation);
	
	
	FVector StartLocation;
	FVector EndLocation;

	FRifleTableRow* DataRow;

	UPROPERTY()
	int32 MaxAmmo = 50;

	UPROPERTY()
	int32 CurrentAmmo;
	
	float FireRange;
};
