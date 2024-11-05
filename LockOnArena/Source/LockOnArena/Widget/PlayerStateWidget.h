// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerStateWidget.generated.h"


class UProgressBar;
class UEditableTextBox;
class UCharacterStateComponent;

UCLASS()
class LOCKONARENA_API UPlayerStateWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	UFUNCTION()
	virtual void UpDateCharacterState();

	virtual void UpDateExpProgress(float InDeltaTime);
	virtual void UpDateHpProgress(float InDeltaTime);
protected:
	UCharacterStateComponent* PlayerState;

protected: // Exp
	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	UProgressBar* ExpProgress = nullptr;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	UEditableTextBox* CurrentExpText = nullptr;

	float ExpTargetPercent; // 변경 후 
	float ExpCurrentPercent; // 변경 전

	float HpTargetPercent; // 변경 후
	float HpCurrentPercent; // 변경 전

	bool bEndExp = true;
	bool bEndHp = true;

protected: // Hp
	UPROPERTY(VisibleAnywhere, meta =(BindWidget))
	UProgressBar* HPProgress = nullptr;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	UEditableTextBox* HpCount = nullptr;
};
