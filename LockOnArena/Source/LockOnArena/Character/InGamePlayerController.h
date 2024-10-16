// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "InGamePlayerController.generated.h"

class UInputMappingContext;
class UAction;
struct FInputActionValue;
class ADefaultCharacter;
class UCharacterMovementComponent;

USTRUCT()
struct LOCKONARENA_API FCharacterControllerTableRow : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = "IMC")
	UInputMappingContext* InputMappingContext = nullptr;
};



UCLASS()
class LOCKONARENA_API AInGamePlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AInGamePlayerController();
protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

	//virtual void OnPossess(APawn* InPawn);
	

protected:
	UInputMappingContext* IMC_Default = nullptr;

	UFUNCTION()
	virtual void OnMove(const FInputActionValue& InValue);

	UFUNCTION()
	virtual void OnLook(const FInputActionValue& InValue);

	UFUNCTION()
	virtual void OnJump(const FInputActionValue& InValue);

	UFUNCTION()
	virtual void OnStopJump(const FInputActionValue& InValue);


protected:
	float MoveForwardSpeed = 1.0f;
	float MoveBackwardSpeed = 0.7f;
	float MoveRightSpeed = 0.8f;

public:
	UPROPERTY(EditAnywhere)
	float Sensitivity = 1.0f;


protected:
	//UPROPERTY(EditAnywhere, meta = (RowType = "/Script/KDT3D.WeaponTableRow"))

	UDataTable* DataTable = nullptr;
	// Controller 상태 변경시 TableRow도 변경 필요
	const FCharacterControllerTableRow* ControllerTableRow = nullptr;
	ADefaultCharacter* ControlledCharacter = nullptr;

	UCharacterMovementComponent* CharacterMovement;
};
