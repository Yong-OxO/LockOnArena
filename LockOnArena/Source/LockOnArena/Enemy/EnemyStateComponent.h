// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Misc/Utils.h"

#include "EnemyStateComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class LOCKONARENA_API UEnemyStateComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UEnemyStateComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	virtual  bool CanAttack() const { return bCanAttack; }
	virtual  bool CanMove() const { return bCanMove; }

	virtual void SetAttack(const bool InbAttack) { bCanAttack = InbAttack; }
	virtual void SetCanMove(const bool InbMove) { bCanMove = InbMove; }

	virtual WeaponType GetEquipmentType() { return EquipmentType; }
	virtual void SetEquipmentType(const WeaponType InNum) { EquipmentType = InNum; }

	virtual void ReduceHp(const float Damage);


public:
	virtual float GetMaxHp() { return MaxHp; }
	virtual float GetCurrentHp() { return CurrentHp; }

public:
	float MaxHp = 300.f;
	float CurrentHp = 300.f;
	
	float EnemyEXP = 100.f;
protected:
	bool bCanMove = true;
	bool bCanAttack = true;

	WeaponType EquipmentType;
};
