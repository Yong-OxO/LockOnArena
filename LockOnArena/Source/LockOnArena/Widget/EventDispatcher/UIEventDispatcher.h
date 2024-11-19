// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "UIEventDispatcher.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FUIEventDelegate, const FName, EventName);


UCLASS()
class LOCKONARENA_API UUIEventDispatcher : public UObject
{
	GENERATED_BODY()
	

public:
	FUIEventDelegate UIEventDelegate;

	void BroadCastUIEvent(const FName EventName) { UIEventDelegate.Broadcast(EventName); }
};
