// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/SkillUserWidget.h"
#include "Components/ProgressBar.h"
#include "Components/EditableTextBox.h"
#include "Character/DefaultCharacter.h"
#include "Character/CharacterStateComponent.h"

void USkillUserWidget::NativeOnInitialized()
{
	ControlledCharacter = GetOwningPlayerPawn<ADefaultCharacter>();
	CharacterState = ControlledCharacter->GetState();
}

void USkillUserWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	float MaxCD_LockOn = CharacterState->GetCD_LockOn();
	float CD_RemainLockOn = CharacterState->GetCD_RemainLockOn();
	const float Percent = CD_RemainLockOn / MaxCD_LockOn;
	CD_LockOn->SetPercent(Percent);

	if (CD_RemainLockOn <= 0)
	{
		RemainTime->SetVisibility(ESlateVisibility::Hidden);
	}
	else
	{
		RemainTime->SetVisibility(ESlateVisibility::Visible);
	}
#define LOCTEXT_NAMESPACE "MyNamespace"
	FString FormattedString = FString::Printf(TEXT("%.1f"), CD_RemainLockOn);
	FText Text = FText::Format(LOCTEXT("ExampleFText", " {0}"), FText::FromString(FormattedString));
	RemainTime->SetText(Text);
#undef LOCTEXT_NAMESPACE
}
