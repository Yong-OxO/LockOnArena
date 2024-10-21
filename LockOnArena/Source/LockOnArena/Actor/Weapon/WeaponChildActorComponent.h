// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ChildActorComponent.h"
#include "WeaponChildActorComponent.generated.h"

/**
 * 
 */
UCLASS()
class LOCKONARENA_API UWeaponChildActorComponent : public UChildActorComponent
{
	GENERATED_BODY()


public:
	UWeaponChildActorComponent();

public:
	virtual void SetData(const FDataTableRowHandle& InRowHandle);
	//virtual void SetData( const FDataTableRowHandle& InRowHandle);

};
