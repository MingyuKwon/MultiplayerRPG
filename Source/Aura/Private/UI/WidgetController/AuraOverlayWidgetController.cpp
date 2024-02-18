// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/WidgetController/AuraOverlayWidgetController.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "AbilitySystem/AuraAbilitySystemComponentBase.h"

void UAuraOverlayWidgetController::BroadcastInitialValues()
{
	const UAuraAttributeSet* AuraAttributeSet = CastChecked<UAuraAttributeSet>(AttributeSet);

	OnHealthChanged.Broadcast(AuraAttributeSet->GetHealth());
	OnMaxHealthChanged.Broadcast(AuraAttributeSet->GetMaxHealth());
	OnManaChanged.Broadcast(AuraAttributeSet->GetMana());
	OnMaxManaChanged.Broadcast(AuraAttributeSet->GetMaxMana());
}

void UAuraOverlayWidgetController::BindCallbacksToDependencies()
{
	const UAuraAttributeSet* AuraAttributeSet = CastChecked<UAuraAttributeSet>(AttributeSet);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAttributeSet->GetHealthAttribute())
		.AddLambda(
			[this](const FOnAttributeChangeData& Data) {
				OnHealthChanged.Broadcast(Data.NewValue);
			}
		);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAttributeSet->GetMaxHealthAttribute())
		.AddLambda(
			[this](const FOnAttributeChangeData& Data) {
				OnMaxHealthChanged.Broadcast(Data.NewValue);
			}
		);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAttributeSet->GetManaAttribute())
		.AddLambda(
			[this](const FOnAttributeChangeData& Data) {
				OnManaChanged.Broadcast(Data.NewValue);
			}
	);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAttributeSet->GetMaxManaAttribute())
		.AddLambda(
			[this](const FOnAttributeChangeData& Data) {
				OnMaxManaChanged.Broadcast(Data.NewValue);
			}
	);

	UAuraAbilitySystemComponentBase* AuraAbilitySystemComponent = Cast<UAuraAbilitySystemComponentBase>(AbilitySystemComponent);
	AuraAbilitySystemComponent->EffectAssetTagsDelegates.AddUObject(this, &UAuraOverlayWidgetController::AssetTagBroadCasted);

}

void UAuraOverlayWidgetController::AssetTagBroadCasted(const FGameplayTagContainer& GameplayTagContainer)
{
	for (auto tag : GameplayTagContainer)
	{
		FGameplayTag MessageTag = FGameplayTag::RequestGameplayTag(FName(TEXT("Message")));
		bool isMessageTag = tag.MatchesTag(MessageTag);

		if (isMessageTag)
		{
			FUIWidgetRow* Row = GetDataTableRowByTag<FUIWidgetRow>(MessageWidgetDataTable, tag);
			if (Row != nullptr)
			{
				MessageWidgetRowDelegate.Broadcast(*Row);
			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("row find failed // TagName :: %s"), tag.GetTagName());
			}
			
		}

		
	}
}


