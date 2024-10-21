// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actor/Weapon/WeaponBase.h"
#include "RifleBase.generated.h"

USTRUCT()
struct LOCKONARENA_API FRifleTableRow : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	int32 Ammo = 50;
};


UCLASS()
class LOCKONARENA_API ARifleBase : public AWeaponBase
{
	GENERATED_BODY()
public:
	virtual void Attack() override;

	UPROPERTY()
	int count = 0;
};
