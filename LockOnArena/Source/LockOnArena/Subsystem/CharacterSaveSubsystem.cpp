// Fill out your copyright notice in the Description page of Project Settings.


#include "Subsystem/CharacterSaveSubsystem.h"
#include "Character/DefaultCharacter.h"
#include "Character/CharacterStateComponent.h"

void UCharacterSaveSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	Level = 0;
}

void UCharacterSaveSubsystem::SaveCharacterState(ADefaultCharacter* Character)
{
	UCharacterStateComponent* CharacterState = Character->GetState();
	Level = CharacterState->GetCharacterLevel();
	StatPoint = CharacterState->GetStatPoint();
	ATK = CharacterState->GetCharacterATK();
	MaxHp = CharacterState->GetMaxHp();
	MaxExp = CharacterState->GetMaxExp();
	Exp = CharacterState->GetCurrentExp();
	bShop = CharacterState->CanUseShop();
}

void UCharacterSaveSubsystem::LoadCharacterState(ADefaultCharacter* Character)
{
	if (Level == 0) { return; }
	UCharacterStateComponent* CharacterState = Character->GetState();
	CharacterState->SetCharacterLevel(Level);
	CharacterState->SetStatPoint(StatPoint);
	CharacterState->SetCharacterATK(ATK);
	CharacterState->SetMaxHp(MaxHp);
	CharacterState->SetMaxExp(MaxExp);
	CharacterState->SetCurrentExp(Exp);

	CharacterState->HealCurrentHp(MaxHp);
	CharacterState->SetUseShop(bShop);
	

	CharacterState->OnCharacterStateChanged.Broadcast();
}
