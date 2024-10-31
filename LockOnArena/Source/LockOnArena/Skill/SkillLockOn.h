// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Skill/SkillSystem.h"
#include "SkillLockOn.generated.h"

/**
 * 
 */
UCLASS()
class LOCKONARENA_API ASkillLockOn : public ASkillSystem
{
	GENERATED_BODY()
	
protected:
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(EditAnywhere, Category = "Rotation")
	FRotator ToTargetRotation;

public:

	UFUNCTION()
	virtual void StartLockOnPlay();

	UFUNCTION()
	virtual void StopLockOnPlay();

	virtual void LockOn(const float DeltaTime);

protected:
	virtual void SetData(const FDataTableRowHandle& InRowHandle) override;

protected:

	UPROPERTY()
	float DetectionDist = 3000.f; // 탐지거리

	UPROPERTY()
	bool bIsLocking = false; // LockOn이 실행중

	bool Overlap = false;


	UPROPERTY()
	TArray<FOverlapResult> OverlapResults;


protected:
	UFUNCTION()
	virtual void CheckLockOn();
	bool bLockOnSucceed; // LockOn이 끝났을때 에임이 조준 되어있는지

	FTimerHandle TimerHandle;
};
