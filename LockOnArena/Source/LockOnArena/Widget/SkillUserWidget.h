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
class UImage;


UCLASS()
class LOCKONARENA_API USkillUserWidget : public UUserWidget
{
	GENERATED_BODY()

	virtual void NativeOnInitialized() override;
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

public:
	virtual void SetData(const FDataTableRowHandle& InHandle);

protected:
	virtual void LockOnIcon();
	virtual void Skill01Icon();
protected:
	// LockOn

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	UImage* LockOnImage = nullptr;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	UProgressBar* CD_LockOn = nullptr; 

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	UEditableTextBox* RemainTime = nullptr;


	// Skill 01

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	UImage* Skill01Image = nullptr;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	UProgressBar* CD_Skill01 = nullptr;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	UEditableTextBox* Skill01Remain = nullptr;

protected:
	ADefaultCharacter* ControlledCharacter;
	UCharacterStateComponent* CharacterState;
	AWeaponBase* Weapon;
};
