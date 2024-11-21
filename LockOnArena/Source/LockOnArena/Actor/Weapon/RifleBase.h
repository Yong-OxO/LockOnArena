// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actor/Weapon/WeaponBase.h"
#include "RifleBase.generated.h"


class AEffect;

USTRUCT()
struct LOCKONARENA_API FRifleTableRow : public FWeaponBaseTableRow
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	int32 MaxAmmo = 30;
	UPROPERTY(EditAnywhere)
	float FireRange = 3000.f;

	UPROPERTY(EditAnywhere, Category = "Effect", meta = (RowType = "/Script/LOCKONARENA.EffectTableRow"))
	FDataTableRowHandle HitEffectRowHandle;


};


UCLASS()
class LOCKONARENA_API ARifleBase : public AWeaponBase
{
	GENERATED_BODY()
	
public:
	ARifleBase();

public:
	UPROPERTY(EditAnywhere, Category = "Effect", meta = (RowType = "/Script/LOCKONARENA.EffectTableRow"))
	FDataTableRowHandle HitEffectRowHandle;

public:
	virtual void SetData(const FDataTableRowHandle& InHandle) override;

	virtual void Attack() override;
	virtual void Fire(const FVector Start, const FRotator Rotation);
	virtual void BeginDestroy() override;
	
	FVector StartLocation;
	FVector EndLocation;

	FRifleTableRow* DataRow;

	UPROPERTY()
	int32 MaxAmmo = 30;

	UPROPERTY()
	int32 CurrentAmmo;
	
	float FireRange;

	AEffect* HitEffect;
};
