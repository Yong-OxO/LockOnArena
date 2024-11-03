// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HomingProjectile.generated.h"

class UHomingProjectileComponent;
UCLASS()
class LOCKONARENA_API AHomingProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	AHomingProjectile();

	void SpawnProjectile(FVector StartLocation, FRotator StartRotation, FVector TargetLocation);
protected:
	virtual void BeginPlay() override;


private:	
	UPROPERTY(VisibleAnywhere, Category = "Movement") 
	UHomingProjectileComponent* HomingComponent;

	UFUNCTION()
	void StartMovement();

	FTimerHandle TimerHandle;
};
