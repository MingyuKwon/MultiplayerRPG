// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnhancedInputComponent.h"
#include "AuraInputConfig.h"
#include "AuraInputComponent.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API UAuraInputComponent : public UEnhancedInputComponent
{
	GENERATED_BODY()

public:
	template<class UserClass, typename PressedFuncType, typename ReleasedFuncType, typename HeldFuncType>
	void BindAbilityActions(const UAuraInputConfig* InputConfig, UserClass* Object, PressedFuncType PressFunc, ReleasedFuncType ReleasedFunc, HeldFuncType HeldFunc);
	
};

template<class UserClass, typename PressedFuncType, typename ReleasedFuncType, typename HeldFuncType>
inline void UAuraInputComponent::BindAbilityActions(const UAuraInputConfig* InputConfig, UserClass* Object, PressedFuncType PressFunc, ReleasedFuncType ReleasedFunc, HeldFuncType HeldFunc)
{
	check(InputConfig);

	for (auto& action : InputConfig->AbilityInputActions)
	{
		if (action.InputAction && action.InputTag.IsValid())
		{
			if (PressFunc)
			{
				BindAction(action.InputAction, ETriggerEvent::Started, Object, PressFunc, action.InputTag);
			}

			if (ReleasedFunc)
			{
				BindAction(action.InputAction, ETriggerEvent::Completed, Object, ReleasedFunc, action.InputTag);
			}

			if (HeldFunc)
			{
				BindAction(action.InputAction, ETriggerEvent::Triggered, Object, HeldFunc, action.InputTag);
			}
		}
	}
}
