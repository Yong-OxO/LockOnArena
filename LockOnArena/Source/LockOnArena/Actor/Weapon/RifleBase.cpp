// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/Weapon/RifleBase.h"
#include "Kismet/GameplayStatics.h"
#include "Character/DefaultCharacter.h"
#include "Character/InGamePlayerController.h"
#include "Character/CharacterStateComponent.h"
#include "Misc/Utils.h"
#include "Actor/Effect/Effect.h"

ARifleBase::ARifleBase()
{
	CurrentAmmo = MaxAmmo;
}

void ARifleBase::SetData(const FDataTableRowHandle& InHandle)
{
	Super::SetData(InHandle);

	DataRow = InHandle.GetRow<FRifleTableRow>(TEXT("DataRow"));
	FireRange = DataRow->FireRange;
	HitEffectRowHandle = DataRow->HitEffectRowHandle;
}

void ARifleBase::Attack()
{
	if (CurrentAmmo <= 0) { return; }

	Super::Attack();

	UE_LOG(LogTemp, Display, TEXT("Rifle Attack"));
}

void ARifleBase::Fire(const FVector Start, const FRotator Rotation)
{
	if (CurrentAmmo <= 0) { return; }

	FCollisionQueryParams CollisionQueryParams;
	CollisionQueryParams.AddIgnoredActor(this);

	{
		StartLocation = Start;
		FVector NormalVector = Rotation.Vector();
		StartLocation = StartLocation + NormalVector * 40.f;
		EndLocation = StartLocation + NormalVector * FireRange;		
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
	//DrawDebugLine(GetWorld(), StartLocation, EndLocation, FColor::Red, false, 3.f);

	TSubclassOf<UCustomDamageType> CustomDamageType;

	UGameplayStatics::ApplyDamage(HitResult.GetActor(), CharacterState->GetCharacterATK(), CharacterController, this, CustomDamageType);

	UE_LOG(LogTemp, Display, TEXT("Ammo : %d"), CurrentAmmo);
	//--CurrentAmmo;

	{	
		bool EffectSucceed = GetWorld()->LineTraceSingleByChannel(
		HitResult,
		StartLocation,
		EndLocation,
		ECollisionChannel::ECC_WorldStatic,
		CollisionQueryParams);

		if (EffectSucceed)
		{
			FVector EffectLocation = HitResult.Location;
			FRotator EffectRotation = (-GetActorForwardVector()).Rotation();

			HitEffect = GetWorld()->SpawnActor<AEffect>();
			HitEffect->Play(HitEffectRowHandle, EffectLocation, EffectRotation);
		}
	}
}

void ARifleBase::BeginDestroy()
{
	Super::BeginDestroy();
}

