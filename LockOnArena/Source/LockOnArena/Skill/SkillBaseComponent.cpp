// Fill out your copyright notice in the Description page of Project Settings.


#include "Skill/SkillBaseComponent.h"
#include "Animation/AnimMontage.h"

// Sets default values for this component's properties
USkillBaseComponent::USkillBaseComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void USkillBaseComponent::BeginPlay()
{
	Super::BeginPlay();

	AActor* Temp = GetOwner();
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
	UE_LOG(LogTemp, Display, TEXT("Play Skill"));

	if (RemainCoolDown > 0)
	{
		UE_LOG(LogTemp, Display, TEXT("Cooldown"));
		bCanPlay = false;
		return;
	}

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
	DataRow = InHandle.GetRow<FSkillBaseTableRow>(TEXT("DataRow"));

	MaxCooldown = DataRow->MaxCoolDown;
	bSuperAmmo = DataRow->IsSuperAmmo;
	SuperAmmoTime = DataRow->SuperAmmoTime;
}

