// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectExecutionCalculation.h"
#include "ExecCalc_Effect.generated.h"

/**
 * 
 */
UCLASS()
class PROJEKTZ_API UExecCalc_Effect : public UGameplayEffectExecutionCalculation
{
	GENERATED_BODY()
public:

	UExecCalc_Effect();
	virtual void Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const override;
};