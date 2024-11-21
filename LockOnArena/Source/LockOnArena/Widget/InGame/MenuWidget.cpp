// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/InGame/MenuWidget.h"
#include "Subsystem/UIEventSubsystem.h"
#include "Misc/Utils.h"
#include "Components/Button.h"
#include "Components/CanvasPanel.h"
#include "Character/DefaultCharacter.h"
#include "Character/InGamePlayerController.h"
#include "Character/CharacterStateComponent.h"
#include "GameFramework/PlayerController.h"
#include "SaveGame/CharacterSaveGame.h"
#include "Kismet/GameplayStatics.h"


void UMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();

	Character = Cast<ADefaultCharacter>(GetOwningPlayerPawn());
	CharacterState = Character->GetState();
	{
		ContinueBtn->OnClicked.RemoveDynamic(this, &ThisClass::OnContinueBtn);
		SettingBtn->OnClicked.RemoveDynamic(this, &ThisClass::OnSettingBtn);
		ExitBtn->OnClicked.RemoveDynamic(this, &ThisClass::OnExitWindowBtn);
		ExitYes->OnClicked.RemoveDynamic(this, &ThisClass::OnExitYesBtn);
		ExitNo->OnClicked.RemoveDynamic(this, &ThisClass::OnExitNoBtn);

		ContinueBtn->OnClicked.AddDynamic(this, &ThisClass::OnContinueBtn);
		SettingBtn->OnClicked.AddDynamic(this, &ThisClass::OnSettingBtn);
		ExitBtn->OnClicked.AddDynamic(this, &ThisClass::OnExitWindowBtn);
		ExitYes->OnClicked.AddDynamic(this, &ThisClass::OnExitYesBtn);
		ExitNo->OnClicked.AddDynamic(this, &ThisClass::OnExitNoBtn);
	}
	bIsFocusable = true;
	SetKeyboardFocus();
	bKeyDown = false;
	ExitWindow->SetVisibility(ESlateVisibility::Hidden);
}

FReply UMenuWidget::NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent)
{
	if (bKeyDown) { return Super::NativeOnKeyDown(InGeometry, InKeyEvent); }
	if (InKeyEvent.GetKey() == EKeys::Q) 
	{
		UUIEventSubsystem* UIEventSubsystem = GetGameInstance()->GetSubsystem<UUIEventSubsystem>();		
		UIEventSubsystem->BroadCastUIEvent(UIEventName::Menu);
		bKeyDown = true;
	}

	return Super::NativeOnKeyDown(InGeometry, InKeyEvent);
}

void UMenuWidget::OnContinueBtn()
{	
	UUIEventSubsystem* UIEventSubsystem = GetGameInstance()->GetSubsystem<UUIEventSubsystem>();
	UIEventSubsystem->BroadCastUIEvent(UIEventName::Menu);
}

void UMenuWidget::OnSettingBtn()
{
}

void UMenuWidget::OnExitWindowBtn()
{	
	ExitWindow->SetVisibility(ESlateVisibility::Visible);
}

void UMenuWidget::OnExitYesBtn()
{
	AInGamePlayerController* Controller = Cast<AInGamePlayerController>(Character->GetController());

	FString MyPlayerName = TEXT("PlayerOne");
	UCharacterSaveGame* SaveGameInstance = Cast<UCharacterSaveGame>(UGameplayStatics::CreateSaveGameObject(UCharacterSaveGame::StaticClass()));
	SaveGameInstance->PlayerName = MyPlayerName;

	UGameplayStatics::SaveGameToSlot(SaveGameInstance, SaveGameInstance->PlayerName, 0);

	UKismetSystemLibrary::QuitGame(GetWorld(), Controller, EQuitPreference::Quit, false);
}

void UMenuWidget::OnExitNoBtn()
{
	ExitWindow->SetVisibility(ESlateVisibility::Hidden);
}
