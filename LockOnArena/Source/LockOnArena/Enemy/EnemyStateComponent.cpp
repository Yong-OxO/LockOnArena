// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/EnemyStateComponent.h"

// Sets default values for this component's properties
UEnemyStateComponent::UEnemyStateComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	//bDied = false;
	//bCanMove = true;
	//bCanAttack = true;

	static ConstructorHelpers::FObjectFinder<UDataTable> DataTableAsset(TEXT("/Script/Engine.DataTable'/Game/Blueprint/Data/Enemy/DT_EnemyState.DT_EnemyState'"));
	DataTable = DataTableAsset.Object;
	DataTableRow = DataTable->FindRow<FEnemyStateTableRow>(FName("SilverDevil"), TEXT("EnemyStateDataTableRow"));
}


// Called when the game starts
void UEnemyStateComponent::BeginPlay()
{
	Super::BeginPlay();

	SetState(DataTableRow);
}


// Called every frame
void UEnemyStateComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UEnemyStateComponent::ReduceHp(const float Damage)
{
	if (bDied) { return; }

	CurrentHp -= Damage;

	if (CurrentHp <= 0)
	{
		CurrentHp = 0;
		bDied = true;
	}

	UE_LOG(LogTemp, Display, TEXT("CurrnetHp : %.1f"), CurrentHp);
}

void UEnemyStateComponent::SetState(const FEnemyStateTableRow* InDataTableRow)
{
	MaxHp = InDataTableRow->MaxHp;
	CurrentHp = MaxHp;

	EnemyEXP = InDataTableRow->EnemyEXP;
	ATK = InDataTableRow->EnemyATK;
}

