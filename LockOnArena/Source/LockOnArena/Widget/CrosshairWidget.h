// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CrosshairWidget.generated.h"

class UImage;

UCLASS()
class LOCKONARENA_API UCrosshairWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeOnInitialized();
	virtual void NativePreConstruct();
	virtual void NativeConstruct();
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime);
	
public:
	void VisibleNormalCrosshair();
	void VisibleLockOnCrosshair();



protected:
	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	UImage* NormalCrosshair = nullptr;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	UImage* LockOnCrosshair = nullptr;
};
