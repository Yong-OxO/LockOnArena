// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "InGamePlayerController.generated.h"

class UInputMappingContext;
class UAction;
struct FInputActionValue;
class ADefaultCharacter;

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

	virtual void OnMove(const FInputActionValue& InValue);

protected:
	float MoveForwardSpeed = 500.f;
	float MoveRightSpeed = 450.f;

protected:
	//UPROPERTY(EditAnywhere, meta = (RowType = "/Script/KDT3D.WeaponTableRow"))
	//FDataTableRowHandle DataTableRowHandle;

	const FCharacterControllerTableRow* WeaponTableRow = nullptr;
	ADefaultCharacter* ControlledCharacter = nullptr;

};
