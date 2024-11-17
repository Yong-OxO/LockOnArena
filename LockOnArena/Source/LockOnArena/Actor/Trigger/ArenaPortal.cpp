// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/Trigger/ArenaPortal.h"
#include "Misc/Utils.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/UserWidget.h"
#include "MoviePlayer.h"

AArenaPortal::AArenaPortal()
{
	PrimaryActorTick.bCanEverTick = true;
	bGenerateOverlapEventsDuringLevelStreaming = true;

	Portal = CreateDefaultSubobject<UBoxComponent>(TEXT("Portal"));
	SetRootComponent(Portal);
	Portal->SetCollisionProfileName(CollisionProfileName::Portal);
	Portal->SetCollisionEnabled(ECollisionEnabled::QueryOnly);

	Portal->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnTrigger);	
}

void AArenaPortal::BeginPlay()
{
	Super::BeginPlay();


}

void AArenaPortal::OnTrigger(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
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
