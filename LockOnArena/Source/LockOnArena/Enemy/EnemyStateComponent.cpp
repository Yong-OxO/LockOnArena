// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/EnemyStateComponent.h"

// Sets default values for this component's properties
UEnemyStateComponent::UEnemyStateComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	bDied = false;
	bCanMove = true;
	bCanAttack = true;
}


// Called when the game starts
void UEnemyStateComponent::BeginPlay()
{
	Super::BeginPlay();

	CurrentHp = MaxHp;	
}


// Called every frame
void UEnemyStateComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
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

