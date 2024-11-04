// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/SkillUserWidget.h"
#include "Components/ProgressBar.h"
#include "Components/EditableTextBox.h"
#include "Components/Image.h"
#include "Character/DefaultCharacter.h"
#include "Actor/Weapon/WeaponBase.h"
#include "Skill/SkillBaseComponent.h"


void USkillUserWidget::NativeOnInitialized()
{

}

void USkillUserWidget::NativeConstruct()
{
	Super::NativeConstruct();

	ControlledCharacter = GetOwningPlayerPawn<ADefaultCharacter>();
	CharacterState = ControlledCharacter->GetState();
}

void USkillUserWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
	LockOnIcon();
	Skill01Icon();
}

void USkillUserWidget::SetData(const FDataTableRowHandle& InHandle)
{
	FWeaponBaseTableRow* DataTableRow = InHandle.GetRow<FWeaponBaseTableRow>(TEXT("DataTableRow"));
	ensureMsgf(DataTableRow, TEXT("Not Valid DataTableRow"));

	Weapon = ControlledCharacter->ActiveWeapon;
	if (Weapon)
	{		
		LockOnImage->SetBrushResourceObject(Weapon->LockOn->SkillImage);
		Skill01Image->SetBrushResourceObject(Weapon->Skill01->SkillImage);
	}
}

void USkillUserWidget::LockOnIcon()
{
	Weapon = ControlledCharacter->ActiveWeapon;
	USkillBaseComponent* LockOn = Weapon->LockOn;

	float MaxCD_LockOn = LockOn->GetMaxCooldown();
	float CD_RemainLockOn = LockOn->GetCooldown();
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
#define LOCTEXT_NAMESPACE "LockOn"
	FString FormattedString = FString::Printf(TEXT("%.1f"), CD_RemainLockOn);
	FText Text = FText::Format(LOCTEXT("ExampleFText", " {0}"), FText::FromString(FormattedString));
	RemainTime->SetText(Text);
#undef LOCTEXT_NAMESPACE
}

void USkillUserWidget::Skill01Icon()
{
	Weapon = ControlledCharacter->ActiveWeapon;

	USkillBaseComponent* Skill01 = Weapon->Skill01;
	float MaxCD_Skill01 = Skill01->GetMaxCooldown();
	float CD_RemainSkill01 = Weapon->GetSkill01_CD();
	const float Percent = CD_RemainSkill01 / MaxCD_Skill01;
	CD_Skill01->SetPercent(Percent);

	if (CD_RemainSkill01 <= 0)
	{
		Skill01Remain->SetVisibility(ESlateVisibility::Hidden);
	}
	else
	{
		Skill01Remain->SetVisibility(ESlateVisibility::Visible);
	}
#define LOCTEXT_NAMESPACE "SKill01"
	FString FormattedString01 = FString::Printf(TEXT("%.1f"), CD_RemainSkill01);
	FText Text01 = FText::Format(LOCTEXT("ExampleFText", " {0}"), FText::FromString(FormattedString01));
	Skill01Remain->SetText(Text01);
#undef LOCTEXT_NAMESPACE
}
