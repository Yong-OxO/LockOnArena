// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SkillBase.generated.h"

USTRUCT()
struct LOCKONARENA_API FSkillBaseTableRow : public FTableRowBase
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, Category = "Skill")
	float CoolDown;
};


class ADefaultCharacter;
class AInGamePlayerController;
class UCharacterStateComponent;


UCLASS()
class LOCKONARENA_API ASkillBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASkillBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
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
