// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "DefaultHUD.generated.h"


class ADefaultCharacter;
class UCharacterStateComponent;
class AInGamePlayerController;


UCLASS()
class LOCKONARENA_API ADefaultHUD : public AHUD
{
	GENERATED_BODY()
	
public:

protected:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

protected:

	AInGamePlayerController* Controller = nullptr;
	ADefaultCharacter* ControlledCharacter = nullptr;
	UCharacterStateComponent* CharacterState = nullptr;


	
};
