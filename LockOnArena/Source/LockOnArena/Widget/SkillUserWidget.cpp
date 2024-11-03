// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/SkillUserWidget.h"
#include "Components/ProgressBar.h"
#include "Components/EditableTextBox.h"
#include "Character/DefaultCharacter.h"
#include "Actor/Weapon/WeaponBase.h"

void USkillUserWidget::NativeOnInitialized()
{

}

void USkillUserWidget::NativeConstruct()
{
	Super::NativeConstruct();

	ControlledCharacter = GetOwningPlayerPawn<ADefaultCharacter>();	
}

void USkillUserWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	Weapon = ControlledCharacter->ActiveWeapon;

	float MaxCD_LockOn = Weapon->GetLockOn_MaxCD();
	float CD_RemainLockOn = Weapon->GetLockOn_CD();
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
