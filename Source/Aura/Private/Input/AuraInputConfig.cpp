// Fill out your copyright notice in the Description page of Project Settings.


#include "Input/AuraInputConfig.h"

const UInputAction* UAuraInputConfig::FindAbilityInputActionForTag(const FGameplayTag& inputTag, bool bLogNotFound) const
{
	for (auto& action : AbilityInputActions)
	{
		if (action.InputAction && action.InputTag == inputTag)
		{
			return action.InputAction;
		}
	}

	if (bLogNotFound)
	{
		UE_LOG(LogTemp, Display, TEXT("cant find abilityInputAction for InputTag [%s]") , *inputTag.ToString());
	}

	return nullptr;
}
