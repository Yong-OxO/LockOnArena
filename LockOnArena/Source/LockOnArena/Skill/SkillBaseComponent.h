// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SkillBaseComponent.generated.h"


class UAnimMontage;
class USkillBaseComponent;
class ADefaultCharacter;
class AInGamePlayerController;
class UCharacterStateComponent;
class AWeaponBase;


USTRUCT()
struct LOCKONARENA_API FSkillBaseTableRow : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	TSubclassOf<USkillBaseComponent> SkillClass = nullptr;

public:
	UPROPERTY(EditAnywhere, Category = "Skill|Base")
	float MaxCoolDown = 0.f;

	UPROPERTY(EditAnywhere, Category = "Skill|Base")
	bool IsSuperAmmo = false;

	UPROPERTY(EditAnywhere, Category = "Skill|Base")
	float SuperAmmoTime = 0.f;
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
	UFUNCTION()
	virtual void SetData(const FDataTableRowHandle& InHandle);

public:
	UFUNCTION()
	virtual bool CanPlaySkill() { return bCanPlay; }

	UFUNCTION()
	virtual void PlaySkill();

	UFUNCTION()
	virtual float GetMaxCooldown();	
	UFUNCTION()
	virtual float GetCooldown();

	UFUNCTION()
	virtual void ReduceCooldown(float DeltaTime);
	


protected:
	ADefaultCharacter* ControlledCharacter;
	AInGamePlayerController* Controller;
	UCharacterStateComponent* CharacterState;
	AWeaponBase* Weapon;

protected:
	UPROPERTY()
	float MaxCooldown = 0.f;


	UPROPERTY()
	float RemainCoolDown = 0.f;
	
	bool bCanPlay = true;
	

	float DamagePercent = 100.f;
	bool bSuperAmmo = false;
	float SuperAmmoTime = 0.f;
};
