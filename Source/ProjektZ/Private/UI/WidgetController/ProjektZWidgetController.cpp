// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/WidgetController/ProjektZWidgetController.h"

void UProjektZWidgetController::SetWidgetControllerParams(const FWidgetControllerParams& WCParams)
{
	PlayerController = WCParams.PlayerController;
	PlayerState = WCParams.PlayerState;
	AbilitySystemComponent = WCParams.AbilitySystemComponent;
	AttributeSet = WCParams.AttributeSet;
}

void UProjektZWidgetController::BroadcastInitialValues()
{
}

void UProjektZWidgetController::BindCallbackToDependencies()
{
}
