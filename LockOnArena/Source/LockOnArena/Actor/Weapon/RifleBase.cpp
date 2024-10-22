// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/Weapon/RifleBase.h"



ARifleBase::ARifleBase()
{
	CurrentAmmo = MaxAmmo;
}

void ARifleBase::SetData(const FDataTableRowHandle& InHandle)
{
	Super::SetData(InHandle);

	DataRow = InHandle.GetRow<FRifleTableRow>(TEXT("DataRow"));
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
		StartLocation = StartLocation + NormalVector * 40.f;
	}
	FHitResult HitResult;
	bool Succeed = GetWorld()->LineTraceSingleByChannel(
		HitResult, 
		StartLocation, 
		EndLocation,
		ECollisionChannel::ECC_GameTraceChannel1,
		CollisionQueryParams);
	if (Succeed)
	{
		UE_LOG(LogTemp, Display, TEXT("asdf"));
	}
	DrawDebugLine(GetWorld(), StartLocation, EndLocation, FColor::Red, false, 3.f);

	UE_LOG(LogTemp, Display, TEXT("Ammo : %d"), CurrentAmmo);
	--CurrentAmmo;
}

