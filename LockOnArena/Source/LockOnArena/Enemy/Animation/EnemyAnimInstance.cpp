// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/Animation/EnemyAnimInstance.h"
#include "GameFramework/PawnMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"


void UEnemyAnimInstance::NativeInitializeAnimation()
{
	Pawn = TryGetPawnOwner();
	if (Pawn)
	{
		MovementComponent = Pawn->GetMovementComponent();
	}
}

void UEnemyAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (!MovementComponent)
	{
		//ensureMsgf(false, TEXT("MovementComponent is null"));
		return;
	}

	Speed = UKismetMathLibrary::VSizeXY(MovementComponent->Velocity);
	Speed > 3.f ? bMove = true : bMove = false;

	bIsCrouch = MovementComponent->IsCrouching();
	bIsFalling = MovementComponent->IsFalling();

	Angle = CalculateDirection(MovementComponent->Velocity, Pawn->K2_GetActorRotation());
}
