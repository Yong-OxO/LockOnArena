// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/InGame/StatusWidget.h"
#include "Character/DefaultCharacter.h"
#include "Character/CharacterStateComponent.h"
#include "Components/ProgressBar.h"
#include "Components/EditableTextBox.h"
#include "Components/Button.h"


void UStatusWidget::NativeConstruct()
{
	Super::NativeConstruct();

	Character = Cast<ADefaultCharacter>(GetOwningPlayerPawn());
	CharacterState = Character->GetState();
	//CharacterState->OnCharacterStateChanged.AddDynamic(this, &UStatusWidget::SetStatus);

	{
		HpUpButton->OnClicked.RemoveDynamic(this, &ThisClass::CharacterHpUp);
		ATKUpButton->OnClicked.RemoveDynamic(this, &ThisClass::CharacterATKUp);

		HpUpButton->OnClicked.AddDynamic(this, &ThisClass::CharacterHpUp);
		ATKUpButton->OnClicked.AddDynamic(this, &ThisClass::CharacterATKUp);
	}

	SetStatus();
}


void UStatusWidget::SetStatus() // 시작할 때 + 버튼 클릭함수에서 호출
{
	FString FormattedString;
	FText Text;

#define LOCTEXT_NAMESPACE "CharacterHpStat"
	FormattedString = FString::Printf(TEXT("%.0f"), CharacterState->GetMaxHp());
	Text = FText::Format(LOCTEXT("ExampleFText", " {0}"), FText::FromString(FormattedString));
	CharacterHpStat->SetText(Text);
#undef LOCTEXT_NAMESPACE

#define LOCTEXT_NAMESPACE "CharacterATKStat"
	FormattedString = FString::Printf(TEXT("%.0f"), CharacterState->GetCharacterATK());
	Text = FText::Format(LOCTEXT("ExampleFText", " {0}"), FText::FromString(FormattedString));
	CharacterATKStat->SetText(Text);
#undef LOCTEXT_NAMESPACE

#define LOCTEXT_NAMESPACE "StatPoint"
	FormattedString = FString::Printf(TEXT("%d"), CharacterState->StatPoint);
	Text = FText::Format(LOCTEXT("ExampleFText", " {0}"), FText::FromString(FormattedString));
	StatPoint->SetText(Text);
#undef LOCTEXT_NAMESPACE

	CharacterState->OnCharacterStateChanged.Broadcast();
}

void UStatusWidget::CharacterHpUp()
{ 
	if (CharacterState->StatPoint > 0)
	{
		float UpMaxHp = CharacterState->GetMaxHp() * 0.1;
		CharacterState->AddMaxHp(UpMaxHp);
		CharacterState->HealCurrentHp(UpMaxHp);

		--CharacterState->StatPoint;

		SetStatus();
	}
}

void UStatusWidget::CharacterATKUp()
{
	if (CharacterState->StatPoint > 0)
	{
		float UpATK = 3;
		CharacterState->AddCharacterATK(UpATK);
		--CharacterState->StatPoint;

		SetStatus();
	}
}



