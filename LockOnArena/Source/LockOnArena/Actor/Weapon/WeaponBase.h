// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Character/Animation/AnimInstance/InGameAnimInstance.h"

#include "WeaponBase.generated.h"

class AWeaponBase;
class UInGameAnimInstance;
class UStaticMeshComponent;
class USkeletalMeshComponent;
class ADefaultCharacter;
class UCharacterStateComponent;
class AEffect;
class USkillBaseComponent;
class AInGamePlayerController;

USTRUCT()
struct LOCKONARENA_API FWeaponBaseTableRow : public FTableRowBase
{
	GENERATED_BODY()

public: // 
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
	TSubclassOf<UInGameAnimInstance> AnimInstance = nullptr;

	UPROPERTY(EditAnywhere, Category = "Weapon|Animation")
	UAnimMontage* WeaponAttackMontage = nullptr;

	UPROPERTY(EditAnywhere, Category = "Weapon|Animation")
	UAnimMontage* WeaponChangeMontage = nullptr;	

	UPROPERTY(EditAnywhere, Category = "Weapon|Animation")
	UAnimMontage* UnEquipWeaponMontage = nullptr;

	UPROPERTY(EditAnywhere, Category = "Weapon|Animation")
	UAnimMontage* UnEquipWeapon = nullptr;

	UPROPERTY(EditAnywhere, Category = "Weapon|Animation")
	UAnimMontage* HitReactMontage = nullptr;	


public: // WeaponStatus
	UPROPERTY(EditAnywhere)
	float WeaponATK = 1.f;
public: // Skiil

	UPROPERTY(EditAnywhere, Category = "Weapon|Skiil", meta = (RowType = "/Script/LOCKONARENA.SkillBaseTableRow"))
	FDataTableRowHandle LockOnHandle;
	UPROPERTY(EditAnywhere, Category = "Weapon|Skiil")
	TSubclassOf<USkillBaseComponent> LockOnClass;


	UPROPERTY(EditAnywhere, Category = "Weapon|Skiil", meta = (RowType = "/Script/LOCKONARENA.SkillBaseTableRow"))
	FDataTableRowHandle Skill01;
	UPROPERTY(EditAnywhere, Category = "Weapon|Skiil")
	TSubclassOf<USkillBaseComponent> Skill01Class;
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
	UFUNCTION()
	virtual void Attack();

	// @TODO : 블루프린트 호출 가능성
	UFUNCTION()
	virtual void SwapEquipment();	

	UFUNCTION()
	virtual float GetLockOn_CD();
	UFUNCTION()
	virtual float GetLockOn_MaxCD();

	UFUNCTION()
	virtual float GetSkill01_CD();
	UFUNCTION()
	virtual float GetSkill01_MaxCD();

	UFUNCTION()
	virtual void OnMontageEnd(UAnimMontage* Montage, bool bInterrupted);

	virtual void UpdateCharacter();
public:
	UPROPERTY(VisibleAnywhere)
	USceneComponent* SceneComponent = nullptr;

	UPROPERTY(VisibleAnywhere)
	USkeletalMeshComponent* SkeletalMeshComponent = nullptr;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* StaticMeshComponent = nullptr;

public:
	FDataTableRowHandle DataHandle;
	USkeletalMesh* SkeletalMesh = nullptr;

	UStaticMesh* StaticMesh = nullptr;

	UInGameAnimInstance* AnimInstance = nullptr;
	UDataTable* DataTable = nullptr;
public:
	const FWeaponBaseTableRow* DataTableRow = nullptr;

	UPROPERTY(VisibleAnywhere)
	ADefaultCharacter* OwnerCharacter = nullptr;

	UPROPERTY(VisibleAnywhere)
	AInGamePlayerController* CharacterController = nullptr;

	UPROPERTY(VisibleAnywhere)
	UCharacterStateComponent* CharacterState = nullptr;

public: // WeaponStatus
	float WeaponATK = 1.f;

public: // Skill
	USkillBaseComponent* LockOn = nullptr;
	FVector TargetLocation;
	USkillBaseComponent* Skill01 = nullptr;
	//UPROPERTY(VisibleAnywhere)
	//AEffect* MuzzleEffect = nullptr;
};
