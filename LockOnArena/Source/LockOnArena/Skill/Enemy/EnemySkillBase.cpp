// Fill out your copyright notice in the Description page of Project Settings.


#include "Skill/Enemy/EnemySkillBase.h"
#include "Enemy/EnemyBase.h"
#include "Enemy/EnemyStateComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Enemy/Animation/EnemyAnimInstance.h"

UEnemySkillBase::UEnemySkillBase()
{
	PrimaryComponentTick.bCanEverTick = true;

}


// Called when the game starts
void UEnemySkillBase::BeginPlay()
{
	Super::BeginPlay();	
}


void UEnemySkillBase::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);


	if (RemainCoolDown > 0.f)
	{
		ReduceCooldown(DeltaTime);
	}
}

void UEnemySkillBase::SetData(const FDataTableRowHandle& InHandle)
{
	// EnemyBase의 BeginPlay에서 실행
	DataRow = InHandle.GetRow<FEnemySkillBaseTableRow>(TEXT("DataRow"));

	SkillMontage = DataRow->SkillMontage;
	MaxCooldown = DataRow->MaxCoolDown;
	DamagePercent = DataRow->DamagePercent;
}

bool UEnemySkillBase::CanPlaySkill()
{
	ControlledEnemy = GetOwner<AEnemyBase>();
	EnemyState = ControlledEnemy->GetState();

	UEnemyAnimInstance* AnimInstance = ControlledEnemy->AnimInstance;

	if (FMath::IsNearlyZero(RemainCoolDown) && !AnimInstance->IsAnyMontagePlaying())
	{
		return true;
	}
	return false;
}

void UEnemySkillBase::PlaySkill()
{
	ControlledEnemy = GetOwner<AEnemyBase>();
	EnemyState = ControlledEnemy->GetState();

	if (!CanPlaySkill()) { return; }

	if (RemainCoolDown > 0.f)	{ return; }

	UAnimInstance* AnimInstance = ControlledEnemy->GetMesh()->GetAnimInstance();
	if (SkillMontage)
	{
		AnimInstance->Montage_Play(SkillMontage);
		RemainCoolDown = MaxCooldown;

		if (DataRow->IsSuperAmmo)
		{
			EnemyState->SetSuperAmmo(DataRow->SuperAmmoTime);
		}
	}
}

void UEnemySkillBase::ReduceCooldown(float DeltaTime)
{
	RemainCoolDown -= DeltaTime;

	if (RemainCoolDown <= 0)
	{
		RemainCoolDown = 0;
		bCanPlay = true;
	}
	//CharacterState->SetCD_RemainLockOn(RemainCoolDown);
}

