// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HomingProjectile.generated.h"

class UHomingProjectileComponent;
class AWeaponBase;


UCLASS()
class LOCKONARENA_API AHomingProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	AHomingProjectile();

	void SpawnProjectile(FVector StartLocation, FRotator StartRotation, FVector TargetLocation);

	FVector EnemyTargetLocation;
protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* StaticMeshComponent;

	UFUNCTION()
	void OnTrigger (UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
private:	
	UPROPERTY(VisibleAnywhere, Category = "Movement") 
	UHomingProjectileComponent* HomingComponent;

	UFUNCTION()
	void StartMovement();

	FTimerHandle TimerHandle;	
	AWeaponBase* Weapon = nullptr;
};
