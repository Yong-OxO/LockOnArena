// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/InGamePlayerController.h"
#include "Character/DefaultCharacter.h"
#include "Character/CharacterStateComponent.h"
#include "Misc/Utils.h"
#include "Kismet/KismetMathLibrary.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Actor/Weapon/WeaponBase.h"
#include "Actor/Weapon/WeaponChildActorComponent.h"
#include "Skill/SkillChildActorComponent.h"
#include "Skill/SkillSystem.h"

AInGamePlayerController::AInGamePlayerController()
{
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UDataTable> DataTableAsset (TEXT("/Script/Engine.DataTable'/Game/Blueprint/Data/DT_CharacterController.DT_CharacterController'"));
	DataTable = DataTableAsset.Object;
	// @TODO : RowName namespace
	ControllerTableRow = DataTable->FindRow<FCharacterControllerTableRow>(FName("DefaultAction"), TEXT("PlayerController DataTable"));

	IMC_Default = ControllerTableRow->InputMappingContext;
	Sensitivity = 0.7f;
}

void AInGamePlayerController::BeginPlay()
{
	Super::BeginPlay();
	{
		ControlledCharacter = CastChecked<ADefaultCharacter>(GetPawn());
		CharacterState = ControlledCharacter->GetState();
		//WeaponChildActor = ControlledCharacter->Weapon;
	}
	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	Subsystem->AddMappingContext(IMC_Default, 0);
	{
		CharacterMovement = ControlledCharacter->GetCharacterMovement();
		CharacterMovement->JumpZVelocity = 530.f;
		CharacterMovement->AirControl = 0.2f;
		CharacterMovement->MaxWalkSpeed = WalkSpeed;
	}
}

void AInGamePlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);

	// Input Action Mapping
	if (const UInputAction* InputAction = FUtils::FindActionFromName(IMC_Default, FName("IA_Move"))) // Move
	{
		EnhancedInputComponent->BindAction(InputAction, ETriggerEvent::Triggered, this, &ThisClass::OnMove);
	}

	if (const UInputAction* InputAction = FUtils::FindActionFromName(IMC_Default, FName("IA_Look"))) // Look
	{
		EnhancedInputComponent->BindAction(InputAction, ETriggerEvent::Triggered, this, &ThisClass::OnLook);
	}

	if (const UInputAction* InputAction = FUtils::FindActionFromName(IMC_Default, FName("IA_Jump"))) // Jump
	{
		EnhancedInputComponent->BindAction(InputAction, ETriggerEvent::Triggered, this, &ThisClass::OnJump);
	}
	if (const UInputAction* InputAction = FUtils::FindActionFromName(IMC_Default, FName("IA_Jump")))
	{
		EnhancedInputComponent->BindAction(InputAction, ETriggerEvent::Completed, this, &ThisClass::StopJump);
	}

	if (const UInputAction* InputAction = FUtils::FindActionFromName(IMC_Default, FName("IA_Run"))) // Run
	{
		EnhancedInputComponent->BindAction(InputAction, ETriggerEvent::Triggered, this, &ThisClass::OnRun);
	}	
	if (const UInputAction* InputAction = FUtils::FindActionFromName(IMC_Default, FName("IA_Run")))
	{
		EnhancedInputComponent->BindAction(InputAction, ETriggerEvent::Completed, this, &ThisClass::StopRun);
	}

	if (const UInputAction* InputAction = FUtils::FindActionFromName(IMC_Default, FName("IA_Attack"))) // Attack
	{
		EnhancedInputComponent->BindAction(InputAction, ETriggerEvent::Triggered, this, &ThisClass::OnAttack);
	}

	if (const UInputAction* InputAction = FUtils::FindActionFromName(IMC_Default, FName("IA_Equip01")))
	{
		EnhancedInputComponent->BindAction(InputAction, ETriggerEvent::Started, this, &ThisClass::OnEquip);
	}

	if (const UInputAction* InputAction = FUtils::FindActionFromName(IMC_Default, FName("IA_LockOn")))
	{
		EnhancedInputComponent->BindAction(InputAction, ETriggerEvent::Started, this, &ThisClass::OnLockOn);
	}
}

void AInGamePlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (bIsRun) { ToRun(DeltaTime); }
	else { ToWalk(DeltaTime); }

}

void AInGamePlayerController::OnMove(const FInputActionValue& InValue)
{
	if (!CharacterState->CanMove() || CharacterState->GetLockOn()) { return; }

	ControlledCharacter = CastChecked<ADefaultCharacter>(GetPawn());

	const FVector2D InputVector = InValue.Get<FVector2D>();

	const FRotator CharacterRotation = ControlledCharacter->GetActorRotation();
	const FRotator CharacterRotationYaw = FRotator(0.0, CharacterRotation.Yaw, 0.0);

	const FVector ForwardVector = UKismetMathLibrary::GetForwardVector(CharacterRotationYaw);
	const FVector RightVector = UKismetMathLibrary::GetRightVector(CharacterRotationYaw);

	if (InputVector.X >= 0)
	{
		ControlledCharacter->AddMovementInput(ForwardVector, InputVector.X);
		ControlledCharacter->AddMovementInput(RightVector, InputVector.Y * MoveRightSpeed);
	}
	else if (InputVector.X <= 0)
	{
		ControlledCharacter->AddMovementInput(ForwardVector, InputVector.X * MoveBackwardSpeed);
		ControlledCharacter->AddMovementInput(RightVector, InputVector.Y * MoveRightSpeed);
	}
}



void AInGamePlayerController::OnLook(const FInputActionValue& InValue)
{
	ControlledCharacter = CastChecked<ADefaultCharacter>(GetPawn());
	if (CharacterState->GetLockOn()) // LockOn중이면 마우스 움직임 x
	{
		return;
	}
	FVector2D InputVector = InValue.Get<FVector2D>();	

	AddYawInput(InputVector.X * Sensitivity);
	AddPitchInput(InputVector.Y * Sensitivity);
}

