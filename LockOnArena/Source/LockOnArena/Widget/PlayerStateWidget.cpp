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

	float PlayerMaxExp = PlayerState->GetMaxExp();
	float PlayerCurrentExp = PlayerState->GetCurrentExp();

	bCanTick = false;

	CurrentPercent = PlayerCurrentExp / PlayerMaxExp;
}

void UPlayerStateWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	if (!bCanTick) { return; }

	Super::NativeTick(MyGeometry, InDeltaTime);

	float Alpha = 10 * InDeltaTime;
	if (PlayerState->StackLevel) // Level 스택이 있을 때
	{
		if (FMath::IsNearlyEqual(CurrentPercent, 1, 0.01f))
		{
			CurrentPercent = 0.0f;
			--(PlayerState->StackLevel);
			Alpha = 10 * InDeltaTime;
		}
		else
		{
			CurrentPercent = FMath::Lerp(CurrentPercent, 1, Alpha);
			Alpha += InDeltaTime * 5;
			ExpProgress->SetPercent(CurrentPercent);
		}
	}
	else // Level 스택이 없을 때
	{
		if (FMath::IsNearlyEqual(CurrentPercent, TargetPercent, 0.01f))
		{
			CurrentPercent = TargetPercent;
			ExpProgress->SetPercent(CurrentPercent);
			Alpha = 10 * InDeltaTime;
			bCanTick = false;
		}
		else
		{
			CurrentPercent = FMath::Lerp(CurrentPercent, TargetPercent, 0.1);
			Alpha += InDeltaTime;
			ExpProgress->SetPercent(CurrentPercent);
		}
	}
}


void UPlayerStateWidget::UpDateCharacterState()
{// @TODO : Hp도 보이게
	
	float PlayerMaxExp = PlayerState->GetMaxExp();
	float PlayerCurrentExp = PlayerState->GetCurrentExp();

	TargetPercent = PlayerCurrentExp / PlayerMaxExp;
	//ExpProgress->SetPercent(TargetPercent);

	float TextPercent = TargetPercent * 100.f;

#define LOCTEXT_NAMESPACE "PlayerState"
	FString FormattedString = FString::Printf(TEXT("%.2f%%"), TextPercent);
	FText Text = FText::Format(LOCTEXT("ExampleFText", "{0}"), FText::FromString(FormattedString));
	CurrentExpText->SetText(Text);
#undef LOCTEXT_NAMESPACE

	bCanTick = true;
}


