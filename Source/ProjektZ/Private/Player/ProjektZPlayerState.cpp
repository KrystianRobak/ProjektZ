// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/ProjektZPlayerState.h"
#include <AbilitySystem/ProjektZAbilitySystemComponent.h>
#include <AbilitySystem/ProjektZAttributeSet.h>

AProjektZPlayerState::AProjektZPlayerState()
{
	AbilitySystemComponent = CreateDefaultSubobject<UProjektZAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);

	AttributeSet = CreateDefaultSubobject<UProjektZAttributeSet>("AttributeSet");

	NetUpdateFrequency = 100.f;
}

UAbilitySystemComponent* AProjektZPlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}
