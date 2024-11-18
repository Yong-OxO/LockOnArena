// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/Trigger/BossClearPortal.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BillboardComponent.h"
#include "Kismet/KismetMathLibrary.h"

ABossClearPortal::ABossClearPortal()
{
	SetActorHiddenInGame(true);

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	StaticMeshComponent->SetupAttachment(RootComponent);
	StaticMeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);	

	UpVector = RootComponent->GetUpVector();

	SetActorEnableCollision(false);	
}

void ABossClearPortal::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	StaticMeshComponent->AddLocalRotation(FRotator(0.0, 60 * DeltaSeconds, 0.0));

	StaticMeshComponent->K2_AddRelativeLocation(UpVector * 30 * DeltaSeconds, false, HitResult, true);
	float Distance = UKismetMathLibrary::Vector_Distance(StaticMeshComponent->GetComponentLocation(), RootComponent->GetComponentLocation());

	if (Distance > 25)
	{
		UpVector = -UpVector;
	}
}

void ABossClearPortal::ActivePortal()
{
	SetActorHiddenInGame(false);
	SetActorEnableCollision(true);
}
