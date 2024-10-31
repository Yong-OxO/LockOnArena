// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Actor/Weapon/WeaponBase.h"

#include "BaseCharacter.generated.h"


UCLASS()
class LOCKONARENA_API ABaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABaseCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void SetData(const FDataTableRowHandle& InRowHandle) PURE_VIRTUAL(ABaseCharacter::SetData, ;);
public:

	virtual void WeaponInit();

	// ActiveWeapon만 갖고 Weapon Hanlde 및 WeaponChildActor는 각자 구현
	AWeaponBase* ActiveWeapon = nullptr;
};
