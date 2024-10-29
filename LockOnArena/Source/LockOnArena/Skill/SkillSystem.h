// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SkillSystem.generated.h"


class ADefaultCharacter;
class AInGamePlayerController;
class UCharacterStateComponent;


class ASkillSystem;
USTRUCT()
struct LOCKONARENA_API FSkillSystemTableRow : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Category = "Skill")
	TSubclassOf<ASkillSystem> SkillSystemClass;

	UPROPERTY(EditAnywhere, Category = "Skill")
	float CoolDown;
};

UCLASS()
class LOCKONARENA_API ASkillSystem : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASkillSystem();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

public:
	virtual void SetData(const FDataTableRowHandle& InRowHandle);

public:
	// Input값만큼 RemainCooldown에서 빼기
	UFUNCTION()
	virtual void ReduceCooldown(float DeltaTime);

	UFUNCTION()
	virtual float GetRemainCooldown() { return RemainCoolDown; };

	UFUNCTION()
	virtual bool CanPlaySkill() { return bCanPlay; };	

	UFUNCTION()
	virtual void PlaySkill(const int SkillNum);

	 
protected:
	UPROPERTY()
	float CoolDown = 5.f; // CoolDown

	UPROPERTY()
	float RemainCoolDown = 0.f;

	UPROPERTY()
	bool bCanPlay = true;

protected:
	UPROPERTY()
	ADefaultCharacter* ControlledCharacter = nullptr;

	UPROPERTY()
	AInGamePlayerController* Controller = nullptr;

	UPROPERTY()
	UCharacterStateComponent* CharacterState = nullptr;
};


