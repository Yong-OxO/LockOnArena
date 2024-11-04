// Fill out your copyright notice in the Description page of Project Settings.


#include "Skill/HomingProjectileComponent.h"
#include "Skill/HomingProjectile.h"
#include "Skill/HomingSkill.h"
#include "Actor/Weapon/WeaponBase.h"


UHomingProjectileComponent::UHomingProjectileComponent()
{
	bIsHomingProjectile = true;
	PrimaryComponentTick.bCanEverTick = true;
}

void UHomingProjectileComponent::SetHomingTarget(FVector TargetLocation)
{
	Weapon = Cast<AWeaponBase>(GetOwner()->GetOwner());

	HomingAccelerationMagnitude = 10000.0f;
	
	HomingTargetLocation = TargetLocation;

}

void UHomingProjectileComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (bCanMove)
	{
		FVector Direction = (Weapon->TargetLocation - GetOwner()->GetActorLocation()).GetSafeNormal();
		FVector NewVelocity = Direction * 4000.f; //HomingAccelerationMagnitude
		Velocity = NewVelocity;
	}
}