void AInGamePlayerController::OnJump(const FInputActionValue& InValue)
{
	ControlledCharacter = CastChecked<ADefaultCharacter>(GetPawn());
	if (!CharacterState->CanMove() || CharacterState->GetLockOn())
	{
		return;
	}

	ControlledCharacter = CastChecked<ADefaultCharacter>(GetPawn());
	int32 JumpCurrentCount = ControlledCharacter->JumpCurrentCount;
	int32 MaxJumpCount = ControlledCharacter->JumpMaxCount;

	if (JumpCurrentCount < MaxJumpCount)
	{
		ControlledCharacter->Jump();
	}
}

void AInGamePlayerController::StopJump(const FInputActionValue& InValue)
{
	ControlledCharacter = CastChecked<ADefaultCharacter>(GetPawn());
	ControlledCharacter->StopJumping();
}

void AInGamePlayerController::OnRun(const FInputActionValue& InValue)
{
	bIsRun = true;
}

void AInGamePlayerController::StopRun(const FInputActionValue& InValue)
{
	bIsRun = false;
}

void AInGamePlayerController::OnAttack(const FInputActionValue& InValue)
{
	 // @TODO : Num, 공격 불가 알림	
	if (CharacterState->GetLockOn())
	{
		// @TODO : CharacterState의 공격력 2배 버프 1초
		CharacterState->SetLockOn(false); 
	}
	ControlledCharacter = CastChecked<ADefaultCharacter>(GetPawn());
	CharacterState = ControlledCharacter->CharacterState;

	//if (CharacterState->CanAttack())
	//{
	ControlledCharacter->ActiveWeapon->Attack();
	//}
}

void AInGamePlayerController::OnEquip(const FInputActionValue& InValue)
{
	//WeaponType InKey = WeaponType::Knife;

	ControlledCharacter = CastChecked<ADefaultCharacter>(GetPawn());
	CharacterState = ControlledCharacter->GetState();
	int Value = (int)InValue.Get<float>();
	ControlledCharacter->SwitchWeapon(Value);
	//if (!CharacterState->CanAttack() || CharacterState->GetLockOn())
	//{
	//	return;
	//}
	//WeaponType InKey = (WeaponType)InValue.Get<float>();
	//if (InKey == EquipmentType) { return; }

	//UWeaponChildActorComponent* CharacterWeapon = ControlledCharacter->Weapon;

	//switch (InKey)
	//{
	//	case WeaponType::NonWeapon:
	//	{
	//		CharacterWeapon->SetData(ControlledCharacter->DataTableRow->WeaponBaseTableRowHandle);
	//		ControlledCharacter->CharacterState->SetEquipmentType(WeaponType::NonWeapon);
	//		break;
	//	}
	//	case WeaponType::Punch:
	//	{
	//		CharacterWeapon->SetData(ControlledCharacter->DataTableRow->PunchTableRowHandle);
	//		ControlledCharacter->CharacterState->SetEquipmentType(WeaponType::Punch);
	//		break;
	//	}
	//	case WeaponType::Knife:
	//	{
	//		CharacterWeapon->SetData(ControlledCharacter->DataTableRow->KnifeTableRowHandle);
	//		ControlledCharacter->CharacterState->SetEquipmentType(WeaponType::Knife);
	//		break;
	//	}		
	//	case WeaponType::Rifle:
	//	{
	//		CharacterWeapon->SetData(ControlledCharacter->DataTableRow->RifleTableRowHandle);
	//		ControlledCharacter->CharacterState->SetEquipmentType(WeaponType::Rifle);
	//		break;
	//	}
	//}

	//EquipmentType = ControlledCharacter->CharacterState->GetEquipmentType();
	//AWeaponBase* Weapon = CastChecked<AWeaponBase>(CharacterWeapon->GetChildActor());
	//Weapon->SwapEquipment();
}

void AInGamePlayerController::OnLockOn(const FInputActionValue& InValue)
{
	ControlledCharacter = CastChecked<ADefaultCharacter>(GetPawn());
	//ASkillSystem* SkillSystem = Cast<ASkillSystem>(CharacterState->GetSkillSystem()->GetChildActor());
	//if (!SkillSystem->CanPlaySkill()) // 스킬사용이 불가능일때
	//{
	//	UE_LOG(LogTemp, Display, TEXT("LockOn is CoolDown"));
	//	return;
	//}

	//SkillSystem->PlaySkill(0);
}

void AInGamePlayerController::ToRun(const float DeltaTime)
{
	// 여기서 조건 검사하고 Tick 실행까지 결정할지 말지
	float Alpha = 20 * DeltaTime;
	if (Alpha < 1)
	{
		CharacterMovement->MaxWalkSpeed = UKismetMathLibrary::Lerp(CharacterMovement->MaxWalkSpeed, RunSpeed, Alpha);
	}
	else
	{
		CharacterMovement->MaxWalkSpeed = UKismetMathLibrary::Lerp(CharacterMovement->MaxWalkSpeed, RunSpeed, 1);
	}
}

void AInGamePlayerController::ToWalk(const float DeltaTime)
{
	float Alpha = 20 * DeltaTime;
	if (Alpha < 1)
	{
		CharacterMovement->MaxWalkSpeed = UKismetMathLibrary::Lerp(CharacterMovement->MaxWalkSpeed, WalkSpeed, Alpha);
	}
	else
	{
		CharacterMovement->MaxWalkSpeed = UKismetMathLibrary::Lerp(CharacterMovement->MaxWalkSpeed, WalkSpeed, 1);
	}
}
