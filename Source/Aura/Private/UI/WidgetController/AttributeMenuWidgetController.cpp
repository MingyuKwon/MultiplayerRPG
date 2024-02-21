// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/WidgetController/AttributeMenuWidgetController.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "AbilitySystem/Data/AttributeInfo.h"
#include "AuraGameplayTags.h"


void UAttributeMenuWidgetController::BroadcastInitialValues()
{
	UAuraAttributeSet* AS = CastChecked<UAuraAttributeSet>(AttributeSet);

	check(AttributeInfo);

	for (auto& Pair : AS->TagsToAttributes)
	{
		FAuraAttributeInfo info = AttributeInfo->FindAttributeInfoForTag(Pair.Key);
		FGameplayAttribute attr = Pair.Value();
		info.AttributeValue = attr.GetNumericValue(AS);

		AttributeInfoDelegate.Broadcast(info);
	}
	
}

void UAttributeMenuWidgetController::BindCallbacksToDependencies()
{
	

}

