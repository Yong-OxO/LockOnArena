// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/BaseAIController.h"
#include "Components/SkeletalMeshComponent.h"
#include "BehaviorTree/BlackboardComponent.h"


void ABaseAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	APawn* OwningPawn = GetPawn();

	if (Blackboard)
	{
		bool bIsMontagePlaying = OwningPawn->GetComponentByClass<USkeletalMeshComponent>()->GetAnimInstance()->IsAnyMontagePlaying();
		Blackboard->SetValueAsBool(TEXT("MontageIsPlaying"), bIsMontagePlaying);
	}
}
