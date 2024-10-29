// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ChildActorComponent.h"
#include "SkillChildActorComponent.generated.h"

/**
 * 
 */
UCLASS()
class LOCKONARENA_API USkillChildActorComponent : public UChildActorComponent
{
	GENERATED_BODY()
	
public:
	USkillChildActorComponent();

public:
	virtual void SetData(const FDataTableRowHandle& InRowHandle);
};
