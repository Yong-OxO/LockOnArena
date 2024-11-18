// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actor/Trigger/ArenaPortal.h"
#include "BossClearPortal.generated.h"


class UStaticMeshComponent;

UCLASS()
class LOCKONARENA_API ABossClearPortal : public AArenaPortal
{
	GENERATED_BODY()


public:
	ABossClearPortal();
	virtual void ActivePortal();

	virtual void Tick(float DeltaSeconds) override;

public:
	UPROPERTY(EditAnywhere)
	TObjectPtr<UStaticMeshComponent> StaticMeshComponent = nullptr;

protected:
	FHitResult HitResult;
	FVector UpVector;
};
