#pragma once

#include "CoreMinimal.h"
#include "InputMappingContext.h"
#include "InputAction.h"
#include "InputActionValue.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "EnhancedActionKeyMapping.h"

namespace FPathName
{
	
}

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
