// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/CharacterStateComponent.h"

// Sets default values for this component's properties
UCharacterStateComponent::UCharacterStateComponent()
{

	PrimaryComponentTick.bCanEverTick = true;

	EquipmentType = WeaponType::NonWeapon;
}


// Called when the game starts
void UCharacterStateComponent::BeginPlay()
{
	Super::BeginPlay();

	
}


// Called every frame
void UCharacterStateComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

