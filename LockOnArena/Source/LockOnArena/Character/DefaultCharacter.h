// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/BaseCharacter.h"
#include "Actor/Weapon/WeaponBase.h"
#include "Actor/Weapon/RifleBase.h"
#include "DefaultCharacter.generated.h"


// @TODO : SetData -> 무기가 바뀌면 호출, 애니메이션 등 교체
// 맨손(기본) 애니메이션에서 변경
// 무기마다 실행시킬 애니메이션 보유중
// 무기 DataTable로 CharacterDataTable의 값을 변경

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnEnemyTakeDamage, const AActor*, Enemy);

class UStaticMeshComponent;
class UCharacterStateComponent;
class UWeaponChildActorComponent;
class UCameraComponent;
class USpringArmComponent;
class ADefaultHUD;
class AInGamePlayerController;

USTRUCT()
struct LOCKONARENA_API FDefaultCharacterTableRow : public FTableRowBase
{
	GENERATED_BODY()
public:
	//WeaponTableRowHandle
	UPROPERTY(EditAnywhere, meta = (RowType = "/Script/LOCKONARENA.WeaponBaseTableRow"))
	FDataTableRowHandle WeaponBaseTableRowHandle; // 1

	UPROPERTY(EditAnywhere, meta = (RowType = "/Script/LOCKONARENA.WeaponBaseTableRow"))
	FDataTableRowHandle PunchTableRowHandle; // 2

	UPROPERTY(EditAnywhere, meta = (RowType = "/Script/LOCKONARENA.WeaponBaseTableRow"))
	FDataTableRowHandle KnifeTableRowHandle; // 3
	
	UPROPERTY(EditAnywhere, meta = (RowType = "/Script/LOCKONARENA.RifleTableRow"))
	FDataTableRowHandle RifleTableRowHandle; // 4

	UPROPERTY(EditAnywhere, meta = (RowType = "/Script/LOCKONARENA.CharacterStateTableRow"))
	FDataTableRowHandle CharacterStateTableRowHandle;

public:
	UPROPERTY(EditAnywhere, Category = "Character|Animation")
	UAnimMontage* HitMontage = nullptr;	

	UPROPERTY(EditAnywhere, Category = "Character|Animation")
	UAnimMontage* SkillHitMontage = nullptr;

	UPROPERTY(EditAnywhere, Category = "Character|Animation")
	UAnimMontage* KneelToStand = nullptr;
	
	UPROPERTY(EditAnywhere, Category = "Character|Animation")
	UAnimMontage* DeathMontage = nullptr;
};


UCLASS()
class LOCKONARENA_API ADefaultCharacter : public ABaseCharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ADefaultCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void SetData(const FDataTableRowHandle& InRowHandle) override;

	virtual UCharacterStateComponent* GetState() { return CharacterState; }

	FTimerHandle TimerHandle;
	FTimerHandle SKillHitTimerHandle;
	UFUNCTION()
	virtual float TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	UFUNCTION()
	virtual void OnSkillHit();

	UFUNCTION()
	virtual void OnDIe();


public:
	UPROPERTY(EditAnywhere)
	UCharacterStateComponent* CharacterState = nullptr;

	UPROPERTY()
	AInGamePlayerController* PlayerController = nullptr;

	UDataTable* DataTable = nullptr;

	const FDefaultCharacterTableRow* DataTableRow = nullptr;

public: // Camera
	UPROPERTY(VisibleAnywhere, Category = "Camera")
	USpringArmComponent* SpringArmComponent;

	UPROPERTY(VisibleAnywhere, Category = "Camera")
	UCameraComponent* CameraComponent;
	
public: // HUD, Widget
	UPROPERTY(EditAnywhere, Category = "Widget")
	ADefaultHUD* DefaultHUD;
	
	UFUNCTION()
	virtual void VisibleEnemyHpBar(const AActor* DamagedEnemy);
	FOnEnemyTakeDamage OnEnemyTakeDamage;

	
public: // WeaponManage
	virtual void WeaponInit() override;
	virtual void SwitchWeapon(int InValue);


	AWeaponBase* ActiveWeapon = nullptr;

protected:

	UPROPERTY(EditAnywhere, Category = "Weapons")
	TArray<FDataTableRowHandle> WeaponDataHandles;

	TArray<UWeaponChildActorComponent*> WeaponInstances;
	UWeaponChildActorComponent* WeaponInstance;


};
