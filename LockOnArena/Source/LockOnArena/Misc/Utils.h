#pragma once

#include "CoreMinimal.h"
#include "InputMappingContext.h"
#include "InputAction.h"
#include "InputActionValue.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "EnhancedActionKeyMapping.h"
#include "GameFramework/DamageType.h"

#include "Utils.generated.h"



UCLASS()
class UCustomDamageType : public UDamageType
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = DamageType)
	uint32 bRifleBase : 1;
};

UENUM()
enum class WeaponType : int8
{
	NonWeapon = 1,
	Punch,
	Knife,
	Rifle
};


class FUtils
{

public:
	static const UInputAction* FindActionFromName(const UInputMappingContext* IMC, const FName& InActionName)
	{
		if (!IMC)
		{
			checkf(nullptr, TEXT("IMC is not Valid"));
		}

		TArray<FEnhancedActionKeyMapping> Mappings = IMC->GetMappings();

		for (FEnhancedActionKeyMapping It : Mappings)
		{
			if (It.Action->GetName() == InActionName)
			{
				return It.Action;
			}				
		}
		return nullptr; 
	}
};
