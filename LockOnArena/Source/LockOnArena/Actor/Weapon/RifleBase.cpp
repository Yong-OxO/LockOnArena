// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/Weapon/RifleBase.h"



void ARifleBase::SetData(const FDataTableRowHandle& InHandle)
{
	Super::SetData(InHandle);

	DataRow = InHandle.GetRow<FRifleTableRow>(TEXT("DataRow"));
	MaxAmmo = DataRow->MaxAmmo;
	FireRange = DataRow->FireRange;
}

void ARifleBase::Attack()
{
	Super::Attack();
}

void ARifleBase::Fire(const FVector Start, const FRotator Rotation)
{
	FCollisionQueryParams CollisionQueryParams;
	CollisionQueryParams.AddIgnoredActor(this);

	{
		StartLocation = Start;
		FVector NormalVector = Rotation.Vector();
		EndLocation = StartLocation + NormalVector * FireRange;
	}
	FHitResult HitResult;
	GetWorld()->LineTraceSingleByChannel(
		HitResult, 
		StartLocation, 
		EndLocation,
		ECollisionChannel::ECC_GameTraceChannel1,
		CollisionQueryParams);

	DrawDebugLine(GetWorld(), StartLocation, EndLocation, FColor::Red, false, 3.f);
}

