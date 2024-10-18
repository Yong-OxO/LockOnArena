// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "WeaponSubsystem.generated.h"

UCLASS()
class LOCKONARENA_API UWeaponSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
public:
	UWeaponSubsystem();
	FDataTableRowHandle FindWeapon(const FName& InWeaponName);

protected:
	UDataTable* WeaponBaseDataTable = nullptr;
	//UDataTable* 

};
