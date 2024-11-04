// Fill out your copyright notice in the Description page of Project Settings.


#include "Skill/HomingProjectile.h"
#include "Skill/HomingProjectileComponent.h"
#include "Actor/Weapon/WeaponBase.h"
#include "Kismet/GameplayStatics.h"
//#include "Character/InGamePlayerController.h"

// Sets default values
AHomingProjectile::AHomingProjectile()
{
	PrimaryActorTick.bCanEverTick = true;
	InitialLifeSpan = 5.f;

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ProjectileStaticMeshComponent"));;
	RootComponent = StaticMeshComponent;
	StaticMeshComponent->SetCollisionProfileName(TEXT("Projectile"));
	StaticMeshComponent->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnTrigger);

	HomingComponent = CreateDefaultSubobject<UHomingProjectileComponent>(TEXT("HomingComponent"));
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

void AHomingProjectile::OnTrigger(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Display, TEXT("TestProjectile"));

	UGameplayStatics::ApplyDamage(OtherActor, 30.f, GetWorld()->GetFirstPlayerController(), this, nullptr);

	Destroy();
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
	
	Weapon = GetOwner<AWeaponBase>();
	EnemyTargetLocation = Weapon->TargetLocation;

	if (HomingComponent)
	{
		HomingComponent->SetHomingTarget(EnemyTargetLocation);
	}
}



