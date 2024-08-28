// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemGlobals.h"
#include "ProjektZAbilitySystemGlobals.generated.h"


/**
 * 
 */
UCLASS()
class PROJEKTZ_API UProjektZAbilitySystemGlobals : public UAbilitySystemGlobals
{
	GENERATED_BODY()
	
	virtual FGameplayEffectContext* AllocGameplayEffectContext() const override;

};
