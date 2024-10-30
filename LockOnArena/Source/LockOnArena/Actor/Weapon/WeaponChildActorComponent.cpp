// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/Weapon/WeaponChildActorComponent.h"
#include "Actor/Weapon/WeaponBase.h"
#include "Actor/Weapon/RifleBase.h"


UWeaponChildActorComponent::UWeaponChildActorComponent()
{
	SetChildActorClass(AWeaponBase::StaticClass());

	static ConstructorHelpers::FObjectFinder<UDataTable> DataTableAsset(TEXT("/Script/Engine.DataTable'/Game/Blueprint/Data/Weapon/DT_WeaponChildActor.DT_WeaponChildActor'"));
	UDataTable* DataTable = DataTableAsset.Object;
	DataTableRow = DataTable->FindRow<FWeaponChildBaseTableRow>(FName("Default"), TEXT("WeaponChildActor DataTableRow"));
}

void UWeaponChildActorComponent::BeginPlay()
{
	Super::BeginPlay();

	InitializeWeapons();
}

void UWeaponChildActorComponent::InitializeWeapons()
{

}

void UWeaponChildActorComponent::SwitchWeapon(const int WeaponIndex)
{
	if (!WeaponClasses[WeaponIndex]) { return; }

	if (WeaponClasses[WeaponIndex] != GetChildActorClass())
	{
		CurrentWeapon->SetActorHiddenInGame(true);
		SetChildActorClass(WeaponClasses[WeaponIndex]);

		CurrentWeapon = WeaponInstances[WeaponIndex];
		CurrentWeapon->SetActorHiddenInGame(false);

		CurrentWeapon->SwapEquipment();
	}
}

void UWeaponChildActorComponent::SetData(const FDataTableRowHandle& InRowHandle)
{
	FDataTableRowHandle RowHandle = InRowHandle;
	 
	FWeaponBaseTableRow* WeaponDataRow = RowHandle.GetRow<FWeaponBaseTableRow>(TEXT("DataTableRow"));

	ensureMsgf(DataTableRow, TEXT("Not Valid DataTableRow"));

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

