// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/BaseCharacter.h"
#include "EnemyBase.generated.h"

class UWeaponChildActorComponent;
class UEnemyStateComponent;
class UEnemyAnimInstance;

USTRUCT()
struct LOCKONARENA_API FEnemyBaseTableRow : public FTableRowBase
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, Category = "Enemy|Weapon", meta = (RowType = "/Script/LOCKONARENA.WeaponBaseTableRow"))
	FDataTableRowHandle WeaponBaseTableRowHandle; // 1

	UPROPERTY(EditAnywhere, Category = "Enemy|Weapon", meta = (RowType = "/Script/LOCKONARENA.WeaponBaseTableRow"))
	FDataTableRowHandle PunchTableRowHandle; // 2

	UPROPERTY(EditAnywhere, Category = "Enemy|Weapon", meta = (RowType = "/Script/LOCKONARENA.WeaponBaseTableRow"))
	FDataTableRowHandle KnifeTableRowHandle; // 3

	UPROPERTY(EditAnywhere, Category = "Enemy|Weapon", meta = (RowType = "/Script/LOCKONARENA.RifleTableRow"))
	FDataTableRowHandle RifleTableRowHandle; // 4

public:	
	UPROPERTY(EditAnywhere, Category = "Enemy|Animation")
	UAnimMontage* HitMontage = nullptr;

};


UCLASS()
class LOCKONARENA_API AEnemyBase : public ABaseCharacter
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
	virtual void SetData(const FDataTableRowHandle& InRowHandle) override;

public:
	virtual float TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

public:
	UFUNCTION()
	virtual void OnMontageEnd(UAnimMontage* Montage, bool bInterrupted);

	virtual UEnemyStateComponent* GetState() { return EnemyState; }

	UPROPERTY(VisibleAnywhere)
	UEnemyStateComponent* EnemyState = nullptr;
	UDataTable* DataTable = nullptr;
	const FEnemyBaseTableRow* DataTableRow = nullptr;


	UEnemyAnimInstance* AnimInstance = nullptr;

	UPROPERTY(VisibleAnywhere)
	UWeaponChildActorComponent* Weapon = nullptr;

	float StackDamage = 0.f; // 일정 스택이 되면 Montage재생
};
