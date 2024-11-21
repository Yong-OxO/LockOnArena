// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "AN_SilverDevil_Skl02_01.generated.h"

/**
 * 
 */
UCLASS()
class LOCKONARENA_API UAN_SilverDevil_Skl02_01 : public UAnimNotify
{
	GENERATED_BODY()
	
public:
	UAN_SilverDevil_Skl02_01();

	UPROPERTY(EditAnywhere, Category = "SKill", meta = (RowType = "/Script/LOCKONARENA.EnemySkillBaseTableRow"))
	FDataTableRowHandle RowHandle;

	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;
};
