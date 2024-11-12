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

	int32 SkillNum = Enemy->Skills.Num();
	int32 PlaySkillNum = FMath::RandRange(0, SkillNum - 1);

	for (int i = 0; i < SkillNum; ++i)
	{	
		UEnemySkillBase* Skill = Enemy->Skills[PlaySkillNum];
		if (Skill->CanPlaySkill())
		{
			Skill->PlaySkill();
			return EBTNodeResult::Succeeded;
		}

		PlaySkillNum = (PlaySkillNum + 1) % SkillNum;
	}

	return EBTNodeResult::Failed;
}

void UTask_EnemyPlaySkill::OnMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
}
