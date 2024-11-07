// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "GameplayTagContainer.h"
#include "ReactiveInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UReactiveInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class PROJEKTZ_API IReactiveInterface
{
	GENERATED_BODY()

	UFUNCTION(BlueprintCallable)
	FGameplayTag GetElementTag();

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
};
