// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/InGame/MenuWidget.h"
#include "Widget/EventDispatcher/UIEventDispatcher.h"
#include "Misc/Utils.h"
#include "Components/Button.h"
#include "Character/DefaultCharacter.h"
#include "Character/InGamePlayerController.h"
#include "Character/CharacterStateComponent.h"
#include "GameFramework/PlayerController.h"


void UMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();

	Character = Cast<ADefaultCharacter>(GetOwningPlayerPawn());
	CharacterState = Character->GetState();
	{
		ContinueBtn->OnClicked.RemoveDynamic(this, &ThisClass::OnContinueBtn);
		SettingBtn->OnClicked.RemoveDynamic(this, &ThisClass::OnSettingBtn);
		ExitBtn->OnClicked.RemoveDynamic(this, &ThisClass::OnExitBtn);

		ContinueBtn->OnClicked.AddDynamic(this, &ThisClass::OnContinueBtn);
		SettingBtn->OnClicked.AddDynamic(this, &ThisClass::OnSettingBtn);
		ExitBtn->OnClicked.AddDynamic(this, &ThisClass::OnExitBtn);
	}
	bIsFocusable = true;
	SetKeyboardFocus();
	bKeyDown = false;
}

FReply UMenuWidget::NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent)
{
	if (bKeyDown) { return Super::NativeOnKeyDown(InGeometry, InKeyEvent); }
	if (InKeyEvent.GetKey() == EKeys::Q) 
	{
		AInGamePlayerController* Controller = Cast<AInGamePlayerController>(Character->GetController());
		Controller->UIEventDispatcher->BroadCastUIEvent(UIEventName::Menu);
		bKeyDown = true;
	}

	return Super::NativeOnKeyDown(InGeometry, InKeyEvent);
}

void UMenuWidget::OnContinueBtn()
{	
	AInGamePlayerController* Controller = Cast<AInGamePlayerController>(Character->GetController());
	Controller->UIEventDispatcher->BroadCastUIEvent(UIEventName::Menu);
}

void UMenuWidget::OnSettingBtn()
{
}

void UMenuWidget::OnExitBtn()
{
}
