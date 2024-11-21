// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Misc/Utils.h"

#include "EnemyStateComponent.generated.h"


USTRUCT()
struct LOCKONARENA_API FEnemyStateTableRow : public FTableRowBase
{
	GENERATED_BODY()

public: // Status
	UPROPERTY(EditAnywhere, Category = "Enemy|Status")
	float MaxHp = 100.f;
	UPROPERTY(EditAnywhere, Category = "Enemy|Status")
	float EnemyATK = 10.f;
	UPROPERTY(EditAnywhere, Category = "Enemy|Status")
	float EnemyEXP = 100.f;
};

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

	virtual bool IsDie() { return bDied; }

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

	virtual float GetATK() { return ATK; }
protected:
	virtual void SetState(const FEnemyStateTableRow* DataTableRow);

public:
	UPROPERTY(EditAnywhere, meta = (RowType = "/Script/LOCKONARENA.EnemyStateTableRow"))
	FDataTableRowHandle CharacterStateTableRowHandle;

	FEnemyStateTableRow* DataTableRow;
public:
	float MaxHp = 100.f;
	float CurrentHp = 100.f;
	
	float EnemyEXP = 100.f;
	float ATK = 10.f;

public:
	virtual bool IsSuperAmmo() { return bSuperAmmo; }
	FTimerHandle SuperAmmoTimerHandle;
	virtual void SetSuperAmmo(const float InSuperAmmoTime);
	virtual void OffSuperAmmo();

protected:
	bool bDied = false;
	bool bSuperAmmo = false;
	bool bCanMove = true;
	bool bCanAttack = true;


	WeaponType EquipmentType;
};
