// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widget/AuraUserWidget.h"

void UAuraUserWidget::SetWidgetController(UObject* InWidgetController)
{
	WidgetController = InWidgetController;
	// ���⼭ blueprintimplement WidgetControllerSet�� �θ��� ����, ��Ȯ�� ���ϸ� widgetcontroller�� set �� ��Ȳ������
	// �ļ� ��ġ�� �Լ����� �̺�Ʈ�� ���� �������Ʈ �ʿ��� ó���϶�� �ѱ� ���ϰ� �ٸ��� ����
	WidgetControllerSet();
}
