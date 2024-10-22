// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/Effect/Effect.h"
#include "Particles/ParticleSystem.h"
#include "Particles/ParticleSystemComponent.h"
#include "Components/SceneComponent.h"

FEffectTableRow::FEffectTableRow()
	: EffectClass(AEffect::StaticClass())
{
}

// Sets default values
AEffect::AEffect()
{
	PrimaryActorTick.bCanEverTick = true;

	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	RootComponent = SceneComponent;

	ParticleComponent = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("ParticleComponent"));
	ParticleComponent->SetupAttachment(SceneComponent);
	ParticleComponent->bAutoActivate = false;
}

// Called when the game starts or when spawned
void AEffect::BeginPlay()
{
	Super::BeginPlay();


	
}

// Called every frame
void AEffect::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AEffect::Play(const FDataTableRowHandle& InHandle, const FVector InLocation, const FRotator InRotation)
{
	SetData(InHandle);
	SetActorLocation(InLocation);
	SetActorRotation(InRotation);

	ParticleComponent->ActivateSystem(true);
}


void AEffect::SetData(const FDataTableRowHandle& InHandle)
{
	RowHandle = InHandle;
	ensure(!RowHandle.IsNull());
	FEffectTableRow* DataRow = RowHandle.GetRow<FEffectTableRow>(TEXT("DataRow"));

	ParticleComponent->SetTemplate(DataRow->Particle);
	CustomTimeDilation = DataRow->PlaySpeed;
	SetActorTransform(DataRow->Transform);
}



