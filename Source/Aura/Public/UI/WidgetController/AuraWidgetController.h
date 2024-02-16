// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "AuraWidgetController.generated.h"

/**
 * 
 */
class UAbilitySystemComponent;
class UAttributeSet;


USTRUCT(BlueprintType)
struct FAuraWidgetControllerParas
{
	GENERATED_BODY()

	FAuraWidgetControllerParas() {}
	FAuraWidgetControllerParas(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS)
		: PlayerController(PC) , PlayerState(PS), AbilitySystemComponent(ASC), AttributeSet(AS) {}


	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TObjectPtr<APlayerController> PlayerController;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TObjectPtr<APlayerState> PlayerState;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TObjectPtr<UAttributeSet> AttributeSet;
};


UCLASS(Blueprintable, BlueprintType)
class AURA_API UAuraWidgetController : public UObject
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable)
	void SetWIdgetControllerParams(const FAuraWidgetControllerParas& AuraWidgetControllerParas);
	virtual void BroadcastInitialValues();

protected:

	UPROPERTY(BlueprintReadOnly, Category = "WidgetController")
	TObjectPtr<APlayerController> PlayerController;

	UPROPERTY(BlueprintReadOnly, Category = "WidgetController")
	TObjectPtr<APlayerState> PlayerState;

	UPROPERTY(BlueprintReadOnly, Category = "WidgetController")
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY(BlueprintReadOnly, Category = "WidgetController")
	TObjectPtr<UAttributeSet> AttributeSet;

};
