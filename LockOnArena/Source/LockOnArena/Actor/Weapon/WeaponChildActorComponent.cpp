// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/Weapon/WeaponChildActorComponent.h"
#include "Actor/Weapon/WeaponBase.h"


UWeaponChildActorComponent::UWeaponChildActorComponent()
{
	SetChildActorClass(AWeaponBase::StaticClass());
}

void UWeaponChildActorComponent::SetData(const FDataTableRowHandle& InRowHandle)
{
	FDataTableRowHandle RowHandle = InRowHandle;
	 
	FWeaponBaseTableRow* DataTableRow = RowHandle.GetRow<FWeaponBaseTableRow>(TEXT("DataTableRow"));

	ensureMsgf(DataTableRow, TEXT("Not Valid DataTableRow"));

	if (DataTableRow->WeaponClass != GetChildActorClass())
	{
		SetChildActorClass(DataTableRow->WeaponClass);
	}

	// @TODO : Weapon의 Owner 변경
	AWeaponBase* Weapon = CastChecked<AWeaponBase>(GetChildActor());
	APawn* Owner = CastChecked<APawn>(GetOwner());
	Weapon->SetOwner(Owner);
	Weapon->SetData(InRowHandle);
	//Weapon->SetInstigator(OwnerPawn);
	//Weapon->SetData(InDataTableRowHandle);
}
