// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "CharacterSaveGame.generated.h"


UCLASS()
class LOCKONARENA_API UCharacterSaveGame : public USaveGame
{
	GENERATED_BODY()

public:
    UCharacterSaveGame();

public:
    UPROPERTY(VisibleAnywhere, Category = Basic)
    FString PlayerName;

    UPROPERTY(VisibleAnywhere, Category = Basic)
    FString SaveSlotName;

    UPROPERTY(VisibleAnywhere, Category = Basic)
    uint32 UserIndex;

protected:
	UPROPERTY()
	int32 Level = 0;

	UPROPERTY()
	int32 StatPoint = 0;

	UPROPERTY()
	float ATK = 0;

	UPROPERTY()
	float MaxHp = 0;

	UPROPERTY()
	float MaxExp = 0;

	UPROPERTY()
	float Exp = 0;

	UPROPERTY()
	bool bShop = false;
};
