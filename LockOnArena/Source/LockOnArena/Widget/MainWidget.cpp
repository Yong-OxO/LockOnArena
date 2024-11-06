// Fill out your copyright notice in the Description page of Project Settings.



#include "Widget/MainWidget.h"
#include "Widget/CrosshairWidget.h"
#include "Widget/InGame/SkillUserWidget.h"
#include "Widget/InGame/EnemyHpWidget.h"
#include "Character/DefaultCharacter.h"


void UMainWidget::NativeConstruct()
{
	PlayerCharacter = Cast<ADefaultCharacter>(GetOwningPlayerPawn());
	PlayerCharacter->OnEnemyTakeDamage.AddDynamic(this, &ThisClass::VisibleEnemyHpBar);

	UI_EnemyHp->SetVisibility(ESlateVisibility::Hidden);
}

void UMainWidget::NativeDestruct()
{
	Super::NativeDestruct();
	GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
}

void UMainWidget::VisibleNormalCrosshair()
{
	UI_InGameCrosshair->VisibleNormalCrosshair();
}

void UMainWidget::VisibleLockOnCrosshair()
{
	UI_InGameCrosshair->VisibleLockOnCrosshair();
}

void UMainWidget::VisibleEnemyHpBar(const AActor* Enemy)
{
	UI_EnemyHp->SetHpBar(Enemy);
	UI_EnemyHp->SetVisibility(ESlateVisibility::Visible);

	GetWorld()->GetTimerManager().SetTimer(
		TimerHandle,   // FTimerHandle 변수
		this,          // 타이머를 설정할 객체
		&ThisClass::InvisibleEnemyHpBar, // 실행할 함수
		7.f,          // 대기 시간(초 단위)
		false          // 반복 여부 (false면 한 번만 실행)
	);
}

void UMainWidget::InvisibleEnemyHpBar()
{
	UI_EnemyHp->SetVisibility(ESlateVisibility::Hidden);
}
