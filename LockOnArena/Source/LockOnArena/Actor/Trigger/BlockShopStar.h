// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerBase.h"
#include "BlockShopStar.generated.h"


class USceneComponent;
class UBoxComponent;
class UStaticMeshComponent;

UCLASS()
class LOCKONARENA_API ABlockShopStar : public ATriggerBase
{
	GENERATED_BODY()
	
public:
	ABlockShopStar();

public:
	UPROPERTY(EditAnywhere)
	TObjectPtr<USceneComponent> SceneComponent = nullptr;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UStaticMeshComponent> StaticMeshComponent = nullptr;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UBoxComponent> CheckTrigger = nullptr;

protected:
	UFUNCTION()
	virtual void OnTrigger(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
