// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/Weapon/RifleBase.h"

void ARifleBase::Attack()
{
	Super::Attack();

	UE_LOG(LogTemp, Warning, TEXT("Rifle Attack"));
}
