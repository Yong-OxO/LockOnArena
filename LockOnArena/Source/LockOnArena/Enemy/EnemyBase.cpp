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

	ADefaultCharacter* CauserPlayer = Cast<ADefaultCharacter>(DamageCauser->GetOwner());
	if (CauserPlayer == nullptr) // 발사체 등 Weapon이 직접적인 피해를 주지 않을 때
	{
		CauserPlayer = Cast<ADefaultCharacter>(DamageCauser->GetOwner()->GetOwner());
	}

	CauserPlayer->VisibleEnemyHpBar(this);

	// @TODO : Enemy State에서 Die를 관리하고 Die인지 아닌지로 체크
	// 최초의 die라면 Collision을 꺼둠으로써 더 이상의 TakeDamage가 호출되지 않도록

	if (FMath::IsNearlyZero(EnemyState->CurrentHp))
	{
		// 죽음 몽타주 실행 및 플레이어 경험치 오르기, Collision 끄기 등
	
		UCharacterStateComponent* CauserPlayerState = CauserPlayer->GetState();
		CauserPlayerState->AddExp(GetState()->EnemyEXP);
		EnemyState->CurrentHp = 0;

		AnimInstance->StopAllMontages(0.f);
		AnimInstance->Montage_Play(DataTableRow->DeathMontage);

		return Damage;
	}
	
	StackDamage += Damage;

	if (StackDamage >= 100.f) // 일정 이상의 데미지가 누적되면 Montage 재생
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
	//Controller->Movement();
}

