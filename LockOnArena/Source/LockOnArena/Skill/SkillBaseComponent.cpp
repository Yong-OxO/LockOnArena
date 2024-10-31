// Fill out your copyright notice in the Description page of Project Settings.


#include "Skill/SkillBaseComponent.h"
#include "Animation/AnimMontage.h"

// Sets default values for this component's properties
USkillBaseComponent::USkillBaseComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
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

	// ...
}

void USkillBaseComponent::PlaySkill(const int SkillNum)
{
}

void USkillBaseComponent::SetData(const FDataTableRowHandle& InHandle)
{
}

