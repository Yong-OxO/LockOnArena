// Fill out your copyright notice in the Description page of Project Settings.


#include "Skill/SkillSystem.h"
#include "Character/DefaultCharacter.h"
#include "Enemy/EnemyBase.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Character/InGamePlayerController.h"
#include "Character/CharacterStateComponent.h"
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

	if (bLockOnPlay)
	{	
		LockOn(DeltaTime);
	}
}

void ASkillSystem::LockOn(const float DeltaTime)
{
	ControlledCharacter = GetOwner<ADefaultCharacter>(); // Owner의 class는 DefaultCharacter, WeaponBase에서 설정
	Controller = ControlledCharacter->GetController<AInGamePlayerController>();

	bool Overlap = false;

	FVector Location = ControlledCharacter->GetActorLocation();
	FQuat Quat = ControlledCharacter->GetActorQuat();

	FCollisionShape Sphere = FCollisionShape::MakeSphere(DetectionDist / 2);

	Overlap = GetWorld()->OverlapMultiByChannel(
		OverlapResults,
		Location,
		Quat,
		ECollisionChannel::ECC_GameTraceChannel1,
		Sphere);

	if (Overlap)
	{
		FOverlapResult FirstOverlap = OverlapResults[0];

		AEnemyBase* Target = Cast<AEnemyBase>(FirstOverlap.GetActor());
		USkeletalMeshComponent* TargetSkeletal = Target->GetComponentByClass<USkeletalMeshComponent>();
		// @TODO : SoketName
		const USkeletalMeshSocket* TargetSocket = TargetSkeletal->GetSocketByName(FName(TEXT("LockOnTarget")));

		//UCameraComponent* Camera = ControlledCharacter->GetComponentByClass<UCameraComponent>();
		//USpringArmComponent* Arm = ControlledCharacter->GetComponentByClass<USpringArmComponent>();

		//FVector ArmRelativceLocation = Arm->GetRelativeLocation();
		//FVector ArmLocation = CharacterLocation + ArmRelativceLocation;
		////FVector TargetLocation = TargetSocket->GetSocketLocation(TargetSkeletal) - CameraLocation;
		FVector TargetLocation = TargetSkeletal->GetSocketLocation(FName(TEXT("LockOnTarget")));

		//ControlledCharacter;

		// 캐릭터 기준으로 돌려.
		// 돌리면 카메라의 월드 위치를 얻어
		// 그 위치에서 다시 적을 바라보는 방향을 계산
		// 그 방향을 다시 케릭터에 적용
		USpringArmComponent* Arm = ControlledCharacter->GetComponentByClass<USpringArmComponent>();
		//FVector ArmLocation = Arm->GetComponentLocation();
		//FVector Dir = TargetLocation - ArmLocation; Dir.Normalize();
		//double Dot = FVector::DotProduct(Arm->GetForwardVector(), Dir);
		//float Mul = 1.f;
		//if (Dot < 0.f)
		//{
		//	Mul = -1.f;;
		//}

		FVector ArmLocation = Arm->GetComponentLocation(); //V1.Y = 0.f/* * Mul*/;
		FRotator TargerRotation = UKismetMathLibrary::FindLookAtRotation(ArmLocation, TargetLocation);
		//Controller->SetControlRotation(TargerRotation);

		Arm->AddRelativeLocation(FVector(0., 9.0, 0.));

		FVector V2 = Arm->GetComponentLocation(); //V2.Y += 12.5f/* * Mul*/;
		ToTargetRotation = UKismetMathLibrary::FindLookAtRotation(V2, TargetLocation);
		

		Arm->AddRelativeLocation(FVector(0., -9.0, 0.0));
		//Camera->SetWorldRotation(TargerRotation);
		//FRotator TargerRotation = (TargetLocation - CharacterLocation).Rotation();

		FRotator StartRotation = Controller->GetControlRotation();

		FQuat QuatStart = FQuat(StartRotation);
		FQuat QuatEnd = FQuat(ToTargetRotation);
		
		float InterpAlpha = DeltaTime * 10.f;

		if (InterpAlpha > 1)
		{
			InterpAlpha = 1.f;
		}

		FQuat QuatInterp = FQuat::Slerp(QuatStart, QuatEnd, InterpAlpha);
		FRotator RotatorInterp = QuatInterp.Rotator();
		
		Controller->SetControlRotation(RotatorInterp);
	}
}

void ASkillSystem::StartLockOnPlay()
{
	bLockOnPlay = true;


	GetWorldTimerManager().SetTimer(
		TimerHandle,   // FTimerHandle 변수
		this,          // 타이머를 설정할 객체
		&ThisClass::StopLockOnPlay, // 실행할 함수
		1.0f,          // 대기 시간(초 단위)
		false          // 반복 여부 (false면 한 번만 실행)
	);
}

void ASkillSystem::StopLockOnPlay()
{
	bLockOnPlay = false;

	GetWorld()->GetTimerManager().ClearTimer(TimerHandle);

	GetWorldTimerManager().SetTimer(
		TimerHandle,   // FTimerHandle 변수
		this,          // 타이머를 설정할 객체
		&ThisClass::CheckLockOn, // 실행할 함수
		0.2f,          // 대기 시간(초 단위)
		false          // 반복 여부 (false면 한 번만 실행)
	);	
}

void ASkillSystem::CheckLockOn()
{
	FCollisionQueryParams CollisionQueryParams;
	CollisionQueryParams.AddIgnoredActor(this);

	// Debugline그려서 lockon이 성공했는지
	UCameraComponent* Camera = ControlledCharacter->GetComponentByClass<UCameraComponent>();

	FVector StartLocation = Camera->GetComponentLocation();
	FRotator StartRotation = Camera->GetComponentRotation();
	FVector NormalVector = StartRotation.Vector();

	StartLocation = StartLocation + NormalVector * 40.f;
	FVector EndLocation = StartLocation + NormalVector * 1000;

	FHitResult HitResult;
	bLockOnSucceed = GetWorld()->LineTraceSingleByChannel(
		HitResult,
		StartLocation,
		EndLocation,
		ECollisionChannel::ECC_GameTraceChannel1,
		CollisionQueryParams);

	if (bLockOnSucceed)
	{
		ControlledCharacter->GetState()->SetLockOn(bLockOnSucceed);
	}

	GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
}
