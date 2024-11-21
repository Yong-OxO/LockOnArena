// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/DefaultCharacter.h"
#include "Character/CharacterStateComponent.h"
#include "Character/Animation/AnimInstance/InGameAnimInstance.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Actor/Weapon/WeaponChildActorComponent.h"
#include "Subsystem/WeaponSubsystem.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Character/InGamePlayerController.h"
#include "Widget/DefaultHUD.h"
#include "GameMode/ArenaGameInstance.h"
#include "Subsystem/CharacterSaveSubsystem.h"
#include "Skill/SkillDamageType.h"
#include "Engine/DamageEvents.h"
#include "Character/Animation/AnimInstance/InGameAnimInstance.h"


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
	PlayerController = Cast<AInGamePlayerController>(GetController());
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

float ADefaultCharacter::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	if (CharacterState->IsDie()) { return 0.f; }

	UInGameAnimInstance* AnimInstance = Cast<UInGameAnimInstance>(GetMesh()->GetAnimInstance());
	//AnimInstance->OnMontageEnded.AddDynamic(this, &ThisClass::OnMontageEnd);


	ADefaultCharacter* CauserPlayer = Cast<ADefaultCharacter>(DamageCauser->GetOwner());

	if (CauserPlayer == nullptr) // 발사체 등 Weapon이 직접적인 피해를 주지 않을 때
	{
		CauserPlayer = Cast<ADefaultCharacter>(DamageCauser->GetOwner()->GetOwner());
	}

	CharacterState->ReduceHp(Damage);

	if (CharacterState->IsDie()) // 최초 사망판정시
	{
		SetActorEnableCollision(false);
		if (PlayerController) { PlayerController->DisableInput(PlayerController); }


		AnimInstance->StopAllMontages(0.f);
		AnimInstance->Montage_Play(DataTableRow->DeathMontage);

		// 다른 Montage 재생중 Die가 발생하면 기존 Montage가 종료되면서 OnMontageEnd가 실행되므로 따로 관리가 필요하다.
		GetWorld()->GetTimerManager().SetTimer(
			TimerHandle,
			this,
			&ThisClass::OnDIe,
			DataTableRow->DeathMontage->GetPlayLength() - 0.2f,
			false);

		return Damage;
	}

	Controller->StopMovement();

	if (!CharacterState->IsSuperAmmo())
	{
		// Skill로 피해를 입을 때
		if (DamageEvent.DamageTypeClass == USkillDamageType::StaticClass()) 
		{
			AnimInstance->StopAllMontages(0.f);

			float SkillHitMontageTime = DataTableRow->SkillHitMontage->GetPlayLength()/2.1 + DataTableRow->KneelToStand->GetPlayLength();

			CharacterState->SetSuperAmmo(SkillHitMontageTime * 1.1);
			CharacterState->SetCannotMove(SkillHitMontageTime * 1.1);

			AnimInstance->Montage_Play(DataTableRow->SkillHitMontage);

			GetWorld()->GetTimerManager().SetTimer(
				SKillHitTimerHandle,
				this,
				&ThisClass::OnSkillHit,
				DataTableRow->SkillHitMontage->GetPlayLength() - 0.1f,
				false);
			
		}
		else // 일반 공격일 때
		{
			float SkillHitMontageTime = DataTableRow->HitMontage->GetPlayLength();
			CharacterState->SetCannotMove(SkillHitMontageTime * 0.7);
			AnimInstance->StopAllMontages(0.f);
			AnimInstance->Montage_Play(DataTableRow->HitMontage);
		}
	}

	return Damage;
}

void ADefaultCharacter::OnSkillHit()
{
	UInGameAnimInstance* AnimInstance = Cast<UInGameAnimInstance>(GetMesh()->GetAnimInstance());
	AnimInstance->Montage_Play(DataTableRow->KneelToStand);
	CharacterState->SetSuperAmmo(1.f);
}

void ADefaultCharacter::OnDIe()
{
	Destroy();
}

