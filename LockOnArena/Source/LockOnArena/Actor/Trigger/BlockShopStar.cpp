// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/Trigger/BlockShopStar.h"
#include "Components/SceneComponent.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Misc/Utils.h"
#include "Character/DefaultCharacter.h"
#include "Character/CharacterStateComponent.h"

ABlockShopStar::ABlockShopStar()
{
	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	SetRootComponent(SceneComponent);

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	StaticMeshComponent->SetupAttachment(RootComponent); 

	CheckTrigger = CreateDefaultSubobject<UBoxComponent>(TEXT("CheckTrigger"));
	CheckTrigger->SetupAttachment(RootComponent);
	CheckTrigger->SetCollisionProfileName(CollisionProfileName::Portal);
	CheckTrigger->SetCollisionEnabled(ECollisionEnabled::QueryOnly);

	CheckTrigger->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnTrigger);
}

void ABlockShopStar::OnTrigger(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ADefaultCharacter* Character = CastChecked<ADefaultCharacter>(OtherActor);
	UCharacterStateComponent* CharacterState = Character->GetState();

	if (!CharacterState) { return; }

	if (CharacterState->CanUseShop())
	{
		StaticMeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		StaticMeshComponent->SetStaticMesh(nullptr);
	}
}
