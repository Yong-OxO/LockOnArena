// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/Weapon/Enemy/EnemyWeaponBase.h"

// Sets default values
AEnemyWeaponBase::AEnemyWeaponBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AEnemyWeaponBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEnemyWeaponBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

