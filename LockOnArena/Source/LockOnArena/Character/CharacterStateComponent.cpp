// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/CharacterStateComponent.h"
#include "GameFramework/Actor.h"

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

	if (bLockOnSuccessed)
	{
		UE_LOG(LogTemp, Display, TEXT("Is Lockon"));
	}
}

void UCharacterStateComponent::SetLockOn(const bool InValue)
{
	bLockOnSuccessed = true;

	FTimerHandle TimerHandle;

	GetWorld()->GetTimerManager().SetTimer(
		TimerHandle,   // FTimerHandle 변수
		this,          // 타이머를 설정할 객체
		&ThisClass::SetLockOnFalse, // 실행할 함수
		1.0f,          // 대기 시간(초 단위)
		false          // 반복 여부 (false면 한 번만 실행)
	);

	
}

void UCharacterStateComponent::SetLockOnFalse()
{
	bLockOnSuccessed = false;
	bCanMove = !bLockOnSuccessed;
}

