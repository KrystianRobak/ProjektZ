// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/WidgetController/ProjektZWidgetController.h"
#include "Inventory/DA_BaseItem.h"
#include "InventoryWidgetController.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FItemChangedDelegate, const UTexture2D*, AbilityIcon, EItemPlacement, ItemPlacement);
/**
 * 
 */
UCLASS()
class PROJEKTZ_API UInventoryWidgetController : public UProjektZWidgetController
{
	GENERATED_BODY()


public:


	UPROPERTY(BlueprintAssignable, Category = "GAS|Messages")
	FItemChangedDelegate ItemChangedDelegate;
	
};
