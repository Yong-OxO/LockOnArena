// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainWidget.generated.h"

class ADefaultCharacter;
class UCrosshairWidget;
class USkillUserWidget;
class UEnemyHpWidget;

UCLASS()
class LOCKONARENA_API UMainWidget : public UUserWidget
{
	GENERATED_BODY()
	
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

public:
	void VisibleNormalCrosshair();
	void VisibleLockOnCrosshair();

	UFUNCTION()
	void VisibleEnemyHpBar(const AActor* Enemy);

	UFUNCTION()
	void InvisibleEnemyHpBar();

protected:
	FTimerHandle TimerHandle;

protected:
	ADefaultCharacter* PlayerCharacter;

public:
	virtual  UCrosshairWidget* GetCrosshairWidget() { return UI_InGameCrosshair; }

public:
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UCrosshairWidget* UI_InGameCrosshair;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	USkillUserWidget* UI_Skill;	
	
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UEnemyHpWidget* UI_EnemyHp;


};
