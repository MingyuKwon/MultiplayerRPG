// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widget/AuraUserWidget.h"

void UAuraUserWidget::SetWidgetController(UObject* InWidgetController)
{
	WidgetController = InWidgetController;
	// 여기서 blueprintimplement WidgetControllerSet을 부르는 것은, 정확히 말하면 widgetcontroller가 set 된 상황에서의
	// 후속 조치를 함수이자 이벤트로 만들어서 블루프린트 쪽에서 처리하라고 넘긴 것하고 다름이 없다
	WidgetControllerSet();
}
