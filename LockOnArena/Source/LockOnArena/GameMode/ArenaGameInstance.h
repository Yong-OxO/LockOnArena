// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "ArenaGameInstance.generated.h"


class UUserWidget;
class UCharacterSaveSubsystem;

UCLASS()
class LOCKONARENA_API UArenaGameInstance : public UGameInstance
{
	GENERATED_BODY()
	public: 
		virtual void Init() override;

		virtual void AsyncOpenLevel(TSubclassOf<UUserWidget> WidgetClass, TSoftObjectPtr<UWorld> NextLevel);
		virtual void OnPostLoadMapWithWorld(UWorld* LoadedWorld);

		UCharacterSaveSubsystem* CharacterSaveSubsystem;
};
