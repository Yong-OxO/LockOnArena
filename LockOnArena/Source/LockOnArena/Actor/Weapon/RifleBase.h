// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actor/Weapon/WeaponBase.h"
#include "RifleBase.generated.h"

/**
 * 
 */
UCLASS()
class LOCKONARENA_API ARifleBase : public AWeaponBase
{
	GENERATED_BODY()
public:
	virtual void Attack();
};
