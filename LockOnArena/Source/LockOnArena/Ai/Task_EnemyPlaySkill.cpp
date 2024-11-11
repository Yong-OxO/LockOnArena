// Fill out your copyright notice in the Description page of Project Settings.


#include "Ai/Task_EnemyPlaySkill.h"
#include "AIController.h"
#include "Enemy/EnemyBase.h"
#include "Skill/Enemy/EnemySkillBase.h"

UTask_EnemyPlaySkill::UTask_EnemyPlaySkill()
{
	NodeName = "PlaySkill";
	bCreateNodeInstance = true;
	bTickIntervals = true;
	bNotifyTick = true;
}

void UTask_EnemyPlaySkill::SetOwner(AActor* InActorOwner)
{
	ActorOwner = InActorOwner;
	AIController = Cast<AAIController>(InActorOwner);
}

EBTNodeResult::Type UTask_EnemyPlaySkill::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	BehaviorTreeComponent = &OwnerComp;
	BlackboardComponent = OwnerComp.GetBlackboardComponent();

	AEnemyBase* Enemy = Cast<AEnemyBase>(AIController->GetPawn());

	UEnemySkillBase* Skill = Enemy->Skill01;
	if (Skill->CanPlaySkill())
	{
		Skill->PlaySkill();
		return EBTNodeResult::Succeeded;
	}

	return EBTNodeResult::InProgress;
}

void UTask_EnemyPlaySkill::OnMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
}
