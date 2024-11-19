// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/InGame/MenuWidget.h"
#include "Components/Button.h"
#include "Character/DefaultCharacter.h"
#include "Character/CharacterStateComponent.h"

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
}

void UMenuWidget::OnContinueBtn()
{

}

void UMenuWidget::OnSettingBtn()
{
}

void UMenuWidget::OnExitBtn()
{
}
