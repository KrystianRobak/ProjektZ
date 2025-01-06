// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/WidgetController/ProjektZWidgetController.h"
#include <AbilitySystem/Data/AttributeInfo.h>
#include "AttributeMenuWidgetController.generated.h"


struct FProjektZAttributeInfo;
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FAttributeInfoSignature, const FProjektZAttributeInfo&, Info);



/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class PROJEKTZ_API UAttributeMenuWidgetController : public UProjektZWidgetController
{
	GENERATED_BODY()
public:
	virtual void BindCallbackToDependencies() override;
	virtual void BroadcastInitialValues() override;

	UPROPERTY(BluePrintAssignable, Category="Gas|Attributes")
	FAttributeInfoSignature AttributeInfoDelegate;

protected:

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UAttributeInfo> AttributeInformation;

private:

	//void BroadcastAttributeInfo(const FGameplayTag& AttributeTag, const  FGameplayAttribute& GamAttribute);
};
