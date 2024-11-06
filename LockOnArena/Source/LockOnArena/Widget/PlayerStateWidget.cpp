// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/PlayerStateWidget.h"
#include "Character/DefaultCharacter.h"
#include "Character/CharacterStateComponent.h"
#include "Components/ProgressBar.h"
#include "Components/EditableTextBox.h"


void UPlayerStateWidget::NativeConstruct()
{
	Super::NativeConstruct();

	ADefaultCharacter* PlayerCharacter = Cast<ADefaultCharacter>(GetOwningPlayerPawn());
	PlayerState = PlayerCharacter->GetState();

	UpDateCharacterState();

	PlayerState->OnCharacterStateChanged.AddDynamic(this, &UPlayerStateWidget::UpDateCharacterState);

	bEndExp = true;
	bEndHp = true;

	ExpCurrentPercent = PlayerState->GetCurrentExp() / PlayerState->GetMaxExp();
	ExpProgress->SetPercent(ExpCurrentPercent);

	HpCurrentPercent = PlayerState->GetCurrentHp() / PlayerState->GetMaxHp();	
	HPProgress->SetPercent(HpCurrentPercent);
}

void UPlayerStateWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	if (bEndExp && bEndHp) { return; }

	UpDateExpProgress(InDeltaTime);
	UpDateHpProgress(InDeltaTime);
}


void UPlayerStateWidget::UpDateCharacterState()
{
	// Hp
	float CurrentHp = PlayerState->GetCurrentHp();
	float MaxHp = PlayerState->GetMaxHp();

	HpTargetPercent = CurrentHp / MaxHp;

#define LOCTEXT_NAMESPACE "PlayerHp"
	FString FormattedString = FString::Printf(TEXT("%.0f / %.0f"), CurrentHp, MaxHp);
	FText Text = FText::Format(LOCTEXT("ExampleFText", "{0}"), FText::FromString(FormattedString));
	HpCount->SetText(Text);
#undef LOCTEXT_NAMESPACE

	// EXP
	float PlayerMaxExp = PlayerState->GetMaxExp();
	float PlayerCurrentExp = PlayerState->GetCurrentExp();

	ExpTargetPercent = PlayerCurrentExp / PlayerMaxExp;

	float TextPercent = ExpTargetPercent * 100.f;

#define LOCTEXT_NAMESPACE "PlayerExp"
	FormattedString = FString::Printf(TEXT("%.2f%%"), TextPercent);
	Text = FText::Format(LOCTEXT("ExampleFText", "{0}"), FText::FromString(FormattedString));
	CurrentExpText->SetText(Text);
#undef LOCTEXT_NAMESPACE
	bEndExp = false;
	bEndHp = false;
}

void UPlayerStateWidget::UpDateExpProgress(float InDeltaTime)
{
	float Alpha = 5 * InDeltaTime;
	if (PlayerState->StackLevel) // Level 스택이 있을 때
	{
		if (FMath::IsNearlyEqual(ExpCurrentPercent, 1, 0.01f))
		{
			ExpCurrentPercent = 0.0f;
			--(PlayerState->StackLevel);
			Alpha = 5 * InDeltaTime;
		}
		else
		{
			ExpCurrentPercent = FMath::Lerp(ExpCurrentPercent, 1, Alpha);
			Alpha += InDeltaTime * 2;
			ExpProgress->SetPercent(ExpCurrentPercent);
		}
	}
	else // Level 스택이 없을 때
	{
		if (FMath::IsNearlyEqual(ExpCurrentPercent, ExpTargetPercent, 0.01f))
		{
			ExpCurrentPercent = ExpTargetPercent;
			ExpProgress->SetPercent(ExpCurrentPercent);
			Alpha = 10 * InDeltaTime;
			bEndExp = true;
		}
		else
		{
			ExpCurrentPercent = FMath::Lerp(ExpCurrentPercent, ExpTargetPercent, 0.1);
			Alpha += InDeltaTime;
			ExpProgress->SetPercent(ExpCurrentPercent);
		}
	}
}

void UPlayerStateWidget::UpDateHpProgress(float InDeltaTime)
{
	if (FMath::IsNearlyEqual(HpCurrentPercent, HpTargetPercent, 0.001))
	{
		HpCurrentPercent = HpTargetPercent;
		bEndHp = true;
	}
	else
	{
		float Alpha = InDeltaTime * 5;

		if (Alpha > 1) { Alpha = 1; }

		HpCurrentPercent = FMath::Lerp(HpCurrentPercent, HpTargetPercent, Alpha);
		HPProgress->SetPercent(HpCurrentPercent);
	}

}


