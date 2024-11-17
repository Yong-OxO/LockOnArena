// Fill out your copyright notice in the Description page of Project Settings.

#include "GameMode/ArenaGameInstance.h"

//#include "Framework/Application/SlateApplication.h"
//#include "UObject/UObjectGlobals.h"
#include "MoviePlayer.h" 
#include "Engine/Engine.h"


void UArenaGameInstance::Init()
{
	Super::Init();

	if (FSlateApplication::IsInitialized())
	{
		FCoreUObjectDelegates::PostLoadMapWithWorld.AddUObject(this, &UArenaGameInstance::OnPostLoadMapWithWorld);
	}
}


void UArenaGameInstance::OnPostLoadMapWithWorld(UWorld* LoadedWorld)
{
	if (IsMoviePlayerEnabled()) 
	{ 
		// MoviePlayer를 초기화하고 로딩 스크린을 표시합니다. 
		GetMoviePlayer()->PlayMovie();
	}
}