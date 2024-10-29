// Fill out your copyright notice in the Description page of Project Settings.


#include "Skill/RifleSkillSystem.h"
#include "Skill/SkillBase.h"

ARifleSkillSystem::ARifleSkillSystem()
{
	FRifleSkillSystemTableRow* Row;
	LockOn = CreateDefaultSubobject<>(TEXT("LockOn"));
}

void ARifleSkillSystem::PlaySkill(const int SkillNum)
{
	switch (SkillNum)
	{
	case 0:
	{
		// LockOn->Play
		break;
	}
	}
}
