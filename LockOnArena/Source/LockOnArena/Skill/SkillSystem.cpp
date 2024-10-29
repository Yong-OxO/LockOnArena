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

	if (RemainCoolDown > 0.f)
	{
		ReduceCooldown(DeltaTime);
	}
}

void ASkillSystem::SetData(const FDataTableRowHandle& InRowHandle)
{
	FSkillSystemTableRow* TableRow = InRowHandle.GetRow<FSkillSystemTableRow>(TEXT("TableRow"));

	CoolDown = TableRow->CoolDown;

	ControlledCharacter = GetOwner<ADefaultCharacter>();
	Controller = CastChecked<AInGamePlayerController>(ControlledCharacter->GetController());
	CharacterState = ControlledCharacter->GetState();
}


void ASkillSystem::PlaySkill(const int SkillNum)
{
	if (RemainCoolDown > 0)
	{
		UE_LOG(LogTemp, Display, TEXT("Cooldown"));
		bCanPlay = false;
		return;
	}

	RemainCoolDown = CoolDown;
}




void ASkillSystem::ReduceCooldown(float DeltaTime)
{
	RemainCoolDown -= DeltaTime;

	if (RemainCoolDown <= 0)
	{
		bCanPlay = true;
	}
	CharacterState->SetCD_RemainLockOn(RemainCoolDown);
}

