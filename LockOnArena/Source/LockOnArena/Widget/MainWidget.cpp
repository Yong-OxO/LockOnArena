// Fill out your copyright notice in the Description page of Project Settings.



#include "Widget/MainWidget.h"
#include "Widget/CrosshairWidget.h"
#include "Widget/InGame/SkillUserWidget.h"
#include "Widget/InGame/EnemyHpWidget.h"
#include "Widget/InGame/StatusWidget.h"
#include "Character/DefaultCharacter.h"
#include "Character/InGamePlayerController.h"
#include "Blueprint/WidgetBlueprintLibrary.h"

void UMainWidget::NativeConstruct()
{
	PlayerCharacter = Cast<ADefaultCharacter>(GetOwningPlayerPawn());
	PlayerController = Cast<AInGamePlayerController>(PlayerCharacter->GetController());

	PlayerCharacter->OnEnemyTakeDamage.AddDynamic(this, &ThisClass::VisibleEnemyHpBar);
	PlayerController->OnStatusUIPressed.AddDynamic(this, &ThisClass::ShowHideStatusUI);

	UI_EnemyHp->SetVisibility(ESlateVisibility::Hidden);

	bStatusUIActive = true; // True 상태에서 호출해야 false가 되기 때문
	ShowHideStatusUI();
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

void UMainWidget::ShowHideStatusUI()
{
	if (bStatusUIActive) // 창 끄기
	{
		UI_Status->RemoveFromViewport();

		FInputModeGameOnly InputModeGame;
		PlayerController->SetInputMode(InputModeGame);

		//UWidgetBlueprintLibrary::SetInputMode_GameOnly(PlayerController, true);

		PlayerController->SetShowMouseCursor(false);

		bStatusUIActive = false;
	}

	else // 창띄우기
	{
		UI_Status->AddToViewport();
		FInputModeGameAndUI InputModeGame;
		PlayerController->SetInputMode(InputModeGame);

		//UWidgetBlueprintLibrary::SetInputMode_GameAndUIEx(PlayerController, this);
		PlayerController->SetShowMouseCursor(true);

		bStatusUIActive = true;
	}
}
