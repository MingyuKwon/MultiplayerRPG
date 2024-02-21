// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/WidgetController/AttributeMenuWidgetController.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "AbilitySystem/Data/AttributeInfo.h"
#include "AuraGameplayTags.h"
#include "AbilitySystem/Data/AttributeInfo.h"


void UAttributeMenuWidgetController::BroadcastInitialValues()
{
	UAuraAttributeSet* AS = CastChecked<UAuraAttributeSet>(AttributeSet);

	check(AttributeInfo);

	FAuraAttributeInfo info = AttributeInfo->FindAttributeInfoForTag(FAuraGamplayTags::Get().Attribute_Primary_Strength);
	info.AttributeValue = AS->GetStrength();

	AttributeInfoDelegate.Broadcast(info);
}

void UAttributeMenuWidgetController::BindCallbacksToDependencies()
{
	

}

