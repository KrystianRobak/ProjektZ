// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widget/ProjektZUserWidget.h"

void UProjektZUserWidget::SetWidgetController(UObject* InWidgetController)
{
	WidgetController = InWidgetController;
	WidgetControllerSet();
}