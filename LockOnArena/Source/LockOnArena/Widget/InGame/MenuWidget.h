// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MenuWidget.generated.h"

class UButton;
class ADefaultCharacter;
class UCharacterStateComponent;
class UCanvasPanel;

UCLASS()
class LOCKONARENA_API UMenuWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeConstruct() override;
	virtual FReply NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent) override;

	bool bKeyDown = false;
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


	// Exit 최종 확인 Window
	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	UCanvasPanel* ExitWindow;
	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	UButton* ExitYes;
	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	UButton* ExitNo;

private:
	UFUNCTION()
	void OnContinueBtn();

	UFUNCTION()
	void OnSettingBtn();

	UFUNCTION()
	void OnExitWindowBtn();	

	UFUNCTION()
	void OnExitYesBtn();	
	
	UFUNCTION()
	void OnExitNoBtn();
};
