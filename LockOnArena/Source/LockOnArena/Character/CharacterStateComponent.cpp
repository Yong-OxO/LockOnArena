// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/CharacterStateComponent.h"
#include "GameFramework/Actor.h"

// Sets default values for this component's properties
UCharacterStateComponent::UCharacterStateComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	EquipmentType = WeaponType::NonWeapon;
	
	// @TODO : RowName namespace
	static ConstructorHelpers::FObjectFinder<UDataTable> DataTableAsset(TEXT("/Script/Engine.DataTable'/Game/Blueprint/Character/DT_CharacterState.DT_CharacterState'"));
	UDataTable* DataTable = DataTableAsset.Object;
	FCharacterStateTableRow* DataTableRow = DataTable->FindRow<FCharacterStateTableRow>(FName("Default"), TEXT("CharacterState DataTableRow"));

	MaxHp = DataTableRow->MaxHp;
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


}

void UCharacterStateComponent::SetLockOn(const bool InValue)
{
	bLockOnSuccessed = InValue;

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

void UCharacterStateComponent::SetData(const FDataTableRowHandle& RowHandle)
{
	int a = 0;
	//RowHandle.GetRow<>();
}

