// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "EnemyBase.generated.h"

class UWeaponChildActorComponent;
class UEnemyStateComponent;

USTRUCT()
struct LOCKONARENA_API FEnemyBaseTableRow : public FTableRowBase
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, meta = (RowType = "/Script/LOCKONARENA.WeaponBaseTableRow"))
	FDataTableRowHandle WeaponBaseTableRowHandle; // 1

	UPROPERTY(EditAnywhere, meta = (RowType = "/Script/LOCKONARENA.WeaponBaseTableRow"))
	FDataTableRowHandle PunchTableRowHandle; // 2

	UPROPERTY(EditAnywhere, meta = (RowType = "/Script/LOCKONARENA.WeaponBaseTableRow"))
	FDataTableRowHandle KnifeTableRowHandle; // 3

	UPROPERTY(EditAnywhere, meta = (RowType = "/Script/LOCKONARENA.RifleTableRow"))
	FDataTableRowHandle RifleTableRowHandle; // 4

	//UPROPERTY(EditAnywhere)
	//UCharacterStateComponent* CharacterState = nullptr;
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
	virtual void SetData(const FDataTableRowHandle& InRowHandle);

public:
	UPROPERTY(VisibleAnywhere)
	UWeaponChildActorComponent* Weapon = nullptr;

	UPROPERTY(VisibleAnywhere)
	UEnemyStateComponent* CharacterState = nullptr;

	UDataTable* DataTable = nullptr;

	const FEnemyBaseTableRow* DataTableRow = nullptr;
};
