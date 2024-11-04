// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/MainWidget.h"
#include "Widget/CrosshairWidget.h"
#include "Widget/SkillUserWidget.h"

void UMainWidget::VisibleNormalCrosshair()
{
	UI_InGameCrosshair->VisibleNormalCrosshair();
}

void UMainWidget::VisibleLockOnCrosshair()
{
	UI_InGameCrosshair->VisibleLockOnCrosshair();
}
