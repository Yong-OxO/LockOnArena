// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/Trigger/GravityTrigger.h"
#include "Misc/Utils.h"
#include "Components/SceneComponent.h"
#include "Components/BoxComponent.h"
#include "Character/DefaultCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
AGravityTrigger::AGravityTrigger()
{
	PrimaryActorTick.bCanEverTick = true;

	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	SetRootComponent(SceneComponent);


	CheckTrigger = CreateDefaultSubobject<UBoxComponent>(TEXT("CheckTrigger"));
	CheckTrigger->SetupAttachment(RootComponent);
	CheckTrigger->SetCollisionProfileName(CollisionProfileName::Portal);
	CheckTrigger->SetCollisionEnabled(ECollisionEnabled::QueryOnly);

	CheckTrigger->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnTrigger);
	CheckTrigger->OnComponentEndOverlap.AddDynamic(this, &ThisClass::EndTrigger);
}

void AGravityTrigger::OnTrigger(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ADefaultCharacter* PlayerCharacter = Cast<ADefaultCharacter>(OtherActor);
	if (PlayerCharacter)
	{
		UCharacterMovementComponent* MovementComponent = PlayerCharacter->GetCharacterMovement();
		MovementComponent->GravityScale = CustomGravityScale;
	}

	UE_LOG(LogTemp, Display, TEXT("TriggerEnd"));
}

void AGravityTrigger::EndTrigger(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{

}

// Called when the game starts or when spawned
void AGravityTrigger::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGravityTrigger::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

