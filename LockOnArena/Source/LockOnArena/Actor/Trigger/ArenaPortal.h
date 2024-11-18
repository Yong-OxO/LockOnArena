// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerBase.h"
#include "ArenaPortal.generated.h"


class USceneComponent;
class UBoxComponent;
class UUserWidget;


UCLASS()
class LOCKONARENA_API AArenaPortal : public AActor
{
	GENERATED_BODY()
public:
	AArenaPortal();
	
public:
	virtual void BeginPlay() override;

public:
	UPROPERTY(EditAnywhere)
	TObjectPtr<USceneComponent> SceneComponent = nullptr;
	
	UPROPERTY(EditAnywhere)
	TObjectPtr<UBoxComponent> Portal;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> WidgetClass;

	UPROPERTY(EditAnywhere, Category = "Level")
	TSoftObjectPtr<UWorld> NextLevel;

	UFUNCTION()
	virtual void OnTrigger(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
