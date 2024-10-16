// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/InGamePlayerController.h"
#include "Character/DefaultCharacter.h"
#include "Misc/Utils.h"
#include "Kismet/KismetMathLibrary.h"
#include "GameFramework/CharacterMovementComponent.h"


AInGamePlayerController::AInGamePlayerController()
{


	static ConstructorHelpers::FObjectFinder<UDataTable> DataTableAsset (TEXT("/Script/Engine.DataTable'/Game/Blueprint/Data/DT_CharacterController.DT_CharacterController'"));
	DataTable = DataTableAsset.Object;
	ControllerTableRow = DataTable->FindRow<FCharacterControllerTableRow>(FName("DefaultAction"), TEXT("PlayerController DataTable"));

	IMC_Default = ControllerTableRow->InputMappingContext;
	Sensitivity = 0.7f;
	
}

void AInGamePlayerController::BeginPlay()
{
	Super::BeginPlay();

	ControlledCharacter = CastChecked<ADefaultCharacter>(GetPawn());

	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	Subsystem->AddMappingContext(IMC_Default, 0);

	CharacterMovement = ControlledCharacter->GetCharacterMovement();
	CharacterMovement->JumpZVelocity = 530.f;
	CharacterMovement->AirControl = 0.2f;
}

void AInGamePlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	UEnhancedInputComponent* EnhanedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);

	if (const UInputAction* InputAction = FUtils::FindActionFromName(IMC_Default, FName("IA_Move")))
	{
		EnhanedInputComponent->BindAction(InputAction, ETriggerEvent::Triggered, this, &ThisClass::OnMove);
	}
	if (const UInputAction* InputAction = FUtils::FindActionFromName(IMC_Default, FName("IA_Look")))
	{
		EnhanedInputComponent->BindAction(InputAction, ETriggerEvent::Triggered, this, &ThisClass::OnLook);
	}
	if (const UInputAction* InputAction = FUtils::FindActionFromName(IMC_Default, FName("IA_Jump")))
	{
		EnhanedInputComponent->BindAction(InputAction, ETriggerEvent::Triggered, this, &ThisClass::OnJump);
	}
	if (const UInputAction* InputAction = FUtils::FindActionFromName(IMC_Default, FName("IA_Jump")))
	{
		EnhanedInputComponent->BindAction(InputAction, ETriggerEvent::Triggered, this, &ThisClass::OnJump);
	}
}

void AInGamePlayerController::OnMove(const FInputActionValue& InValue)
{
	// @TODO : 움직일 수 있는 상황인지 조건 체크
	
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
	FVector2D InputVector = InValue.Get<FVector2D>();	

	AddYawInput(InputVector.X * Sensitivity);
	AddPitchInput(InputVector.Y * Sensitivity);
}

void AInGamePlayerController::OnJump(const FInputActionValue& InValue)
{
	// @TODO : 움직일 수 있는 상황인지 조건 체크

	ControlledCharacter = CastChecked<ADefaultCharacter>(GetPawn());
	int32 JumpCurrentCount = ControlledCharacter->JumpCurrentCount;
	int32 MaxJumpCount = ControlledCharacter->JumpMaxCount;

	if (JumpCurrentCount < MaxJumpCount)
	{
		ControlledCharacter->Jump();
	}
}

void AInGamePlayerController::OnStopJump(const FInputActionValue& InValue)
{
	ControlledCharacter = CastChecked<ADefaultCharacter>(GetPawn());
	ControlledCharacter->StopJumping();
}
