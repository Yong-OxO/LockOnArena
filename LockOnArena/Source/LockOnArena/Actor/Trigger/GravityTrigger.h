// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GravityTrigger.generated.h"

class USceneComponent;
class UBoxComponent;

UCLASS()
class LOCKONARENA_API AGravityTrigger : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGravityTrigger();

public:
	UPROPERTY(EditAnywhere)
	TObjectPtr<USceneComponent> SceneComponent = nullptr;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UBoxComponent> CheckTrigger = nullptr;

	UPROPERTY(EditAnywhere, Category = "Gravity")
	float CustomGravityScale = 1.f;
protected:
	UFUNCTION()
	virtual void OnTrigger(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	virtual void EndTrigger (UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
