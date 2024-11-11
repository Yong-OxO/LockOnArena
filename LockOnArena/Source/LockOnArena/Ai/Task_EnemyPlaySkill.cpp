// Fill out your copyright notice in the Description page of Project Settings.


#include "Ai/Task_EnemyPlaySkill.h"

EBTNodeResult::Type UTask_EnemyPlaySkill::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	UE_LOG(LogTemp, Display, TEXT("Success"));
	// 스킬 쿨타임인지 확인


	return EBTNodeResult::InProgress;
}

void UTask_EnemyPlaySkill::OnMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
}
