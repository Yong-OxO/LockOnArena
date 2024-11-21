// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Animation/RifleAttack.h"
#include "Actor/Effect/Effect.h"
#include "Actor/Weapon/WeaponChildActorComponent.h"
#include "Actor/Weapon/WeaponBase.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Camera/CameraComponent.h"
#include "Actor/Weapon/RifleBase.h"
#include "Character/DefaultCharacter.h"
#include "Sound/SoundBase.h"
#include "Kismet/GameplayStatics.h"

URifleAttack::URifleAttack()
{
#if WITH_EDITORONLY_DATA
	NotifyColor = FColor(255, 0, 0, 255);
#endif // WITH_EDITORONLY_DATA
}

void URifleAttack::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	DataRow = RowHandle.GetRow<FEffectTableRow>(TEXT("DataRow"));

	ADefaultCharacter* Owner = Cast<ADefaultCharacter>(MeshComp->GetOwner());

#if WITH_EDITOR
	if (!Owner) { return; }
	if (GIsEditor && Owner && Owner->GetWorld() != GWorld) { return; } // 에디터 프리뷰
#endif

	ARifleBase* Weapon = Cast<ARifleBase>(Owner->ActiveWeapon);

	USkeletalMeshComponent* SkeletalMeshComponent = Weapon->GetComponentByClass<USkeletalMeshComponent>();
	UStaticMeshComponent* StaticMeshComponent = Weapon->GetComponentByClass<UStaticMeshComponent>();
	{ // Effect
		FVector SpawnLocation;
		FRotator SpawnRotation;

		if (SkeletalMeshComponent->GetSkeletalMeshAsset()) // 무기가 SkeletalMesh일때
		{
			SpawnLocation = SkeletalMeshComponent->GetSocketLocation(TEXT("Muzzle"));
			SpawnRotation = SkeletalMeshComponent->GetSocketRotation(TEXT("Muzzle"));
		}
		else if (StaticMeshComponent->GetStaticMesh()) // 무기가 StaticMesh일때
		{
			SpawnLocation = StaticMeshComponent->GetSocketLocation(TEXT("Muzzle"));
			SpawnRotation = StaticMeshComponent->GetSocketRotation(TEXT("Muzzle"));
		}
		else
		{
			ensure(false); // 둘 다 아닐때는 Montage가 재생이 안되어 Notify 호출 x
		}

		UGameplayStatics::PlaySoundAtLocation(Weapon->GetWorld(), Sound, Weapon->GetActorLocation(), 0.03f);
		Effect = MeshComp->GetWorld()->SpawnActor<AEffect>();
		Effect->Play(RowHandle, SpawnLocation, SpawnRotation);
	}

	// LineTrace
	{
		UCameraComponent* Camera = Owner->GetComponentByClass<UCameraComponent>();
		FVector StartLocation = Camera->GetComponentLocation();
		FRotator StartRotation = Camera->GetComponentRotation();
		Cast<ARifleBase>(Owner->ActiveWeapon)->Fire(StartLocation, StartRotation);
	}

}

