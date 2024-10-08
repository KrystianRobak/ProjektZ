// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "ProjektZHUD.generated.h"

class UAttributeMenuWidgetController;
class UOverlayWidgetController;
class USpellMenuWidgetController;
class UPartyStatsWidgetController;
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

	UOverlayWidgetController* GetOverlayWidgetController(const FWidgetControllerParams& WcParams);

	UAttributeMenuWidgetController* GetAttributeMenuWidgetController(const FWidgetControllerParams& WcParams);

	USpellMenuWidgetController* GetSpellMenuWidgetController(const FWidgetControllerParams& WcParams);

	UPartyStatsWidgetController* GetPartyMembersWidgetController(const FWidgetControllerParams& WcParams);

	UOverlayWidgetController* InitOverlay(APlayerController* _PlayerController, APlayerState* _PlayerState, UAbilitySystemComponent* _AbilitySystemComponent, UAttributeSet* _AttributeSet);

private:

	UPROPERTY()
	TObjectPtr<UProjektZUserWidget> OverlayWidget;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UProjektZUserWidget> OverlayWidgetClass;

	UPROPERTY()
	TObjectPtr<UOverlayWidgetController> OverlayWidgetController;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UOverlayWidgetController> OverlayWidgetControllerClass;

	UPROPERTY()
	TObjectPtr<UAttributeMenuWidgetController> AttributeMenuWidgetController;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UAttributeMenuWidgetController> AttributeMenuWidgetControllerClass;

	UPROPERTY()
	TObjectPtr<USpellMenuWidgetController> SpellMenuWidgetController;

	UPROPERTY(EditAnywhere)
	TSubclassOf<USpellMenuWidgetController> SpellMenuWidgetControllerClass;

	UPROPERTY()
	TObjectPtr<UProjektZUserWidget> PartyMembersWidget;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UProjektZUserWidget> PartyMembersWidgetClass;

	UPROPERTY()
	TObjectPtr<UPartyStatsWidgetController> PartyMembersWidgetController;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UPartyStatsWidgetController> PartyMembersWidgetControllerClass;
};
