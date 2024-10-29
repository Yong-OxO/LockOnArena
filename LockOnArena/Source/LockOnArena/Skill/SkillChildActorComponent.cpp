// Fill out your copyright notice in the Description page of Project Settings.


#include "Skill/SkillChildActorComponent.h"
#include "Skill/SkillSystem.h"

USkillChildActorComponent::USkillChildActorComponent()
{
	SetChildActorClass(ASkillSystem::StaticClass());
}

void USkillChildActorComponent::SetData(const FDataTableRowHandle& InRowHandle)
{
	FDataTableRowHandle RowHandle = InRowHandle;

	FSkillSystemTableRow* DataTableRow = RowHandle.GetRow<FSkillSystemTableRow>(TEXT("DataTableRow"));

	ensureMsgf(DataTableRow, TEXT("No Valid RowHandle"));

	if (DataTableRow->SkillSystemClass != GetChildActorClass())
	{
		SetChildActorClass(DataTableRow->SkillSystemClass);
	}

	ASkillSystem* SkillSysyem = CastChecked<ASkillSystem>(GetChildActor());
	APawn* Owner = CastChecked<APawn>(GetOwner());
	SkillSysyem->SetOwner(Owner);

	SkillSysyem->SetData(InRowHandle);
}


