// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ChildActorComponent.h"
#include "WeaponChildActorComponent.generated.h"


class AWeaponBase;

USTRUCT()
struct LOCKONARENA_API FWeaponChildBaseTableRow : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, meta = (RowType = "/Script/LOCKONARENA.WeaponBaseTableRow"))
	FDataTableRowHandle NoneWeapon;
	UPROPERTY(EditAnywhere, meta = (RowType = "/Script/LOCKONARENA.WeaponBaseTableRow"))
	FDataTableRowHandle PunchWeapon;
	UPROPERTY(EditAnywhere, meta = (RowType = "/Script/LOCKONARENA.WeaponBaseTableRow"))
	FDataTableRowHandle KnifeWeapon;
	UPROPERTY(EditAnywhere, meta = (RowType = "/Script/LOCKONARENA.WeaponBaseTableRow"))
	FDataTableRowHandle RifleWeapon;
};


UCLASS()
class LOCKONARENA_API UWeaponChildActorComponent : public UChildActorComponent
{
	GENERATED_BODY()

public:
	UWeaponChildActorComponent();

public:
	virtual void BeginPlay() override;

public:
	FWeaponChildBaseTableRow* DataTableRow = nullptr;

	UPROPERTY(EditAnywhere, Category = "Weapons")
	TArray<FDataTableRowHandle> WeaponDataHandles;

	UPROPERTY(EditAnywhere, Category = "Weapons")
	TArray<TSubclassOf<AWeaponBase>> WeaponClasses; // WeaponBase에 WeaponClass를 넣어준다.

	UPROPERTY(VisibleAnywhere, Category = "Weapons")
	TArray<AWeaponBase*> WeaponInstances;

	UPROPERTY()
	AWeaponBase* CurrentWeapon = nullptr; // 이 무기를 통해 실질적인 Attack, skill등 실행

	virtual void InitializeWeapons();

	virtual void SwitchWeapon(const int WeaponIndex);

public:
	virtual void SetData(const FDataTableRowHandle& InRowHandle);
	//virtual void SetData( const FDataTableRowHandle& InRowHandle);

};
