// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/DefaultCharacter.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "CharacterStateComponent.h"

// Sets default values
ADefaultCharacter::ADefaultCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	Weapon_Static	= CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Weapon_Static"));
	Weapon_Static->SetupAttachment(GetMesh(), TEXT("WeaponSocket"));
	Weapon_Skeletal = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Weapon_Skeletal"));
	Weapon_Skeletal->SetupAttachment(GetMesh(), TEXT("WeaponSocket"));
	/*static ConstructorHelpers::FObjectFinder<AActor> WeaponAsset(TEXT("/Script/Engine.Blueprint'/Game/Blueprint/Actor/Weapon/BP_Rifle.BP_Rifle'"));
	Weapon_Static->SetStaticMesh(WeaponAsset.Object);*/
}

// Called when the game starts or when spawned
void ADefaultCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	
}

// Called every frame
void ADefaultCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ADefaultCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

