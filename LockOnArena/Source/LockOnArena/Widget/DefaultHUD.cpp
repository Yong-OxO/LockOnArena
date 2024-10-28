// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/DefaultHUD.h"
#include "Kismet/GameplayStatics.h"
#include "Character/DefaultCharacter.h"
#include "Character/InGamePlayerController.h"
#include "Character/CharacterStateComponent.h"
#include "Widget/MainWidget.h"

void ADefaultHUD::BeginPlay()
{
	Super::BeginPlay();

	Controller = Cast<AInGamePlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));

	UClass* WidgetClass = LoadClass<UMainWidget>(nullptr, TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/Blueprint/Widget/UI_InGameMain.UI_InGameMain_C'"));
	UMainWidget* MainWidget = CreateWidget<UMainWidget>(GetWorld(), WidgetClass);
	MainWidget->AddToViewport();
}

void ADefaultHUD::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
