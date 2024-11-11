// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "EnemySkillBase.generated.h"

class AEnemyBase;
class UEnemyStateComponent;

USTRUCT()
struct LOCKONARENA_API FEnemySkillBaseTableRow : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Category = "Skill|Animation")
	UAnimMontage* SkillMontage = nullptr;

public:
	UPROPERTY(EditAnywhere, Category = "Skill|State")
	float MaxCoolDown = 0.f;

	UPROPERTY(EditAnywhere, Category = "Skill|State")
	bool IsSuperAmmo = false;

	UPROPERTY(EditAnywhere, Category = "Skill|State")
	float DamagePercent = 100.f;

	UPROPERTY(EditAnywhere, Category = "Skill|State")
	float SuperAmmoTime = 0.f;
};


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class LOCKONARENA_API UEnemySkillBase : public UActorComponent
{
	GENERATED_BODY()

public:	
	UEnemySkillBase();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION()
	virtual void SetData(const FDataTableRowHandle& InHandle);

public:
	virtual bool CanPlaySkill();
	virtual void PlaySkill();

	UFUNCTION()
	virtual void ReduceCooldown(float DeltaTime);

protected:
	AEnemyBase* ControlledEnemy = nullptr;
	UEnemyStateComponent* EnemyState = nullptr;

public:
	FEnemySkillBaseTableRow* DataRow = nullptr;

	UPROPERTY(EditAnywhere, Category = "Enemy|Animation")
	UAnimMontage* SkillMontage = nullptr;

protected:
	UPROPERTY()
	float MaxCooldown = 0.f;

	UPROPERTY()
	float RemainCoolDown = 0.f;

	bool bCanPlay = true;

	float DamagePercent = 100.f;
};
