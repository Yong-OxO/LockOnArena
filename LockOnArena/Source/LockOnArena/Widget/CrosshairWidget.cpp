// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/CrosshairWidget.h"
#include "Components/Image.h"

void UCrosshairWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
}

void UCrosshairWidget::NativePreConstruct()
{
	Super::NativePreConstruct();

}

void UCrosshairWidget::NativeConstruct()
{
	Super::NativeConstruct();

}

void UCrosshairWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

}

void UCrosshairWidget::VisibleNormalCrosshair()
{
	NormalCrosshair->SetVisibility(ESlateVisibility::Visible);
	LockOnCrosshair->SetVisibility(ESlateVisibility::Hidden);
}

void UCrosshairWidget::VisibleLockOnCrosshair()
{
	NormalCrosshair->SetVisibility(ESlateVisibility::Hidden);
	LockOnCrosshair->SetVisibility(ESlateVisibility::Visible);
}