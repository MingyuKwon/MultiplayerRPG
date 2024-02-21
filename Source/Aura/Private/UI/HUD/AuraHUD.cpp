// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HUD/AuraHUD.h"
#include "UI/Widget/AuraUserWidget.h"
#include "UI/WidgetController/AttributeMenuWidgetController.h"
#include "UI/WidgetController/AuraOverlayWidgetController.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"


UAuraOverlayWidgetController* AAuraHUD::GetOverlayWidgetController(const FAuraWidgetControllerParas& WCParams)
{
	if (AuraOverlayWidgetController == nullptr)
	{
		AuraOverlayWidgetController = NewObject<UAuraOverlayWidgetController>(this, AuraOverlayWidgetControllerClass);
		AuraOverlayWidgetController->SetWIdgetControllerParams(WCParams);
		AuraOverlayWidgetController->BindCallbacksToDependencies();
	}

	return AuraOverlayWidgetController;
}

UAttributeMenuWidgetController* AAuraHUD::GetAttributeMenuWidgetController(const FAuraWidgetControllerParas& WCParams)
{
	if (AttributeMenuWidgetController == nullptr)
	{
		AttributeMenuWidgetController = NewObject<UAttributeMenuWidgetController>(this, AttributeMenuWidgetControllerClass);
		AttributeMenuWidgetController->SetWIdgetControllerParams(WCParams);
		AttributeMenuWidgetController->BindCallbacksToDependencies();
	}

	return AttributeMenuWidgetController;
}

void AAuraHUD::InitOverlay(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS)
{
	checkf(AuraUserWidgetClass, TEXT("AuraUserWidgetClass is not Initialized"));
	checkf(AuraOverlayWidgetControllerClass, TEXT("AuraOverlayWidgetControllerClass is not Initialized"));


	UAuraUserWidget* Widget = CreateWidget<UAuraUserWidget>(GetWorld(), AuraUserWidgetClass);

	const FAuraWidgetControllerParas WCParams(PC, PS, ASC, AS);
	UAuraOverlayWidgetController* WidgetController = GetOverlayWidgetController(WCParams);

	Widget->SetWidgetController(WidgetController);
	WidgetController->BroadcastInitialValues();

	Widget->AddToViewport();

}
