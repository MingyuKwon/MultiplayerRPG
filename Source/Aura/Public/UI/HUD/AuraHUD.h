// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "AuraHUD.generated.h"

/**
 * 
 */
class UAuraUserWidget;
class UAuraOverlayWidgetController;
struct FAuraWidgetControllerParas;
class UAbilitySystemComponent;
class UAttributeSet;
class UAttributeMenuWidgetController;

UCLASS()
class AURA_API AAuraHUD : public AHUD
{
	GENERATED_BODY()
	
public:

	UAuraOverlayWidgetController* GetOverlayWidgetController(const FAuraWidgetControllerParas& WCParams);
	UAttributeMenuWidgetController* GetAttributeMenuWidgetController(const FAuraWidgetControllerParas& WCParams);

	void InitOverlay(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS);

private:
	UPROPERTY()
	TObjectPtr<UAuraUserWidget> OverlayWidget;


	UPROPERTY(EditAnywhere)
	TSubclassOf<UAuraUserWidget> AuraUserWidgetClass;

	UPROPERTY()
	TObjectPtr<UAuraOverlayWidgetController> AuraOverlayWidgetController;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UAuraOverlayWidgetController> AuraOverlayWidgetControllerClass;

	UPROPERTY()
	TObjectPtr<UAttributeMenuWidgetController> AttributeMenuWidgetController;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UAttributeMenuWidgetController> AttributeMenuWidgetControllerClass;
};
