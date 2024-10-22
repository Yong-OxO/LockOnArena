// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Effect.generated.h"


class AEffect;
class UParticleSystem;
class UParticleSystemComponent;

USTRUCT()
struct LOCKONARENA_API FEffectTableRow : public FTableRowBase
{
	GENERATED_BODY()
	FEffectTableRow();

public:
	UPROPERTY(EditAnywhere, Category = "Effect")
	TSubclassOf<AEffect> EffectClass;

	UPROPERTY(EditAnywhere, Category = "Effect")
	TObjectPtr<UParticleSystem> Particle;

	UPROPERTY(EditAnywhere, Category = "Effect")
	FTransform Transform = FTransform::Identity;

	UPROPERTY(EditAnywhere, Category = "Effect")
	float PlaySpeed = 1.f;
};

UCLASS()
class LOCKONARENA_API AEffect : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEffect();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	virtual void Play(const FDataTableRowHandle& InHandle,const FVector InLocation, const FRotator InRotation);

	UFUNCTION()
	virtual void SetData(const FDataTableRowHandle& InHandle);

protected:
	UPROPERTY(VisibleAnywhere)
	USceneComponent* SceneComponent = nullptr;

	UPROPERTY()
	UParticleSystemComponent* ParticleComponent = nullptr;

	UPROPERTY()
	FTransform Transform = FTransform::Identity;

	UPROPERTY(EditAnywhere, meta = (RowType = "/Script/LOCKONARENA.EffectTableRow"))
	FDataTableRowHandle RowHandle;
};
