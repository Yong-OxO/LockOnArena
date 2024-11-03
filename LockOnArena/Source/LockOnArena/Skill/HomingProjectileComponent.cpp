// Fill out your copyright notice in the Description page of Project Settings.


#include "Skill/HomingProjectileComponent.h"

UHomingProjectileComponent::UHomingProjectileComponent()
{
	bIsHomingProjectile = true;
	PrimaryComponentTick.bCanEverTick = true;
}

void UHomingProjectileComponent::SetHomingTarget(FVector TargetLocation)
{
	HomingAccelerationMagnitude = 10000.0f;
	
	HomingTargetLocation = TargetLocation;
}

void UHomingProjectileComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (bCanMove)
	{
		FVector Direction = (HomingTargetLocation - GetOwner()->GetActorLocation()).GetSafeNormal();
		FVector NewVelocity = Direction * 4000.f; //HomingAccelerationMagnitude
		Velocity = NewVelocity;
	}
}
