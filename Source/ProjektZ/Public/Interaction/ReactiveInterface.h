// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "GameplayTagContainer.h"
#include "ReactiveInterface.generated.h"


UINTERFACE(BlueprintType, MinimalAPI)
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

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:


	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void React(FGameplayTag IncomingElementType);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	bool HasReacted();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void SetReacted(bool value);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	FGameplayTag GetElementTag();
};
