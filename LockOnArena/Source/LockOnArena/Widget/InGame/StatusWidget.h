// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "StatusWidget.generated.h"

class ADefaultCharacter;
class UCharacterStateComponent;
class UProgressBar;
class UEditableTextBox;
class UButton;

UCLASS()
class LOCKONARENA_API UStatusWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeConstruct() override;

private:
	UFUNCTION()
	void SetStatus();

	UFUNCTION()
	void CharacterHpUp();

	UFUNCTION()
	void CharacterATKUp();

private:
	ADefaultCharacter* Character;
	UCharacterStateComponent* CharacterState;

private:
	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	UEditableTextBox* CharacterHpStat = nullptr;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	UEditableTextBox* CharacterATKStat = nullptr;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	UEditableTextBox* StatPoint = nullptr;
	
	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	UButton* HpUpButton;
	
	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	UButton* ATKUpButton;

};
