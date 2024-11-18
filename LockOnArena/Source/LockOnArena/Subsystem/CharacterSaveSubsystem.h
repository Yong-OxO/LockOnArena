// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "CharacterSaveSubsystem.generated.h"


class ADefaultCharacter;

UCLASS()
class LOCKONARENA_API UCharacterSaveSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	void SaveCharacterState(ADefaultCharacter* Character);

	void LoadCharacterState(ADefaultCharacter* Character);

protected:
	int32 Level = 0;
	int32 StatPoint = 0;
	float ATK = 0;
	float MaxHp = 0;
	float MaxExp = 0;
	float Exp = 0;
	bool bShop = false;
};
