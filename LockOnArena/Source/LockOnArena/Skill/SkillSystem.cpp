// Fill out your copyright notice in the Description page of Project Settings.


#include "Skill/SkillSystem.h"
#include "Character/DefaultCharacter.h"
#include "Character/InGamePlayerController.h"
#include "Character/CharacterStateComponent.h"


// Sets default values
ASkillSystem::ASkillSystem()
{
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

void ASkillSystem::SetData(const FDataTableRowHandle& InRowHandle)
{
	int a = 0;

}





