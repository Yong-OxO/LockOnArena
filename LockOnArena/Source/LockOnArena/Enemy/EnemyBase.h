// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "EnemyBase.generated.h"

class UWeaponChildActorComponent;
class UEnemyStateComponent;
class UEnemyAnimInstance;
class UEnemySkillBase;
class ABossClearPortal;

USTRUCT()
struct LOCKONARENA_API FEnemyBaseTableRow : public FTableRowBase
{
	GENERATED_BODY()

public: // Reacta
	UPROPERTY(EditAnywhere, Category = "Enemy|Animation")
	UAnimMontage* HitMontage = nullptr;
	UPROPERTY(EditAnywhere, Category = "Enemy|Animation")
	UAnimMontage* DeathMontage = nullptr;	
	UPROPERTY(EditAnywhere, Category = "Enemy|Animation")
	UAnimMontage* InitMontage = nullptr;

public: // Skill
	UPROPERTY(EditAnywhere, Category = "Enemy|Skill", meta = (RowType = "/Script/LOCKONARENA.EnemySkillBaseTableRow"))
	FDataTableRowHandle Skill01;

	UPROPERTY(EditAnywhere, Category = "Enemy|Skill", meta = (RowType = "/Script/LOCKONARENA.EnemySkillBaseTableRow"))
	FDataTableRowHandle Skill02;

	UPROPERTY(EditAnywhere, Category = "Enemy|Skill", meta = (RowType = "/Script/LOCKONARENA.EnemySkillBaseTableRow"))
	FDataTableRowHandle Skill03;
};


UCLASS()
class LOCKONARENA_API AEnemyBase : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemyBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	virtual float TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

public:
	UFUNCTION()
	virtual void OnMontageEnd(UAnimMontage* Montage, bool bInterrupted);

public:

public:
	virtual FText GetEnemyName() { return EnemyName; }

protected:
	UPROPERTY(EditAnywhere, Category = "Enemy|Info")
	FText EnemyName;

public:
	TArray<UEnemySkillBase*> Skills;
	UEnemySkillBase* Skill01;
	UEnemySkillBase* Skill02;	
	UEnemySkillBase* Skill03;

public:
	virtual UEnemyStateComponent* GetState() { return EnemyState; }

	UPROPERTY(VisibleAnywhere)
	UEnemyStateComponent* EnemyState = nullptr;
	UDataTable* DataTable = nullptr;
	const FEnemyBaseTableRow* DataTableRow = nullptr;


	UEnemyAnimInstance* AnimInstance = nullptr;


	float StackDamage = 0.f; // 일정 스택이 되면 Montage재생
protected:
	FTimerHandle TimerHandle;
	virtual void OnInit();
	virtual void OnDIe();

public:
	UPROPERTY(EditAnywhere)
	TObjectPtr<ABossClearPortal> ClearPortal = nullptr;
};
