// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/WidgetController/ProjektZWidgetController.h"
#include "AbilitySystem/ProjektZAbilitySystemComponent.h"
#include "AbilitySystem/Data/AbilityInfo.h"
#include "USpellMenuWidgetController.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FAbilityInfoDelegate, const FProjektZAbilityInfo&, Info);
/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class PROJEKTZ_API USpellMenuWidgetController : public UProjektZWidgetController
{
	GENERATED_BODY()

public:
	virtual void BroadcastInitialValues() override;
	virtual void BindCallbackToDependencies() override;

	void OnAbilityChanged(UProjektZAbilitySystemComponent* ASC);

public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Widget Data")
	TObjectPtr<UAbilityInfo> AbilityInfo;

	UPROPERTY(BlueprintAssignable, Category = "GAS|Messages")
	FAbilityInfoDelegate AbilityInfoDelegate;
};
