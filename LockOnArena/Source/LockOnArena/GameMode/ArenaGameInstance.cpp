// Fill out your copyright notice in the Description page of Project Settings.

#include "GameMode/ArenaGameInstance.h"
#include "MoviePlayer.h" 
#include "Engine/Engine.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Subsystem/CharacterSaveSubsystem.h"
#include "Character/DefaultCharacter.h"

//#include "Framework/Application/SlateApplication.h"
//#include "UObject/UObjectGlobals.h"

void UArenaGameInstance::Init()
{
	Super::Init();

	if (FSlateApplication::IsInitialized())
	{
		FCoreUObjectDelegates::PostLoadMapWithWorld.AddUObject(this, &UArenaGameInstance::OnPostLoadMapWithWorld);
	}

	CharacterSaveSubsystem = GetSubsystem<UCharacterSaveSubsystem>();
}


void UArenaGameInstance::AsyncOpenLevel(TSubclassOf<UUserWidget> WidgetClass, TSoftObjectPtr<UWorld> NextLevel)
{
	if (CharacterSaveSubsystem)
	{
		ADefaultCharacter* PrevPlayerCharacter = Cast<ADefaultCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0));
		CharacterSaveSubsystem->SaveCharacterState(PrevPlayerCharacter);


		if (!WidgetClass)
		{
			ensureMsgf(false, TEXT("WidgetClass is nullptr"));
			return;
		}
		UUserWidget* Widget = CreateWidget<UUserWidget>(GetWorld(), WidgetClass);

		if (IsMoviePlayerEnabled())
		{
			FLoadingScreenAttributes LoadingScreenAttributes;
			LoadingScreenAttributes.WidgetLoadingScreen = Widget->TakeWidget();
			//LoadingScreenAttributes.WidgetLoadingScreen = FLoadingScreenAttributes::NewTestLoadingScreenWidget();
			LoadingScreenAttributes.MinimumLoadingScreenDisplayTime = 3.f;
			LoadingScreenAttributes.bAutoCompleteWhenLoadingCompletes = true;
			LoadingScreenAttributes.bAllowEngineTick = true;

			GetMoviePlayer()->SetupLoadingScreen(LoadingScreenAttributes);
		}

		UGameplayStatics::OpenLevelBySoftObjectPtr(this, NextLevel);		
	}
}

void UArenaGameInstance::OnPostLoadMapWithWorld(UWorld* LoadedWorld)
{
	if (IsMoviePlayerEnabled()) 
	{ 
		GetMoviePlayer()->PlayMovie();
	}
}