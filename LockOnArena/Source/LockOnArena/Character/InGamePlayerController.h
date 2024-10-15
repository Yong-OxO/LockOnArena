// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "InGamePlayerController.generated.h"

class UInputMappingContext;
class UAction;

USTRUCT()
struct LOCKONARENA_API FCharacterControllerTableRow : public FTableRowBase
{
	GENERATED_BODY()

	UInputMappingContext* InputMappingContext = nullptr;
};



UCLASS()
class LOCKONARENA_API AInGamePlayerController : public APlayerController
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

	//virtual void OnPossess(APawn* InPawn);
	
protected:
	UInputMappingContext* IMC_Default = nullptr;

	
};
