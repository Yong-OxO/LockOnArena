// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnemyWeaponBase.generated.h"

UCLASS()
class LOCKONARENA_API AEnemyWeaponBase : public AActor
{
	GENERATED_BODY()
	
public:	
	AEnemyWeaponBase();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

};
