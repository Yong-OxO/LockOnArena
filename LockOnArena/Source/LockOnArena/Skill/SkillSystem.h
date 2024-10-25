// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SkillSystem.generated.h"


class ADefaultCharacter;
class AInGamePlayerController;
class UCharacterStateComponent;

UCLASS()
class LOCKONARENA_API ASkillSystem : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASkillSystem();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, Category = "Rotation")
	FRotator ToTargetRotation;
public:
	UFUNCTION()
	virtual void StartLockOnPlay();

	UFUNCTION()
	virtual void StopLockOnPlay();

	virtual void LockOn(const float DeltaTime);


protected:
	UPROPERTY()
	ADefaultCharacter* ControlledCharacter = nullptr;
	UPROPERTY()
	AInGamePlayerController* Controller = nullptr;
	UPROPERTY()
	UCharacterStateComponent* CharacterState = nullptr;

	UPROPERTY()
	float DetectionDist = 3000.f; // 탐지거리

	UPROPERTY()
	bool bIsPlaying = false; // LockOn이 실행중



	UPROPERTY()
	TArray<FOverlapResult> OverlapResults;


protected:
	UFUNCTION()
	virtual void CheckLockOn();
	bool bLockOnSucceed; // LockOn이 끝났을때 에임이 조준 되어있는지

	FTimerHandle TimerHandle;


protected: // 쿨타임 관리
	UFUNCTION()
	virtual void LockOnCoolDown(float DeltaTime);

	UPROPERTY()
	float CD_LockOn = 5.f; // CoolDown

	UPROPERTY()
	float CD_RemainLockOn = 0.f;
};


