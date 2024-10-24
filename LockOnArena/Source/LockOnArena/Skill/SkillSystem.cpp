// Fill out your copyright notice in the Description page of Project Settings.


#include "Skill/SkillSystem.h"
#include "Character/DefaultCharacter.h"
#include "Enemy/EnemyBase.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Character/InGamePlayerController.h"
#include "Engine/SkeletalMeshSocket.h"
#include "Camera/CameraComponent.h"

#include "Kismet/KismetMathLibrary.h"


// Sets default values
ASkillSystem::ASkillSystem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASkillSystem::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASkillSystem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool ASkillSystem::LockOn()
{
	ControlledCharacter = GetOwner<ADefaultCharacter>(); // Owner의 class는 DefaultCharacter, WeaponBase에서 설정
	Controller = ControlledCharacter->GetController<AInGamePlayerController>();

	bool bLockOn = false;

	FVector Location = ControlledCharacter->GetActorLocation();
	FQuat Quat = ControlledCharacter->GetActorQuat();

	FCollisionShape Sphere = FCollisionShape::MakeSphere(DetectionDist / 2);

	bLockOn = GetWorld()->OverlapMultiByChannel(
		OverlapResults,
		Location,
		Quat,
		ECollisionChannel::ECC_GameTraceChannel1,
		Sphere);

	if (bLockOn)
	{
		FOverlapResult FirstOverlap = OverlapResults[0];

		AEnemyBase* Target = Cast<AEnemyBase>(FirstOverlap.GetActor());
		USkeletalMeshComponent* TargetSkeletal = Target->GetComponentByClass<USkeletalMeshComponent>();
		// @TODO : SoketName
		const USkeletalMeshSocket* TargetSocket = TargetSkeletal->GetSocketByName(FName(TEXT("LockOnTarget")));

		UCameraComponent* Camera = ControlledCharacter->GetComponentByClass<UCameraComponent>();


		FVector CharacterLocation = ControlledCharacter->GetActorLocation() + FVector(0.0, 30.0 + 20, 90.0);
		FVector TargetLocation = TargetSocket->GetSocketLocation(TargetSkeletal);

		FRotator TargerRotation = (TargetLocation - CharacterLocation).Rotation();
		Controller->SetControlRotation(TargerRotation);
	}



	return bLockOn;
}