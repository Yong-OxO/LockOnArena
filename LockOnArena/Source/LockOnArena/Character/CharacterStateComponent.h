// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Misc/Utils.h"

#include "CharacterStateComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class LOCKONARENA_API UCharacterStateComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UCharacterStateComponent();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	virtual  bool CanAttack() const { return bCanAttack; }
	virtual  bool CanMove() const { return bCanMove; }
	
	virtual void SetAttack(const bool InbAttack) { bCanAttack = InbAttack; }
	virtual void SetCanMove(const bool InbMove) { bCanMove = InbMove; }

	virtual WeaponType GetEquipmentType() { return EquipmentType; }
	virtual void SetEquipmentType(const WeaponType InNum) { EquipmentType = InNum; }

	virtual bool GetLockOn() { return bLockOn; }
	virtual void SetLockOn(const bool InValue);
	virtual void SetLockOnFalse();

	virtual bool GetLockOnPlaying() { return bLockOnPlay; }
	virtual void SetLockOnPlaying(const bool InValue) { bLockOnPlay = InValue; }


public:
	float MaxHp = 100.f;
	float CurrentHp = 100.f;

	bool CanLockOn = true; // 자세한 쿨타임은 skillsystem에서 관리

protected:
	bool bCanMove = true;
	bool bCanAttack = true;


	WeaponType EquipmentType;

	// LockOn
	bool bLockOn = false;
	bool bLockOnPlay = false;
};
