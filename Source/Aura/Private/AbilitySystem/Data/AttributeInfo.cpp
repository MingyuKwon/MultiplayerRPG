// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Data/AttributeInfo.h"

FAuraAttributeInfo UAttributeInfo::FindAttributeInfoForTag(const FGameplayTag& AttributeTag, bool bLogNotFound)
{
	for (const FAuraAttributeInfo& info : AttributeInformation)
	{
		if (info.AttributeTag.MatchesTagExact(AttributeTag))
		{
			return info;
		}
	}

	if (bLogNotFound)
	{
		FString FormattedString = FString::Printf(TEXT("Cant find info for AttributeTag [%s] on AttributeInfo [%s]"), *AttributeTag.ToString(), *GetNameSafe(this));
		UE_LOG(LogTemp, Error, TEXT("%s"), *FormattedString);
	}

	return FAuraAttributeInfo();
}
