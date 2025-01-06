// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjektZAbilitySystemGlobals.h"

#include "ProjektZAbilityTypes.h"

FGameplayEffectContext* UProjektZAbilitySystemGlobals::AllocGameplayEffectContext() const
{
	return new FProjektZGameplayEffectContext();
}
