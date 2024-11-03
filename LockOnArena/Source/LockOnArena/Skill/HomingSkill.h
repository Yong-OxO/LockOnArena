// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Skill/SkillBaseComponent.h"
#include "HomingSkill.generated.h"

// 1. 캐릭터 State에서 LcokOn상태 확인
// 2. LcokOn중일때만 활성화
// 3. Target, 즉 호밍지점 -> CharacterState에서 저장?
// 4. TargetSocket을 저장?
// 4. TargetSocket 위치로 Homming

class AHomingProjectile;

USTRUCT()
struct LOCKONARENA_API FHomingTableRow : public FSkillBaseTableRow
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Category = "Skill|Homing")
	float SkillATKPersent = 0;

public:
	UPROPERTY(EditAnywhere, Category = "Skill|Homing")
	TSubclassOf<AHomingProjectile> ProjectileClass;
};

UCLASS()
class LOCKONARENA_API UHomingSkill : public USkillBaseComponent
{
	GENERATED_BODY()

public:

	virtual void SetData(const FDataTableRowHandle& InHandle) override;

public:
	virtual void PlaySkill() override;

	bool PlayHoming(const FVector TargetLocation);
protected:


	UPROPERTY()
	bool bIsLocking = false; // LockOn이 실행중

	float SkillATKPersent = 0;

	FHomingTableRow* DataTableRow;
};
