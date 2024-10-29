// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SkillSystem.generated.h"





class ASkillSystem;
USTRUCT()
struct LOCKONARENA_API FSkillSystemTableRow : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Category = "Skill")
	TSubclassOf<ASkillSystem> SkillSystemClass;
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
};


