// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "Task_EnemyPlaySkill.generated.h"

/**
 * 
 */
UCLASS()
class LOCKONARENA_API UTask_EnemyPlaySkill : public UBTTaskNode
{
	GENERATED_BODY()

public:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	virtual void OnMontageEnded(UAnimMontage* Montage, bool bInterrupted);
};
