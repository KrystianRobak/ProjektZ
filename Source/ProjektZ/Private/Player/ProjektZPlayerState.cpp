// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/ProjektZPlayerState.h"
#include <AbilitySystem/ProjektZAbilitySystemComponent.h>
#include <AbilitySystem/ProjektZAttributeSet.h>
#include <Net/UnrealNetwork.h>

AProjektZPlayerState::AProjektZPlayerState()
{
	AbilitySystemComponent = CreateDefaultSubobject<UProjektZAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);

	AttributeSet = CreateDefaultSubobject<UProjektZAttributeSet>("AttributeSet");

	NetUpdateFrequency = 100.f;
}

void AProjektZPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AProjektZPlayerState, Level);
}

UAbilitySystemComponent* AProjektZPlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void AProjektZPlayerState::OnRep_Level(int32 OldLevel)
{

}
