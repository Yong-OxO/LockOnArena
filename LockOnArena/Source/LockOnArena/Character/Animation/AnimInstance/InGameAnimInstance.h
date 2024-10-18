// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "InGameAnimInstance.generated.h"


class UPawnMovementComponent;

UCLASS()
class LOCKONARENA_API UInGameAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	UPawnMovementComponent* MovementComponent = nullptr;
	APawn* Pawn = nullptr;
public:
	UPROPERTY(BlueprintReadOnly)
	double Speed = 0.0;

	UPROPERTY(BlueprintReadOnly)
	double Angle = 0.0;

	UPROPERTY(BlueprintReadOnly)
	bool bMove = false;

	UPROPERTY(BlueprintReadOnly)
	bool bIsCrouch = false;

	UPROPERTY(BlueprintReadOnly)
	bool bIsFalling = false;
public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
};
