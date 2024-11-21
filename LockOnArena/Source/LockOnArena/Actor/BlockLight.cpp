// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/BlockLight.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
ABlockLight::ABlockLight()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	StaticMeshComponent->SetupAttachment(RootComponent);

	StaticMeshComponent->SetCastShadow(true);
}

// Called when the game starts or when spawned
void ABlockLight::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABlockLight::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

