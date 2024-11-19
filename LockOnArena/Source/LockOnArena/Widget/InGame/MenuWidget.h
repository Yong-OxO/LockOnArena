// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MenuWidget.generated.h"

class UButton;
class ADefaultCharacter;
class UCharacterStateComponent;

UCLASS()
class LOCKONARENA_API UMenuWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeConstruct() override;

protected:
	ADefaultCharacter* Character;
	UCharacterStateComponent* CharacterState;

public:
	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	UButton* ContinueBtn;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	UButton* SettingBtn;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	UButton* ExitBtn;

private:
	UFUNCTION()
	void OnContinueBtn();

	UFUNCTION()
	void OnSettingBtn();

	UFUNCTION()
	void OnExitBtn();
};
