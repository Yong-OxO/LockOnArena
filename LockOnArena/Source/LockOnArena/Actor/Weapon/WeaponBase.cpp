// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/Weapon/WeaponBase.h"
#include "Character/Animation/AnimInstance/InGameAnimInstance.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Character/DefaultCharacter.h"
#include "Character/CharacterStateComponent.h"


// Sets default values
AWeaponBase::AWeaponBase()
{
	PrimaryActorTick.bCanEverTick = true;

	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultSceneRoot"));
	RootComponent = SceneComponent;

	SkeletalMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMeshComponent"));
	SkeletalMeshComponent->SetupAttachment(RootComponent);
	SkeletalMeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMeshComponent->SetupAttachment(RootComponent);
	StaticMeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	static ConstructorHelpers::FObjectFinder<UDataTable> DataTableAsset(TEXT("/Script/Engine.DataTable'/Game/Blueprint/Data/DT_WeaponBase.DT_WeaponBase'"));
	DataTable = DataTableAsset.Object;
	// @TODO : RowName namespace
	DataTableRow = DataTable->FindRow<FWeaponBaseTableRow>(FName("Basic"), TEXT("WeaponBase DataTableRow"));
}

void AWeaponBase::Attack()
{
	bool bCanAttack = OwnerCharacter->GetState()->CanAttack();
	bool bCanMove = OwnerCharacter->GetState()->CanMove();
	if (bCanAttack || bCanMove || !AimInstance->Montage_IsPlaying(nullptr))
	{
		ADefaultCharacter* TestOwnerCharacter = CastChecked<ADefaultCharacter>(GetOwner());
		AimInstance->Montage_Play(DataTableRow->WeaponAttackMontage);
	}
}

void AWeaponBase::SetData(const FDataTableRowHandle& InRowHandle)
{
	ensureMsgf(DataTableRow, TEXT("Not Valid DataTableRow"));

	if (DataTableRow->SkeletalMesh)
	{
		SkeletalMeshComponent->SetSkeletalMesh(DataTableRow->SkeletalMesh);
	}
	else if (DataTableRow->StaticMesh)
	{
		StaticMeshComponent->SetStaticMesh(DataTableRow->StaticMesh);
	}
	AimInstance = DataTableRow->AimInstance;

	OwnerCharacter = CastChecked<ADefaultCharacter>(GetOwner());
}

void AWeaponBase::BeginPlay()
{ 
	Super::BeginPlay();
}

// Called every frame
void AWeaponBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

