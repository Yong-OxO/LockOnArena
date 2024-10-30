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
	{
		SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultSceneRoot"));
		RootComponent = SceneComponent;
	
		SkeletalMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMeshComponent"));
		SkeletalMeshComponent->SetupAttachment(RootComponent);
		SkeletalMeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);

		StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
		StaticMeshComponent->SetupAttachment(RootComponent);
		StaticMeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
}

void AWeaponBase::Attack()
{
	if (DataTableRow->WeaponAttackMontage)
	{
		if (!AnimInstance->Montage_IsPlaying(nullptr))
		{
			AnimInstance->Montage_Play(DataTableRow->WeaponAttackMontage);
			CharacterState->SetAttack(false);
		}
	}
}

void AWeaponBase::SwapEquipment()
{
	int a = 0;
}

void AWeaponBase::SetData(const FDataTableRowHandle& InRowHandle)
{
	DataTableRow = InRowHandle.GetRow<FWeaponBaseTableRow>(TEXT("DataTableRow"));
	ensureMsgf(DataTableRow, TEXT("Not Valid DataTableRow"));
	SkeletalMesh = DataTableRow->SkeletalMesh;
	StaticMesh = DataTableRow->StaticMesh;
	{
		if (DataTableRow->SkeletalMesh)
		{
			SkeletalMeshComponent->SetSkeletalMesh(SkeletalMesh);
		}
		else if (DataTableRow->StaticMesh)
		{
			StaticMeshComponent->SetStaticMesh(StaticMesh);
		}
		else
		{
			StaticMeshComponent->SetStaticMesh(nullptr);
			SkeletalMeshComponent->SetSkeletalMesh(nullptr);
		}
	}
		OwnerCharacter = CastChecked<ADefaultCharacter>(GetOwner());
		CharacterState = OwnerCharacter->GetState();

		//MuzzleEffect = DataTableRow->MuzzleEffect;
		{
			USkeletalMeshComponent* MeshComponent = GetOwner()->GetComponentByClass<USkeletalMeshComponent>();
			MeshComponent->SetAnimClass(DataTableRow->AnimInstance);

			AnimInstance = Cast<UInGameAnimInstance>(MeshComponent->GetAnimInstance());

			AnimInstance->OnMontageEnded.AddDynamic(this, &ThisClass::OnMontageEnd);
		}
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

void AWeaponBase::OnMontageEnd(UAnimMontage* Montage, bool bInterrupted)
{
	CharacterState->SetAttack(true);
}

void AWeaponBase::UpdateCharacter()
{
	if (DataTableRow->WeaponChangeMontage)
	{
		if (!AnimInstance->Montage_IsPlaying(nullptr))
		{
			AnimInstance->Montage_Play(DataTableRow->WeaponChangeMontage);
			CharacterState->SetAttack(false);
		}
	}

	if (SkeletalMesh)
	{
		SkeletalMeshComponent->SetSkeletalMesh(SkeletalMesh);
	}
	else if (DataTableRow->StaticMesh)
	{
		StaticMeshComponent->SetStaticMesh(StaticMesh);
	}
	else
	{
		StaticMeshComponent->SetStaticMesh(nullptr);
		SkeletalMeshComponent->SetSkeletalMesh(nullptr);
	}

	{
		USkeletalMeshComponent* MeshComponent = GetOwner()->GetComponentByClass<USkeletalMeshComponent>();
		MeshComponent->SetAnimClass(DataTableRow->AnimInstance);
	}
}


