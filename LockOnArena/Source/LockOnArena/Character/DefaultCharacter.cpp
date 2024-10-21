// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/DefaultCharacter.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "CharacterStateComponent.h"
#include "Actor/Weapon/WeaponChildActorComponent.h"
#include "Subsystem/WeaponSubsystem.h"

// Sets default values
ADefaultCharacter::ADefaultCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	// @TODO : RowName namespace
	static ConstructorHelpers::FObjectFinder<UDataTable> DataTableAsset(TEXT("/Script/Engine.DataTable'/Game/Blueprint/Data/DT_BaseCharacter.DT_BaseCharacter'"));
	DataTable = DataTableAsset.Object;
	DataTableRow = DataTable->FindRow<FDefaultCharacterTableRow>(FName("Basic"), TEXT("Character DataTableRow"));


	Weapon = CreateDefaultSubobject<UWeaponChildActorComponent>(TEXT("Weapon"));
	Weapon->SetupAttachment(GetMesh(), TEXT("WeaponSocket"));

	CharacterState = CreateDefaultSubobject<UCharacterStateComponent>(TEXT("CharacterState"));
	CharacterState = DataTableRow->CharacterState;
	/*static ConstructorHelpers::FObjectFinder<AActor> WeaponAsset(TEXT("/Script/Engine.Blueprint'/Game/Blueprint/Actor/Weapon/BP_Rifle.BP_Rifle'"));
	Weapon_Static->SetStaticMesh(WeaponAsset.Object);*/
	
}

// Called when the game starts or when spawned
void ADefaultCharacter::BeginPlay()
{
	Super::BeginPlay();

	// @TODO : WeaponType
	Weapon->SetData(DataTableRow->WeaponBaseTableRowHandle);
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

void ADefaultCharacter::SetData(const FDataTableRowHandle& InRowHandle)
{
	int a = 10;
}

