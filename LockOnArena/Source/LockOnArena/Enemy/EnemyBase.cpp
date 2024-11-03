// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/EnemyBase.h"
#include "Actor/Weapon/WeaponChildActorComponent.h"
#include "Enemy/EnemyStateComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Enemy/Animation/EnemyAnimInstance.h"

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
	UE_LOG(LogTemp, Display, TEXT("Take Damage!"));

	EnemyState->ReduceHp(Damage);

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

