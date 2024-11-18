// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/Trigger/ArenaPortal.h"
#include "Misc/Utils.h"
#include "Components/BoxComponent.h"
#include "Blueprint/UserWidget.h"
#include "GameMode/ArenaGameInstance.h"

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
	UArenaGameInstance* GameInstance = Cast<UArenaGameInstance>(GetGameInstance());

	GameInstance->AsyncOpenLevel(WidgetClass, NextLevel);
}
