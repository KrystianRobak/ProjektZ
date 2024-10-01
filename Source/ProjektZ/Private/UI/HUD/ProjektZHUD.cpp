// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HUD/ProjektZHUD.h"

#include "UI/Widget/ProjektZUserWidget.h"
#include "UI/WidgetController/OverlayWidgetController.h"
#include "UI/WidgetController/AttributeMenuWidgetController.h"
#include "UI/WidgetController/USpellMenuWidgetController.h"

UOverlayWidgetController* AProjektZHUD::GetOverlayWidgetController(const FWidgetControllerParams& WcParams)
{
	if (OverlayWidgetController == nullptr)
	{
		OverlayWidgetController = NewObject<UOverlayWidgetController>(this, OverlayWidgetControllerClass);
		OverlayWidgetController->SetWidgetControllerParams(WcParams);
		OverlayWidgetController->BindCallbackToDependencies();
	}
	return OverlayWidgetController;
}

UAttributeMenuWidgetController* AProjektZHUD::GetAttributeMenuWidgetController(const FWidgetControllerParams& WcParams)
{
	if (AttributeMenuWidgetController == nullptr)
	{
		AttributeMenuWidgetController = NewObject<UAttributeMenuWidgetController>(this, AttributeMenuWidgetControllerClass);
		AttributeMenuWidgetController->SetWidgetControllerParams(WcParams);
		AttributeMenuWidgetController->BindCallbackToDependencies();
	}
	return AttributeMenuWidgetController;
}

USpellMenuWidgetController* AProjektZHUD::GetSpellMenuWidgetController(const FWidgetControllerParams& WcParams)
{
	if (SpellMenuWidgetController == nullptr)
	{
		SpellMenuWidgetController = NewObject<USpellMenuWidgetController>(this, SpellMenuWidgetControllerClass);
		SpellMenuWidgetController->SetWidgetControllerParams(WcParams);
		SpellMenuWidgetController->BindCallbackToDependencies();
	}
	return SpellMenuWidgetController;
}

void AProjektZHUD::InitOverlay(APlayerController* _PlayerController, APlayerState* _PlayerState, UAbilitySystemComponent* _AbilitySystemComponent, UAttributeSet* _AttributeSet)
{
	checkf(OverlayWidgetClass, TEXT("Overlay Widget CLass uninitialized, please fill out BP_ProjektZHUD"));
	checkf(OverlayWidgetControllerClass, TEXT("Overlay Widget Controller CLass uninitialized, please fill out BP_ProjektZHUD"));
	
	UUserWidget* Widget = CreateWidget<UUserWidget>(GetWorld(), OverlayWidgetClass);
	OverlayWidget = Cast<UProjektZUserWidget>(Widget);

	const FWidgetControllerParams WidgetControllerParams(_PlayerController, _PlayerState, _AbilitySystemComponent, _AttributeSet);
	UOverlayWidgetController* WidgetController = GetOverlayWidgetController(WidgetControllerParams);

	OverlayWidget->SetWidgetController(WidgetController);

	WidgetController->BroadcastInitialValues();

	Widget->AddToViewport();
}

