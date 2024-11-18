// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/DefaultCharacter.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "CharacterStateComponent.h"
#include "Actor/Weapon/WeaponChildActorComponent.h"
#include "Subsystem/WeaponSubsystem.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Character/InGamePlayerController.h"
#include "Widget/DefaultHUD.h"
#include "GameMode/ArenaGameInstance.h"
#include "Subsystem/CharacterSaveSubsystem.h"


// Sets default values
ADefaultCharacter::ADefaultCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	// @TODO : RowName namespace
	static ConstructorHelpers::FObjectFinder<UDataTable> DataTableAsset(TEXT("/Script/Engine.DataTable'/Game/Blueprint/Data/DT_BaseCharacter.DT_BaseCharacter'"));
	DataTable = DataTableAsset.Object;
	DataTableRow = DataTable->FindRow<FDefaultCharacterTableRow>(FName("Basic"), TEXT("CharacterDataTableRow"));


	CharacterState = CreateDefaultSubobject<UCharacterStateComponent>(TEXT("CharacterState"));


	/*static ConstructorHelpers::FObjectFinder<AActor> WeaponAsset(TEXT("/Script/Engine.Blueprint'/Game/Blueprint/Actor/Weapon/BP_Rifle.BP_Rifle'"));
	Weapon_Static->SetStaticMesh(WeaponAsset.Object);*/
	{
		//(X=4.000000,Y=30.000000,Z=90.000000)
		SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
		SpringArmComponent->SetupAttachment(RootComponent);
		CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
		CameraComponent->SetupAttachment(SpringArmComponent);

		FTransform Transform;
		Transform.SetLocation(FVector(0.0, 30.0, 90.0));
		SpringArmComponent->SetRelativeTransform(Transform);

		SpringArmComponent->TargetArmLength = 200.f;
		SpringArmComponent->SocketOffset = FVector(0.0, 10.0, 0.0);

		SpringArmComponent->bUsePawnControlRotation = true;
	}
	{
		
	}
}

// Called when the game starts or when spawned
void ADefaultCharacter::BeginPlay()
{
	Super::BeginPlay();

	CharacterState->SetData(DataTableRow->CharacterStateTableRowHandle);
	WeaponInit();
	UArenaGameInstance* ArenaGameInstance = Cast<UArenaGameInstance>(GetGameInstance());
	ArenaGameInstance->CharacterSaveSubsystem->LoadCharacterState(this);
}

// Called every frame
void ADefaultCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ADefaultCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}


void ADefaultCharacter::WeaponInit()
{
	// WeaponHandle값 지정
	WeaponDataHandles.Add(DataTableRow->WeaponBaseTableRowHandle);
	WeaponDataHandles.Add(DataTableRow->PunchTableRowHandle);
	WeaponDataHandles.Add(DataTableRow->KnifeTableRowHandle);
	WeaponDataHandles.Add(DataTableRow->RifleTableRowHandle);

	for (int i = 0; i < WeaponDataHandles.Num(); ++i)
	{
		WeaponInstances.Add(NewObject<UWeaponChildActorComponent>(this, UWeaponChildActorComponent::StaticClass()));
		WeaponInstances[i]->RegisterComponent();
		WeaponInstances[i]->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("WeaponSocket"));
		WeaponInstances[i]->SetData(WeaponDataHandles[i]);
		WeaponInstances[i]->GetChildActor()->SetActorHiddenInGame(true);
		WeaponInstances[i]->GetChildActor()->SetActorEnableCollision(false);
		WeaponInstances[i]->GetChildActor()->SetActorTickEnabled(false);
	}

	ActiveWeapon = Cast<AWeaponBase>(WeaponInstances[0]->GetChildActor());
	WeaponInstances[0]->GetChildActor()->SetActorHiddenInGame(false);
	WeaponInstances[0]->GetChildActor()->SetActorEnableCollision(true);
	WeaponInstances[0]->GetChildActor()->SetActorTickEnabled(true);

	ActiveWeapon->UpdateCharacter();
}



void ADefaultCharacter::SwitchWeapon(int InValue)
{
	--InValue;
	if (ActiveWeapon == Cast<AWeaponBase>(WeaponInstances[InValue]->GetChildActor()))
	{
		return;
	}
	else
	{
		ActiveWeapon = Cast<AWeaponBase>(WeaponInstances[InValue]->GetChildActor());
		for (int i = 0; i < WeaponInstances.Num(); ++i)
		{
			WeaponInstances[i]->GetChildActor()->SetActorHiddenInGame(true);
			WeaponInstances[i]->GetChildActor()->SetActorEnableCollision(false);
			WeaponInstances[i]->GetChildActor()->SetActorTickEnabled(false);
		}
		WeaponInstances[InValue]->GetChildActor()->SetActorHiddenInGame(false);
		WeaponInstances[InValue]->GetChildActor()->SetActorEnableCollision(true);
		WeaponInstances[InValue]->GetChildActor()->SetActorTickEnabled(true);
	}
	
	ActiveWeapon->SwapEquipment();
}

void ADefaultCharacter::VisibleEnemyHpBar(const AActor* DamagedEnemy)
{
	OnEnemyTakeDamage.Broadcast(DamagedEnemy);
}




void ADefaultCharacter::SetData(const FDataTableRowHandle& InRowHandle)
{
	int a = 10;
}

