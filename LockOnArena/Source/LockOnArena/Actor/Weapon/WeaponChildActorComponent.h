// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ChildActorComponent.h"
#include "WeaponChildActorComponent.generated.h"


class AWeaponBase;

UCLASS()
class LOCKONARENA_API UWeaponChildActorComponent : public UChildActorComponent
{
	GENERATED_BODY()

public:
	TSubclassOf<AWeaponBase> WeaponClass;

public:
	UWeaponChildActorComponent();

public:
	virtual void SetData(const FDataTableRowHandle& InRowHandle);
	//virtual void SetData( const FDataTableRowHandle& InRowHandle);

};
