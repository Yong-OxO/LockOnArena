// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "EnemyHpWidget.generated.h"



class ADefaultCharacter;
class AEnemyBase;
class UProgressBar;
class UEditableTextBox;

UCLASS()
class LOCKONARENA_API UEnemyHpWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;


public:
	virtual void SetHpBar(const AActor* Enemy);

protected:

	
	ADefaultCharacter* PlayerCharacter;
	AEnemyBase* DamagedEnemy;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	UProgressBar* HPProgress = nullptr;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	UEditableTextBox* EnemyName = nullptr;
	
	
};
