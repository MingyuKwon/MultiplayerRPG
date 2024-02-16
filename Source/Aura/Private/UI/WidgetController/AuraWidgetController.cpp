// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/WidgetController/AuraWidgetController.h"

void UAuraWidgetController::SetWIdgetControllerParams(const FAuraWidgetControllerParas& AuraWidgetControllerParas)
{
	PlayerController = AuraWidgetControllerParas.PlayerController;
	PlayerState = AuraWidgetControllerParas.PlayerState;
	AbilitySystemComponent = AuraWidgetControllerParas.AbilitySystemComponent;
	AttributeSet = AuraWidgetControllerParas.AttributeSet;

}
