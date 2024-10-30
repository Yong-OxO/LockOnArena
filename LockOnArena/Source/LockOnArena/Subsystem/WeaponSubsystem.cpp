// Fill out your copyright notice in the Description page of Project Settings.


#include "Subsystem/WeaponSubsystem.h"

UWeaponSubsystem::UWeaponSubsystem()
{
	{
		static ConstructorHelpers::FObjectFinder<UDataTable> Asset(TEXT("/Script/Engine.DataTable'/Game/Blueprint/Data/Weapon/DT_WeaponBase.DT_WeaponBase'"));
		//check(Asset.Object);
		WeaponBaseDataTable = Asset.Object;
	}
	{
	/*	static ConstructorHelpers::FObjectFinder<UDataTable> Asset(TEXT("/Script/Engine.DataTable'/Game/Blueprint/Weapon/DT_Gun.DT_Gun'"));
		check(Asset.Object);
		GunDataTable = Asset.Object;*/
	}
}

FDataTableRowHandle UWeaponSubsystem::FindWeapon(const FName& InKey)
{
	FDataTableRowHandle DataTableRowHandle;

#if WITH_EDITOR
	bool bFind = false;
	if (WeaponBaseDataTable->GetRowMap().Find(InKey))
	{
		check(!bFind);
		bFind = true;
		DataTableRowHandle.DataTable = WeaponBaseDataTable;
		DataTableRowHandle.RowName = InKey;
	}
	//if (WeaponBaseDataTable->GetRowMap().Find(InKey))
	//{
	//	check(!bFind);
	//	bFind = true;
	//	DataTableRowHandle.DataTable = WeaponBaseDataTable;
	//	DataTableRowHandle.RowName = InKey;
	//}
#else
	if (WeaponDataTable->GetRowMap().Find(InKey))
	{
		DataTableRowHandle.DataTable = WeaponBaseDataTable;
		DataTableRowHandle.RowName = InKey;
	}
	else if (GunDataTable->GetRowMap().Find(InKey))
	{
		DataTableRowHandle.DataTable = GunDataTable;
		DataTableRowHandle.RowName = InKey;
	}
#endif

	return DataTableRowHandle;
}
