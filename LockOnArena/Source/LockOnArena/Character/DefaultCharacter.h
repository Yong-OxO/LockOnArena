// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "DefaultCharacter.generated.h"

// @TODO : SetData -> 무기가 바뀌면 호출, 애니메이션 등 교체
// 맨손(기본) 애니메이션에서 변경
// 무기마다 실행시킬 애니메이션 보유중
// 무기 DataTable로 CharacterDataTable의 값을 변경
class UStaticMeshComponent;
class UCharacterStateComponent;

USTRUCT()
struct LOCKONARENA_API FDefaultCharacterTableRow : public FTableRowBase
{
	GENERATED_BODY()
};


UCLASS()
class LOCKONARENA_API ADefaultCharacter : public ACharacter
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

public:
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* Weapon_Static = nullptr;

	UPROPERTY(EditAnywhere)
	USkeletalMeshComponent* Weapon_Skeletal = nullptr;

	UPROPERTY(VisibleAnywhere)
	UCharacterStateComponent* CharacterState = nullptr;
};
