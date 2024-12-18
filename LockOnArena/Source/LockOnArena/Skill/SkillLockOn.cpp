// Fill out your copyright notice in the Description page of Project Settings.


#include "Skill/SkillLockOn.h"
#include "GameFramework/Actor.h"
#include "Actor/Weapon/WeaponBase.h"
#include "Character/DefaultCharacter.h"
#include "Character/InGamePlayerController.h"
#include "Character/CharacterStateComponent.h"
#include "Camera/CameraComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Engine/SkeletalMeshSocket.h"
#include "Components/SkeletalMeshComponent.h"
#include "Enemy/EnemyBase.h"
#include "GameFramework/SpringArmComponent.h"

void USkillLockOn::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (bIsLocking || CharacterState->GetLockOn()) // && bOverlap
	{
		LockOn(DeltaTime);
	}
}

void USkillLockOn::SetData(const FDataTableRowHandle& InHandle)
{
	Super::SetData(InHandle);

	FLockOnTableRow* DataRow = InHandle.GetRow<FLockOnTableRow>(TEXT("DataRow"));
	DetectionDist = DataRow->DetectionDist;	
}

void USkillLockOn::PlaySkill()
{
	Super::PlaySkill();

	if (RemainCoolDown > 0)
	{
		UE_LOG(LogTemp, Display, TEXT("Cooldown"));
		bCanPlay = false;
		return;
	}
	RemainCoolDown = MaxCooldown;
	StartLockOnPlay();
}

void USkillLockOn::StartLockOnPlay()
{
	CharacterState->SetLockOnPlaying(true);

	bIsLocking = true;

	RemainCoolDown = RemainCoolDown;
	CharacterState->CanLockOn = false;

	Target = FindTarget();

		GetOwner()->GetWorldTimerManager().SetTimer(
		TimerHandle,   // FTimerHandle 변수
		this,          // 타이머를 설정할 객체
		&ThisClass::StopLockOnPlay, // 실행할 함수
		0.5f,          // 대기 시간(초 단위)
		false          // 반복 여부 (false면 한 번만 실행)
	);
}

void USkillLockOn::StopLockOnPlay()
{
	CharacterState->SetLockOnPlaying(false);
	bIsLocking = false;

	GetWorld()->GetTimerManager().ClearTimer(TimerHandle);

	GetOwner()->GetWorldTimerManager().SetTimer(
		TimerHandle,   // FTimerHandle 변수
		this,          // 타이머를 설정할 객체
		&ThisClass::CheckLockOn, // 실행할 함수
		0.1f,          // 대기 시간(초 단위)
		false          // 반복 여부 (false면 한 번만 실행)
	);
}

void USkillLockOn::LockOn(const float DeltaTime)
{
	if (Target) // 탐지 됐다면 회전
	{
		USpringArmComponent* Arm = ControlledCharacter->GetComponentByClass<USpringArmComponent>();
		USkeletalMeshComponent* TargetSkeletal = Target->GetComponentByClass<USkeletalMeshComponent>();
		// @TODO : SoketName
		const USkeletalMeshSocket* TargetSocket = TargetSkeletal->GetSocketByName(FName(TEXT("LockOnTarget")));
		TargetLocation = TargetSkeletal->GetSocketLocation(FName(TEXT("LockOnTarget")));
		Weapon->TargetLocation = TargetLocation;
		//ControlledCharacter;

		// 캐릭터 기준으로 돌려.
		// 돌리면 카메라의 월드 위치를 얻어
		// 그 위치에서 다시 적을 바라보는 방향을 계산
		// 그 방향을 다시 케릭터에 적용

		FVector ArmLocation = Arm->GetComponentLocation(); //V1.Y = 0.f/* * Mul*/;
		FRotator TargerRotation = UKismetMathLibrary::FindLookAtRotation(ArmLocation, TargetLocation);
		//Controller->SetControlRotation(TargerRotation);

		Arm->AddRelativeLocation(FVector(0., 9.0, 0.));

		FVector V2 = Arm->GetComponentLocation(); //V2.Y += 12.5f/* * Mul*/;
		FRotator ToTargetRotation = UKismetMathLibrary::FindLookAtRotation(V2, TargetLocation);


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

void USkillLockOn::CheckLockOn()
{
	FCollisionQueryParams CollisionQueryParams;
	CollisionQueryParams.AddIgnoredActor(GetOwner());

	// Debugline그려서 lockon이 성공했는지
	UCameraComponent* Camera = ControlledCharacter->GetComponentByClass<UCameraComponent>();

	FVector StartLocation = Camera->GetComponentLocation();
	FRotator StartRotation = Camera->GetComponentRotation();
	FVector NormalVector = StartRotation.Vector();

	StartLocation = StartLocation + NormalVector * 40.f;
	FVector EndLocation = StartLocation + NormalVector * 2000.f; // @TODO : Camera의 Location만큼 보정

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
		ControlledCharacter->GetState()->SetTargetLocation(TargetLocation);
	}

	GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
}

AEnemyBase* USkillLockOn::FindTarget()
{
	TArray<FOverlapResult> OverlapResults;

	FVector Location = ControlledCharacter->GetActorLocation();
	FQuat Quat = ControlledCharacter->GetActorQuat();
	FCollisionShape Sphere = FCollisionShape::MakeSphere(DetectionDist);

	Overlap = GetWorld()->OverlapMultiByChannel(
		OverlapResults,
		Location,
		Quat,
		ECollisionChannel::ECC_GameTraceChannel1,
		Sphere);

	if (OverlapResults.Num() == 0) { return nullptr; }
		USpringArmComponent* Arm = ControlledCharacter->GetComponentByClass<USpringArmComponent>();
		UCameraComponent* Camera = ControlledCharacter->GetComponentByClass<UCameraComponent>();

		Target = nullptr;
		Target = Cast<AEnemyBase>(OverlapResults[0].GetActor());

		FOverlapResult FirstOverlap;

		float CurrentAngle = 0; // 현재 가장 작은 각도
		float TempAngle = 0; // 비교 대상이 되는 각도



		for (int i = 0; i < OverlapResults.Num(); ++i)
		{
			FVector TargetVector = Target->GetActorLocation() - Camera->GetComponentLocation();
			AActor* Temp = OverlapResults[i].GetActor();
			FVector TempVector = OverlapResults[i].GetActor()->GetActorLocation() - Camera->GetComponentLocation(); // 비교대상

			CurrentAngle = GetAngleBetweenVectors(TargetVector, Camera->GetForwardVector());
			TempAngle = GetAngleBetweenVectors(TempVector, Camera->GetForwardVector());

			if (TempAngle < CurrentAngle)
			{
				FirstOverlap = OverlapResults[i];
				Target = Cast<AEnemyBase>(OverlapResults[i].GetActor());
				TargetLocation = Target->GetActorLocation();
			}
		}
	
	return Target;
}

float USkillLockOn::GetAngleBetweenVectors(const FVector& VectorA, const FVector& VectorB)
{
	FVector NormalizedA = VectorA.GetSafeNormal();
	FVector NormalizedB = VectorB.GetSafeNormal(); 

	// 벡터의 내적을 계산 
	float DotProduct = FVector::DotProduct(NormalizedA, NormalizedB); 

	// 코사인의 역함수를 이용해 각도를 라디안 단위로 계산 
	float AngleInRadians = FMath::Acos(DotProduct); 

	// 라디안을 각도로 변환 
	float AngleInDegrees = FMath::RadiansToDegrees(AngleInRadians);

	return FMath::Abs(AngleInDegrees);
}
