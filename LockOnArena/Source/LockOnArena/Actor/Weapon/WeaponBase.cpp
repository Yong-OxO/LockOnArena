// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/Weapon/WeaponBase.h"
#include "Character/Animation/AnimInstance/InGameAnimInstance.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Character/DefaultCharacter.h"
#include "Character/InGamePlayerController.h"
#include "Character/CharacterStateComponent.h"
#include "Skill/SkillBaseComponent.h"
#include "Widget/DefaultHUD.h"
#include "Widget/MainWidget.h"
#include "Widget/SkillUserWidget.h"


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

		//LockOn = CreateDefaultSubobject<USkillBaseComponent>(TEXT("LockOn"));
		//Skill01 = CreateDefaultSubobject<USkillBaseComponent>(TEXT("Skill01"));
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
	UpdateCharacter();

	if (DataTableRow->WeaponChangeMontage)
	{
		if (!AnimInstance->Montage_IsPlaying(nullptr))
		{
			AnimInstance->Montage_Play(DataTableRow->WeaponChangeMontage);
			CharacterState->SetAttack(false);
		}		
	}
	ADefaultHUD* HUD = Cast<ADefaultHUD>(CharacterController->GetHUD());
	USkillUserWidget* UI_Skill = HUD->MainWidget->UI_Skill;
	UI_Skill->SetData(DataHandle);
}

float AWeaponBase::GetLockOn_CD()
{
	return LockOn->GetCooldown();
}

float AWeaponBase::GetLockOn_MaxCD()
{
	return LockOn->GetMaxCooldown();
}

float AWeaponBase::GetSkill01_CD()
{
	return Skill01->GetCooldown();
}

float AWeaponBase::GetSkill01_MaxCD()
{
	return Skill01->GetMaxCooldown();
}

void AWeaponBase::SetData(const FDataTableRowHandle& InRowHandle)
{
	DataHandle = InRowHandle;
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
		CharacterController = Cast<AInGamePlayerController>(OwnerCharacter->GetController());
		CharacterState = OwnerCharacter->GetState();

		//MuzzleEffect = DataTableRow->MuzzleEffect;
		{
			USkeletalMeshComponent* MeshComponent = GetOwner()->GetComponentByClass<USkeletalMeshComponent>();
			MeshComponent->SetAnimClass(DataTableRow->AnimInstance);

			AnimInstance = Cast<UInGameAnimInstance>(MeshComponent->GetAnimInstance());

			AnimInstance->OnMontageEnded.AddDynamic(this, &ThisClass::OnMontageEnd);
		}
		{
			WeaponATK = DataTableRow->WeaponATK;
			CharacterState->AddCharacterATK(WeaponATK);
		}
		{
			LockOn = NewObject<USkillBaseComponent>(this, DataTableRow->LockOnClass, TEXT("LockOn"));
			LockOn->SetData(DataTableRow->LockOnHandle);
			LockOn->RegisterComponent();
			Skill01 = NewObject<USkillBaseComponent>(this, DataTableRow->Skill01Class, TEXT("Skill01"));
			Skill01->SetData(DataTableRow->Skill01);
			Skill01->RegisterComponent();
		}
		{

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
	AActor* Temp = GetOwner();
	USkeletalMeshComponent* MeshComponent = GetOwner()->GetComponentByClass<USkeletalMeshComponent>();
	MeshComponent->SetAnimClass(DataTableRow->AnimInstance);

	AnimInstance = Cast<UInGameAnimInstance>(MeshComponent->GetAnimInstance());

	AnimInstance->OnMontageEnded.AddDynamic(this, &ThisClass::OnMontageEnd);

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
		ADefaultHUD* HUD = Cast<ADefaultHUD>(CharacterController->GetHUD());
		USkillUserWidget* UI_Skill = HUD->MainWidget->UI_Skill;
		UI_Skill->SetData(DataHandle);
	}
}


