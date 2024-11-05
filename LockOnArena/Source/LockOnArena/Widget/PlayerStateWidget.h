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

protected:
	UCharacterStateComponent* PlayerState;

protected:
	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	UProgressBar* ExpProgress = nullptr;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	UEditableTextBox* CurrentExpText = nullptr;

	float TargetPercent;
	float CurrentPercent;

	bool bCanTick = false;
};
