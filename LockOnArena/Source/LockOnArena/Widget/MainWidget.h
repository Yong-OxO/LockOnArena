// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainWidget.generated.h"

class UCrosshairWidget;
class USkillUserWidget;
UCLASS()
class LOCKONARENA_API UMainWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void VisibleNormalCrosshair();
	void VisibleLockOnCrosshair();

	virtual  UCrosshairWidget* GetCrosshairWidget() { return UI_InGameCrosshair; }
public:
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UCrosshairWidget* UI_InGameCrosshair;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	USkillUserWidget* UI_Skill;


};
