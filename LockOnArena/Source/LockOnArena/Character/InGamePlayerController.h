// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Misc/Utils.h"

#include "InGamePlayerController.generated.h"

class UInputMappingContext;
class UAction;
struct FInputActionValue;
class ADefaultCharacter;
class UCharacterMovementComponent;
class UCharacterStateComponent;

class UWeaponChildActorComponent;
class AWeaponBase;

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
	virtual void Tick(float DeltaTime) override;
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
	virtual void StopJump(const FInputActionValue& InValue);

	UFUNCTION()
	virtual void OnRun(const FInputActionValue& InValue);
	UFUNCTION()
	virtual void StopRun(const FInputActionValue& InValue);

	UFUNCTION()
	virtual void OnAttack(const FInputActionValue& InValue);

	UFUNCTION()
	virtual void OnEquip(const FInputActionValue& InValue);

	//Skill
	UFUNCTION()
	virtual void OnLockOn(const FInputActionValue& InValue);

	UFUNCTION()
	virtual void OnSkill01(const FInputActionValue& InValue);

protected:
	UFUNCTION()
	virtual void ToRun(const float DeltaTime);
	UFUNCTION()
	virtual void ToWalk(const float DeltaTime);	




protected:
	float MoveForwardSpeed = 1.0f;
	float MoveBackwardSpeed = 0.7f;
	float MoveRightSpeed = 0.8f;
	bool bIsRun = false;
	double WalkSpeed = 400.f;
	double RunSpeed = WalkSpeed * 1.5;


public:
	UPROPERTY(EditAnywhere)
	float Sensitivity = 1.0f;
	
	UPROPERTY()
	WeaponType EquipmentType;

protected:
	UDataTable* DataTable = nullptr;
	// Controller 상태 변경시 TableRow도 변경 필요
	const FCharacterControllerTableRow* ControllerTableRow = nullptr;
	ADefaultCharacter* ControlledCharacter = nullptr;


	UCharacterMovementComponent* CharacterMovement;
	UCharacterStateComponent* CharacterState;

	// Weapon
	UWeaponChildActorComponent* WeaponChildActor;
};
