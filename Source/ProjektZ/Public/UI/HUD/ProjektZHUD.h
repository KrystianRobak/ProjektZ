// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "ProjektZHUD.generated.h"

class UOverlayWidgetController;
class UProjektZUserWidget;
class UAbilitySystemComponent;
class UAttributeSet;
struct FWidgetControllerParams;
/**
 * 
 */
UCLASS()
class PROJEKTZ_API AProjektZHUD : public AHUD
{
	GENERATED_BODY()
public:
	UPROPERTY()
	TObjectPtr<UProjektZUserWidget> OverlayWidget;

	UOverlayWidgetController* GetOverlayWidgetController(const FWidgetControllerParams& WcParams);

	void InitOverlay(APlayerController* _PlayerController, APlayerState* _PlayerState, UAbilitySystemComponent* _AbilitySystemComponent, UAttributeSet* _AttributeSet);

private:
	UPROPERTY(EditAnywhere)
	TSubclassOf<UProjektZUserWidget> OverlayWidgetClass;

	UPROPERTY()
	TObjectPtr<UOverlayWidgetController> OverlayWidgetController;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UOverlayWidgetController> OverlayWidgetControllerClass;
};
