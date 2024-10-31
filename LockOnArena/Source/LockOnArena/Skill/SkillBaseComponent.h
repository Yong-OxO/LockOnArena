// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SkillBaseComponent.generated.h"


class UAnimMontage;

USTRUCT()
struct LOCKONARENA_API FSkillBaseTableRow : public FTableRowBase
{
	GENERATED_BODY()

public:
	UAnimMontage* Montage;

public:
	UPROPERTY(EditAnywhere)
	float MaxCoolDown = 0.f;

	UPROPERTY(EditAnywhere)
	bool IsSupperAmmo = false;

	UPROPERTY(EditAnywhere)
	float SupperAmmoTime = 0.f;
};


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class LOCKONARENA_API USkillBaseComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USkillBaseComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	virtual bool CanPlaySkill() { return bCanPlay; }

	virtual void PlaySkill(const int SkillNum);

	virtual void SetData(const FDataTableRowHandle& InHandle);

protected:
	UPROPERTY()
	float MaxCooldown = 0.f;


	UPROPERTY()
	float CurrnetCooldown = 0.f;
	
	bool bCanPlay = true;
	
	float DamagePercent = 100.f;

};
