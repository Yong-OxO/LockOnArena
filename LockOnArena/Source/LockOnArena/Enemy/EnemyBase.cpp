// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/EnemyBase.h"
#include "Actor/Weapon/WeaponChildActorComponent.h"
#include "Enemy/EnemyStateComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Enemy/Animation/EnemyAnimInstance.h"
#include "Character/DefaultCharacter.h"
#include "Character/CharacterStateComponent.h"

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
}

// Called when the game starts or when spawned
void AEnemyBase::BeginPlay()
{
	Super::BeginPlay();

	USkeletalMeshComponent* MeshComponent = GetComponentByClass<USkeletalMeshComponent>();
	AnimInstance = Cast<UEnemyAnimInstance>(MeshComponent->GetAnimInstance());
	AnimInstance->OnMontageEnded.AddDynamic(this, &ThisClass::OnMontageEnd);
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

void AEnemyBase::SetData(const FDataTableRowHandle& InRowHandle)
{
	int a = 10;
}

float AEnemyBase::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	if (FMath::IsNearlyZero(EnemyState->CurrentHp)) { return 0; }

	EnemyState->ReduceHp(Damage);

	if (EnemyState->CurrentHp <= 0)
	{
		// 죽음 몽타주 실행 및 플레이어 경험치 오르기, Collision 끄기 등
		ADefaultCharacter* CauserPlayer = Cast<ADefaultCharacter>(DamageCauser->GetOwner());
		if (CauserPlayer == nullptr)
		{
			CauserPlayer = Cast<ADefaultCharacter>(DamageCauser->GetOwner()->GetOwner());
		}
		UCharacterStateComponent* CauserPlayerState = CauserPlayer->GetState();
		CauserPlayerState->AddExp(GetState()->EnemyEXP);
		EnemyState->CurrentHp = 0;
		return Damage;
	}

	StackDamage += Damage;

	if (StackDamage >= 100.f) // 일정 이상의 데미지가 누적되면 Montage 재생
	{
		StackDamage = FMath::Fmod(StackDamage, 100.f);

		AnimInstance->StopAllMontages(0.f);
		AnimInstance->Montage_Play(DataTableRow->HitMontage);
	}

	return Damage;
}

void AEnemyBase::OnMontageEnd(UAnimMontage* Montage, bool bInterrupted)
{
	int a = 0;
}

