// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "RifleAttack.generated.h"

// @TODO : SocketName을 DataTable에서 받아와서 처리

struct FEffectTableRow;
class AEffect;
UCLASS()
class LOCKONARENA_API URifleAttack : public UAnimNotify
{
	GENERATED_BODY()
	
public:
	URifleAttack();

	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;
public:
	UPROPERTY(EditAnywhere, Category = "Effect", meta = (RowType = "/Script/LOCKONARENA.EffectTableRow"))
	FDataTableRowHandle RowHandle;

	FEffectTableRow* DataRow;

	AEffect* Effect = nullptr;
};
