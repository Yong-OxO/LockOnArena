// Fill out your copyright notice in the Description page of Project Settings.


#include "Skill/HomingProjectile.h"
#include "Skill/HomingProjectileComponent.h"

// Sets default values
AHomingProjectile::AHomingProjectile()
{
	PrimaryActorTick.bCanEverTick = true;
	HomingComponent = CreateDefaultSubobject<UHomingProjectileComponent>(TEXT("HomingComponent"));


	UPrimitiveComponent* MyComponent = FindComponentByClass<UPrimitiveComponent>(); 

	if (MyComponent)
	{ // 충돌 프로필 이름을 "BlockAllDynamic"으로 설정 
		MyComponent->SetCollisionObjectType(ECollisionChannel::ECC_GameTraceChannel1);
	}

	HomingComponent->ProjectileGravityScale = 0.f;
	HomingComponent->InitialSpeed = 500.f;
	HomingComponent->bCanMove = false;
}

void AHomingProjectile::BeginPlay()
{
	Super::BeginPlay();	
	SetActorTickEnabled(true);

	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &AHomingProjectile::StartMovement, 0.3f, false);
}

void AHomingProjectile::StartMovement()
{
	HomingComponent->ProjectileGravityScale = 1.f;
	HomingComponent->bCanMove = true;
}


void AHomingProjectile::SpawnProjectile(FVector StartLocation, FRotator StartRotation, FVector TargetLocation)
{
	SetActorLocation(StartLocation);
	SetActorRotation(StartRotation);
	if (HomingComponent)
	{
		HomingComponent->SetHomingTarget(TargetLocation);
	}
}



