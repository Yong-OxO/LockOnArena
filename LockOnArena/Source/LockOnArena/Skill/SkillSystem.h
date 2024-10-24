// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SkillSystem.generated.h"


class ADefaultCharacter;
class AInGamePlayerController;

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


public:
	virtual bool LockOn();

protected:
	ADefaultCharacter* ControlledCharacter = nullptr;
	AInGamePlayerController* Controller = nullptr;

	UPROPERTY()
	float DetectionDist = 3000.f;

	UPROPERTY()
	TArray<FOverlapResult> OverlapResults;


};
