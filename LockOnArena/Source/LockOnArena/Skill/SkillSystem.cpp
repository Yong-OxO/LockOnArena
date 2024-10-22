// Fill out your copyright notice in the Description page of Project Settings.


#include "Skill/SkillSystem.h"

// Sets default values
ASkillSystem::ASkillSystem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASkillSystem::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASkillSystem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASkillSystem::LockOn()
{
	UE_LOG(LogTemp, Display, TEXT("LockOn"));

	
	AActor* TempOwner = GetOwner(); // Owner의 class는 DefaultCharacter, WeaponBase에서 설정
}

