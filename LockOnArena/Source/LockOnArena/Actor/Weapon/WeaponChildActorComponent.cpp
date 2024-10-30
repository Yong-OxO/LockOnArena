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

	CurrentWeapon = WeaponInstances[0];
}

void UWeaponChildActorComponent::InitializeWeapons()
{
	// WeaponHandle값 지정
	WeaponDataHandles.Add(DataTableRow->NoneWeapon);
	WeaponDataHandles.Add(DataTableRow->PunchWeapon);
	WeaponDataHandles.Add(DataTableRow->KnifeWeapon);
	WeaponDataHandles.Add(DataTableRow->RifleWeapon);

	//WeaponClasses 지정
	WeaponClasses.Add(AWeaponBase::StaticClass()); // 1
	WeaponClasses.Add(AWeaponBase::StaticClass()); // 2
	WeaponClasses.Add(AWeaponBase::StaticClass()); // 3
	WeaponClasses.Add(ARifleBase::StaticClass());  // 4

	for (TSubclassOf<AWeaponBase> WeaponClass : WeaponClasses)
	{
		if (WeaponClass)
		{
			AWeaponBase* NewWeapon = GetWorld()->SpawnActor<AWeaponBase>(WeaponClass);
			if (NewWeapon)
			{
				NewWeapon->SetActorHiddenInGame(true);
				NewWeapon->SetOwner(GetOwner());
				WeaponInstances.Add(NewWeapon);
			}
		}
	}
	for (int i = 0; i < WeaponDataHandles.Num(); ++i)
	{
		WeaponInstances[i]->SetData(WeaponDataHandles[i]);
	}
}

void UWeaponChildActorComponent::SwitchWeapon(const int WeaponIndex)
{
	CurrentWeapon->SetActorHiddenInGame(true);

	if (WeaponInstances[WeaponIndex])
	{
		CurrentWeapon = WeaponInstances[WeaponIndex];
		CurrentWeapon->SetActorHiddenInGame(false);
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

