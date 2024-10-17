// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WeaponBase.generated.h"


class AWeaponBase;
class UInGameAnimInstance;
class UStaticMeshComponent;
class USkeletalMeshComponent;

USTRUCT()
struct LOCKONARENA_API FWeaponBaseTableRow : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Category = "Weapon|WeaponBase")
	USkeletalMesh* SkeletalMesh = nullptr;

	UPROPERTY(EditAnywhere, Category = "Weapon|WeaponBase")
	UStaticMesh* StaticMesh = nullptr;

	UPROPERTY(EditAnywhere, Category = "Weapon|WeaponBase")
	FTransform Transform = FTransform::Identity;

	UPROPERTY(EditAnywhere, Category = "Weapon|WeaponBase")
	TSubclassOf<AWeaponBase> WeaponClass = nullptr;

public:
	UPROPERTY(EditAnywhere, Category = "Weapon|Animation")
	TSubclassOf<UInGameAnimInstance> AimInstance = nullptr;

	UPROPERTY(EditAnywhere, Category = "Weapon|Animation")
	UAnimMontage* WeaponAttackMontage = nullptr;

	UPROPERTY(EditAnywhere, Category = "Weapon|Animation")
	UAnimMontage* HitReactMontage = nullptr;
};

UCLASS()
class LOCKONARENA_API AWeaponBase : public AActor
{
	GENERATED_BODY()
	
public:	
	AWeaponBase();



public:
	virtual void SetData(const FDataTableRowHandle& InRowHandle);

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

public:
	// Owner
	virtual void Attack();

public:
	UPROPERTY(VisibleAnywhere)
	TSubclassOf<USceneComponent> SceneComponent = nullptr;

	UPROPERTY(VisibleAnywhere)
	TSubclassOf<USkeletalMeshComponent> SkeletalMesh = nullptr;

	UPROPERTY(VisibleAnywhere)
	TSubclassOf<UStaticMeshComponent> StaticMesh = nullptr;	

public:
	const FWeaponBaseTableRow* DataTableRow = nullptr;

	UPROPERTY(EditAnywhere, meta = (RowType = "/Script/LOCKONARENA_API.WeaponBaseTableRow"))
	FDataTableRowHandle RowHandle;

	//Enemy (피격자)
};
