// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/InGamePlayerController.h"
#include "Character/DefaultCharacter.h"
#include "Misc/Utils.h"
#include "Kismet/KismetMathLibrary.h"


AInGamePlayerController::AInGamePlayerController()
{
	static ConstructorHelpers::FObjectFinder<UDataTable> DataTableAsset (TEXT("/Script/Engine.DataTable'/Game/Blueprint/Data/DT_CharacterController.DT_CharacterController'"));
	WeaponTableRow = DataTableAsset.Object;
	IMC_Default = WeaponTableRow->InputMappingContext;
}

void AInGamePlayerController::BeginPlay()
{
	Super::BeginPlay();

	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	Subsystem->AddMappingContext(IMC_Default, 0);
}

void AInGamePlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	UEnhancedInputComponent* EnhanedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);

	if (const UInputAction* InputAction = FUtils::FindActionFromName(IMC_Default, FName("IA_Move")))
	{
		EnhanedInputComponent->BindAction(InputAction, ETriggerEvent::Triggered, this, &ThisClass::OnMove);
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

	ControlledCharacter->AddMovementInput(ForwardVector, InputVector.X * MoveForwardSpeed);
	ControlledCharacter->AddMovementInput(ForwardVector, InputVector.Y * MoveRightSpeed);
}
