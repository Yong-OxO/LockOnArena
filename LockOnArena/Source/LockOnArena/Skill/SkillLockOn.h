// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Skill/SkillBaseComponent.h"
#include "SkillLockOn.generated.h"

USTRUCT()
struct LOCKONARENA_API FLockOnTableRow : public FSkillBaseTableRow
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Category = "Skill|LockOn")
	float DetectionDist = 0;
};


UCLASS()
class LOCKONARENA_API USkillLockOn : public USkillBaseComponent
{
	GENERATED_BODY()
	
public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	virtual void SetData(const FDataTableRowHandle& InHandle) override;

public:
	virtual void PlaySkill() override;

protected:

	UFUNCTION()
	virtual void StartLockOnPlay();

	UFUNCTION()
	virtual void StopLockOnPlay();

	virtual void LockOn(const float DeltaTime);

	UFUNCTION()
	virtual void CheckLockOn();

protected:
	float DetectionDist = 0;

	UPROPERTY()
	bool bIsLocking = false; // LockOn이 실행중

	bool Overlap = false;
	UPROPERTY()
	TArray<FOverlapResult> OverlapResults;

	bool bLockOnSucceed; // LockOn이 끝났을때 에임이 조준 되어있는지

	FTimerHandle TimerHandle;
};
