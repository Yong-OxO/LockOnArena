// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/InGame/EnemyHpWidget.h"
#include "Character/DefaultCharacter.h"
#include "Enemy/EnemyStateComponent.h"
#include "Enemy/EnemyBase.h"
#include "Components/ProgressBar.h"
#include "Components/EditableTextBox.h"

void UEnemyHpWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void UEnemyHpWidget::SetHpBar(const AActor* Enemy)
{
	AActor* NonconstEnemy = const_cast<AActor*>(Enemy);
	DamagedEnemy = Cast<AEnemyBase>(NonconstEnemy);

	UEnemyStateComponent* EnemyState = DamagedEnemy->GetState();
	float EnemyMaxHp = EnemyState->GetMaxHp();
	float EnemyCurrentHp = EnemyState->GetCurrentHp();

	float TargetPercent = EnemyCurrentHp / EnemyMaxHp;

	HPProgress->SetPercent(TargetPercent);
	EnemyName->SetText(DamagedEnemy->GetEnemyName());
}
