// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Misc/Utils.h"

#include "CharacterStateComponent.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnCharacterStateChanged);

USTRUCT()
struct LOCKONARENA_API FCharacterStateTableRow : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Category = "CharacterState|Status")
	float MaxHp = 100.f;
	UPROPERTY(EditAnywhere, Category = "CharacterState|Status")
	float CharacterATK = 10.f;
	UPROPERTY(EditAnywhere, Category = "CharacterState|Status")
	int32 Level = 1.f;
	UPROPERTY(EditAnywhere, Category = "CharacterState|Status")
	float MaxExp = 50.f;
};




UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class LOCKONARENA_API UCharacterStateComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UCharacterStateComponent();

	UPROPERTY(BlueprintAssignable, Category = "Event")
	FOnCharacterStateChanged OnCharacterStateChanged;
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

	virtual bool GetLockOn() { return bLockOnSuccessed; }
	virtual void SetLockOn(const bool InValue);
	virtual void SetLockOnFalse();

	virtual bool GetLockOnPlaying() { return bLockOnPlay; }
	virtual void SetLockOnPlaying(const bool InValue) { bLockOnPlay = InValue; }


public:
	virtual void SetData(const FDataTableRowHandle& RowHandle);


public: // Status
	virtual int32 GetCharacterLevel() { return Level; }
	virtual void SetCharacterLevel(const int32 InLevel) { Level = InLevel; }

	virtual float GetCharacterATK() { return CharacterATK; }
	virtual void SetCharacterATK(const float InATK) { CharacterATK = InATK; }
	virtual void AddCharacterATK(const float InATK) { CharacterATK += InATK; }

	virtual float GetCurrentHp() { return CurrentHp; }
	virtual void HealCurrentHp(const float InHeal);
	virtual void ReduceHp(float InDamage);

	virtual float GetMaxHp() { return MaxHp; }
	virtual void SetMaxHp(const float InMaxHp) { MaxHp = InMaxHp; }
	virtual void AddMaxHp(const float InHp) { MaxHp += InHp; }

	virtual float GetMaxExp() { return MaxExp; }
	virtual void SetMaxExp(const float InMaxExp) { MaxExp = InMaxExp; }

	virtual float GetCurrentExp() { return CurrentExp; }
	virtual void SetCurrentExp(const float InExp) { CurrentExp = InExp; }

	virtual void AddExp(const float InExp);

	virtual bool CanUseShop() { return bCanShop; }
	virtual void SetUseShop(const bool InCanUseShop) { bCanShop = InCanUseShop; }

	virtual int32 GetStatPoint() { return StatPoint; }
	virtual void SetStatPoint(const int32 InStatPoint) { StatPoint = InStatPoint; }
public: 
	float CharacterATK = 10.f;
	float MaxHp = 100.f;
	float CurrentHp = 100.f;

public:
	virtual void LevelUp();

public:
	int32 StackLevel = 0;
	int32 StatPoint = 0;
protected:
	int32 Level = 1.f;
	float MaxExp = 50.f;
	float CurrentExp = 0.f;

	bool bCanShop = false;

public:
	virtual bool IsDie() { return bDied; }

	virtual bool IsSuperAmmo() { return bSuperAmmo; }
	FTimerHandle SuperAmmoTimerHandle;
	virtual void SetSuperAmmo(const float InSuperAmmoTime);
	virtual void OffSuperAmmo();

	virtual void SetCannotMove(const float InCannotMoveTime);
	virtual void OffCannotMove();
	FTimerHandle MoveTimerHandle;


public:
	bool CanLockOn = true; // 자세한 쿨타임은 skillsystem에서 관리

protected:
	bool bDied = false;
	bool bSuperAmmo = false;
	bool bCanMove = true;
	bool bCanAttack = true;


	WeaponType EquipmentType;



public:	// LockOn
	virtual void SetCD_LockOn(const float InCoolDown) { CD_LockOn = InCoolDown; }
	virtual float GetCD_LockOn() { return CD_LockOn; }

	virtual void SetCD_RemainLockOn(const float InRemainCoolDown) { CD_RemainLockOn = InRemainCoolDown; }
	virtual float GetCD_RemainLockOn() { return CD_RemainLockOn; }
	
	// SKill01
	virtual void SetCD_Skill01(const float InCoolMaxDown) { CD_Skill01 = InCoolMaxDown; }
	virtual float GetCD_Skill01() { return CD_Skill01; }

	virtual void SetCD_RemainSkill01(const float InRemainCoolDown) { CD_RemainSkill01 = InRemainCoolDown; }
	virtual float GetCD_RemainSkill01() { return CD_RemainSkill01; }
	

	virtual void SetTargetLocation(FVector InLocation) { TargetLocation = InLocation; }
	virtual FVector GetTargetLocation() { return TargetLocation; }

protected:	
	bool bLockOnSuccessed = false;
	bool bLockOnPlay = false;
	float CD_LockOn;
	float CD_RemainLockOn;
	
	float CD_Skill01;
	float CD_RemainSkill01;

	FVector TargetLocation;

protected:

};
