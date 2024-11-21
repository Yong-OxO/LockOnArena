// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/EnemyBase.h"
#include "Actor/Weapon/WeaponChildActorComponent.h"
#include "Enemy/EnemyStateComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Enemy/Animation/EnemyAnimInstance.h"
#include "Character/DefaultCharacter.h"
#include "Character/CharacterStateComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Skill/Enemy/EnemySkillBase.h"
#include "Actor/Trigger/BossClearPortal.h"

// Sets default values
AEnemyBase::AEnemyBase()
{
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UDataTable> DataTableAsset(TEXT("/Script/Engine.DataTable'/Game/Blueprint/Data/Enemy/DT_EnemyBase.DT_EnemyBase'"));
	DataTable = DataTableAsset.Object;
	DataTableRow = DataTable->FindRow<FEnemyBaseTableRow>(FName("Defualt"), TEXT("EnemyDataTableRow"));
	{
		EnemyState = CreateDefaultSubobject<UEnemyStateComponent>(TEXT("EnemyState"));
	}
	{
		Skill01 = CreateDefaultSubobject<UEnemySkillBase>(TEXT("Skill01"));
		Skill02 = CreateDefaultSubobject<UEnemySkillBase>(TEXT("Skill02"));
		Skill03 = CreateDefaultSubobject<UEnemySkillBase>(TEXT("Skill03"));
		Skills.Add(Skill01);
		Skills.Add(Skill02);
		Skills.Add(Skill03);
	}
}

// Called when the game starts or when spawned
void AEnemyBase::BeginPlay()
{
	Super::BeginPlay();

	USkeletalMeshComponent* MeshComponent = GetComponentByClass<USkeletalMeshComponent>();
	AnimInstance = Cast<UEnemyAnimInstance>(MeshComponent->GetAnimInstance());
	AnimInstance->OnMontageEnded.AddDynamic(this, &ThisClass::OnMontageEnd);
	{
		Skills[0]->SetData(DataTableRow->Skill01);
		Skills[1]->SetData(DataTableRow->Skill02);
		Skills[2]->SetData(DataTableRow->Skill03);
	}

	AnimInstance->Montage_Play(DataTableRow->InitMontage);
}

// Called every frame
void AEnemyBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AEnemyBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}


float AEnemyBase::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	if (EnemyState->IsDie()) { return 0.f; }

	ADefaultCharacter* CauserPlayer = Cast<ADefaultCharacter>(DamageCauser->GetOwner());

	if (CauserPlayer == nullptr) // 발사체 등 Weapon이 직접적인 피해를 주지 않을 때
	{
		CauserPlayer = Cast<ADefaultCharacter>(DamageCauser->GetOwner()->GetOwner());
	}

	EnemyState->ReduceHp(Damage);
	CauserPlayer->VisibleEnemyHpBar(this);

	if (EnemyState->IsDie()) // 최초 사망판정시
	{
		SetActorEnableCollision(false);
		if (Controller) { Controller->StopMovement(); }

		UCharacterStateComponent* CauserPlayerState = CauserPlayer->GetState();
		CauserPlayerState->AddExp(GetState()->EnemyEXP);
		CauserPlayerState->SetUseShop(true);
		ClearPortal->ActivePortal();
		

		AnimInstance->StopAllMontages(0.f);
		AnimInstance->Montage_Play(DataTableRow->DeathMontage);

		// 다른 Montage 재생중 Die가 발생하면 기존 Montage가 종료되면서 OnMontageEnd가 실행되므로 따로 관리가 필요하다.
		GetWorld()->GetTimerManager().SetTimer(
			TimerHandle,
			this,
			&ThisClass::OnDIe,
			DataTableRow->DeathMontage->GetPlayLength() - 0.2f,
			false);

		return Damage;
	}
	
	StackDamage += Damage;

	if (StackDamage >= 100.f && !EnemyState->IsSuperAmmo()) // 일정 이상의 데미지가 누적되면 Montage 재생
	{
		StackDamage = FMath::Fmod(StackDamage, 100.f);

		Controller->StopMovement();

		AnimInstance->StopAllMontages(0.f);
		AnimInstance->Montage_Play(DataTableRow->HitMontage);
	}

	return Damage;
}

void AEnemyBase::OnMontageEnd(UAnimMontage* Montage, bool bInterrupted)
{
	int a = 0;
}

void AEnemyBase::OnDIe()
{
	Destroy();
}

