// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SkillUserWidget.generated.h"

class UProgressBar;
class ADefaultCharacter;
class UCharacterStateComponent;
class UEditableTextBox;
class AWeaponBase;

UCLASS()
class LOCKONARENA_API USkillUserWidget : public UUserWidget
{
	GENERATED_BODY()

	virtual void NativeOnInitialized() override;
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

protected:
	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	UProgressBar* CD_LockOn = nullptr; 

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	UEditableTextBox* RemainTime = nullptr;

protected:
	ADefaultCharacter* ControlledCharacter;
	UCharacterStateComponent* CharacterState;
	AWeaponBase* Weapon;
};
