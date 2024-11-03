// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "HomingProjectileComponent.generated.h"

/**
 * 
 */
UCLASS()
class LOCKONARENA_API UHomingProjectileComponent : public UProjectileMovementComponent
{
	GENERATED_BODY()

public:
	UHomingProjectileComponent();

	void SetHomingTarget(FVector TargetLocation);

	bool bCanMove = false;

protected:
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
private:
	FVector HomingTargetLocation;


	
};
