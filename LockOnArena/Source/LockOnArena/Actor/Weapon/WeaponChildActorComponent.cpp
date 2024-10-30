// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/Weapon/WeaponChildActorComponent.h"
#include "Actor/Weapon/WeaponBase.h"
#include "Actor/Weapon/RifleBase.h"


UWeaponChildActorComponent::UWeaponChildActorComponent()
{
	SetChildActorClass(AWeaponBase::StaticClass());
}

void UWeaponChildActorComponent::BeginPlay()
{
	Super::BeginPlay();
}



void UWeaponChildActorComponent::SetData(const FDataTableRowHandle& InRowHandle)
{
	FDataTableRowHandle RowHandle = InRowHandle;
	FWeaponBaseTableRow* WeaponDataRow = RowHandle.GetRow<FWeaponBaseTableRow>(TEXT("DataTableRow"));


	if (WeaponDataRow->WeaponClass != GetChildActorClass())
	{
		SetChildActorClass(WeaponDataRow->WeaponClass);
	}


	// @TODO : Weapon의 Owner 변경
	AWeaponBase* Weapon = CastChecked<AWeaponBase>(GetChildActor());
	APawn* Owner = CastChecked<APawn>(GetOwner());
	Weapon->SetOwner(Owner);
	Weapon->SetData(InRowHandle);
	//Weapon->SetInstigator(OwnerPawn);
	//Weapon->SetData(InDataTableRowHandle);
}

