// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Animation/RifleAttack.h"
#include "Actor/Effect/Effect.h"
#include "Actor/Weapon/WeaponChildActorComponent.h"
#include "Actor/Weapon/WeaponBase.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Camera/CameraComponent.h"
#include "Actor/Weapon/RifleBase.h"

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

	AActor* Owner = Cast<AActor>(MeshComp->GetOwner());

#if WITH_EDITOR
	if (GIsEditor && Owner && Owner->GetWorld() != GWorld) { return; } // 에디터 프리뷰
#endif

	UWeaponChildActorComponent* Weapon = Owner->GetComponentByClass<UWeaponChildActorComponent>();
	ARifleBase* Child = Cast<ARifleBase>(Weapon->GetChildActor());

	USkeletalMeshComponent* SkeletalMeshComponent = Child->GetComponentByClass<USkeletalMeshComponent>();
	UStaticMeshComponent* StaticMeshComponent = Child->GetComponentByClass<UStaticMeshComponent>();
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

		Effect = MeshComp->GetWorld()->SpawnActor<AEffect>();
		Effect->Play(RowHandle, SpawnLocation, SpawnRotation);
	}

	//// LineTrace
	//{
	//	UCameraComponent* Camera = Owner->GetComponentByClass<UCameraComponent>();
	//	FVector StartLocation = Camera->GetComponentLocation();
	//	FRotator StartRotation = Camera->GetComponentRotation();
	//	Child->Fire(StartLocation, StartRotation);
	//}

}

