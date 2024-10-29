// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Skill/SkillSystem.h"
#include "RifleSkillSystem.generated.h"


class ASkillSystem;
USTRUCT()
struct LOCKONARENA_API FRifleSkillSystemTableRow : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Category = "Skill")
	ASkillSystem* LockOn;

	UPROPERTY(EditAnywhere, Category = "Skill")
	ASkillSystem* Skill01;
};

UCLASS()
class LOCKONARENA_API ARifleSkillSystem : public ASkillSystem
{
	GENERATED_BODY()

public:
	ARifleSkillSystem();

public:
	virtual void PlaySkill(const int SkillNum) override;


};
