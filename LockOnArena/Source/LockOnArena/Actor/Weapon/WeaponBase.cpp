// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/Weapon/WeaponBase.h"
#include "Character/Animation/AnimInstance/InGameAnimInstance.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Character/DefaultCharacter.h"
#include "Character/CharacterStateComponent.h"
#include "Skill/SkillSystem.h"


// Sets default values
AWeaponBase::AWeaponBase()
{
	PrimaryActorTick.bCanEverTick = true;
	{
		static ConstructorHelpers::FObjectFinder<UDataTable> DataTableAsset(TEXT("/Script/Engine.DataTable'/Game/Blueprint/Data/DT_WeaponBase.DT_WeaponBase'"));
		DataTable = DataTableAsset.Object;
		// @TODO : RowName namespace or DataTableRow에서 본인의 Handle관리
		//DataTableRow = DataTable->FindRow<FWeaponBaseTableRow>(FName("Basic"), TEXT("WeaponBase DataTableRow"));
	}
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
		if (!AimInstance->Montage_IsPlaying(nullptr))
		{
			AimInstance->Montage_Play(DataTableRow->WeaponAttackMontage);
			CharacterState->SetAttack(false);
		}
	}
}

void AWeaponBase::SwapEquipment(const int32 InValue)
{
}

void AWeaponBase::SetData(const FDataTableRowHandle& InRowHandle)
{
	DataTableRow = InRowHandle.GetRow<FWeaponBaseTableRow>(TEXT("DataTableRow"));
	ensureMsgf(DataTableRow, TEXT("Not Valid DataTableRow"));
	{
		if (DataTableRow->SkeletalMesh)
		{
			SkeletalMeshComponent->SetSkeletalMesh(DataTableRow->SkeletalMesh);
		}
		else if (DataTableRow->StaticMesh)
		{
			StaticMeshComponent->SetStaticMesh(DataTableRow->StaticMesh);
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
			MeshComponent->SetAnimClass(DataTableRow->AimInstance);

			AimInstance = Cast<UInGameAnimInstance>(MeshComponent->GetAnimInstance());

			AimInstance->OnMontageEnded.AddDynamic(this, &ThisClass::OnMontageEnd);
		}
		if (SkillSystem)
		{
			SkillSystem->Destroy();
		}
		SkillSystem = GetWorld()->SpawnActor<ASkillSystem>(DataTableRow->SkillSystem);
		SkillSystem->SetOwner(GetOwner());
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


