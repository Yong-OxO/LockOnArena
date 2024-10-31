// Fill out your copyright notice in the Description page of Project Settings.


#include "Skill/SkillBaseComponent.h"
#include "Animation/AnimMontage.h"
#include "Character/DefaultCharacter.h"
#include "Character/InGamePlayerController.h"
#include "Character/CharacterStateComponent.h"

// Sets default values for this component's properties
USkillBaseComponent::USkillBaseComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void USkillBaseComponent::BeginPlay()
{
	Super::BeginPlay();
}




// Called every frame
void USkillBaseComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (RemainCoolDown > 0.f)
	{
		ReduceCooldown(DeltaTime);
	}
}

void USkillBaseComponent::PlaySkill()
{
	Weapon = GetOwner<AWeaponBase>();
	ControlledCharacter = Weapon->GetOwner<ADefaultCharacter>(); // Owner는 Weapon, Weapon의 Owner는 Character
	Controller = ControlledCharacter->GetController<AInGamePlayerController>();
	CharacterState = ControlledCharacter->GetState();

	if (bCanPlay == false)
	{
		return;
	}

	if (RemainCoolDown > 0)
	{
		UE_LOG(LogTemp, Display, TEXT("Cooldown"));
		bCanPlay = false;
		return;
	}
	UE_LOG(LogTemp, Display, TEXT("Play Skill"));
	RemainCoolDown = MaxCooldown;
}

void USkillBaseComponent::ReduceCooldown(float DeltaTime)
{
	RemainCoolDown -= DeltaTime;

	if (RemainCoolDown <= 0)
	{
		RemainCoolDown = 0;
		bCanPlay = true;
	}
	//CharacterState->SetCD_RemainLockOn(RemainCoolDown);
}

void USkillBaseComponent::SetData(const FDataTableRowHandle& InHandle)
{
	FSkillBaseTableRow* DataRow = InHandle.GetRow<FSkillBaseTableRow>(TEXT("DataRow"));

	MaxCooldown = DataRow->MaxCoolDown;
	bSuperAmmo = DataRow->IsSuperAmmo;
	SuperAmmoTime = DataRow->SuperAmmoTime;
}

