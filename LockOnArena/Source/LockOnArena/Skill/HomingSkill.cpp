// Fill out your copyright notice in the Description page of Project Settings.


#include "Skill/HomingSkill.h"
#include "Skill/HomingProjectile.h"
#include "Actor/Weapon/RifleBase.h"
#include "Character/CharacterStateComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Character/DefaultCharacter.h"

void UHomingSkill::SetData(const FDataTableRowHandle& InHandle)
{
	Super::SetData(InHandle);

	DataTableRow = InHandle.GetRow<FHomingTableRow>(TEXT("DataRow"));
	SkillATKPersent = DataTableRow->SkillATKPersent;
}

void UHomingSkill::PlaySkill()
{
	Super::PlaySkill();

	bool Success = PlayHoming(CharacterState->GetTargetLocation());
	if (RemainCoolDown > 0 || Success)
	{
		RemainCoolDown = MaxCooldown;
		UE_LOG(LogTemp, Display, TEXT("Cooldown"));
		bCanPlay = false;
		return;
	}
}

bool UHomingSkill::PlayHoming(const FVector TargetLocation)
{
	if (CharacterState->GetLockOn())
	{
		Weapon = Cast<ARifleBase>(GetOwner());

		UStaticMeshComponent* StaticMeshComponent = Weapon->GetComponentByClass<UStaticMeshComponent>();
		FVector SpawnLocation;
		FRotator SpawnRotation;

		FVector FowardVector = ControlledCharacter->GetActorForwardVector();
		FVector RightVector = ControlledCharacter->GetActorRightVector();
		FVector UpVector = FVector::CrossProduct(FowardVector, RightVector);

		if (StaticMeshComponent->GetStaticMesh()) // 무기가 SkeletalMesh일때
		{
			SpawnLocation = StaticMeshComponent->GetSocketLocation(TEXT("Muzzle"));
			SpawnLocation =  (FowardVector * 50) + SpawnLocation;
			SpawnRotation = (TargetLocation - SpawnLocation).Rotation();
		}

	

		TArray<AHomingProjectile*> Projectile;
		for (int i = 0; i < 5; ++i)
		{
			Projectile.Add(GetWorld()->SpawnActor<AHomingProjectile>(DataTableRow->ProjectileClass, SpawnLocation, SpawnRotation));
		}
		Projectile[0]->SpawnProjectile(SpawnLocation, SpawnRotation, TargetLocation);
		Projectile[1]->SpawnProjectile(SpawnLocation + RightVector * 50, SpawnRotation, TargetLocation);
		Projectile[2]->SpawnProjectile(SpawnLocation + (- 1 * RightVector * 50), SpawnRotation, TargetLocation);
		Projectile[3]->SpawnProjectile(SpawnLocation + UpVector * 50, SpawnRotation, TargetLocation);
		Projectile[4]->SpawnProjectile(SpawnLocation + (-1 * UpVector * 50), SpawnRotation, TargetLocation);

		return true;
	}

	return false;
}
