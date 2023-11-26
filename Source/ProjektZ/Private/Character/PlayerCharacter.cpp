// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/PlayerCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Player/ProjektZPlayerState.h"

APlayerCharacter::APlayerCharacter()
{
	GetCharacterMovement()->bUseControllerDesiredRotation = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 400.f, 0.f);
}

void APlayerCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	// Init ability actor info for the Server
	InitAbilityActorInfo();

}

void APlayerCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();
	// Init ability actor info for the Client
	InitAbilityActorInfo();
}

void APlayerCharacter::InitAbilityActorInfo()
{
	AProjektZPlayerState* ProjektZPlayerState = GetPlayerState<AProjektZPlayerState>();
	check(ProjektZPlayerState);
	ProjektZPlayerState->GetAbilitySystemComponent()->InitAbilityActorInfo(ProjektZPlayerState, this);
	AbilitySystemComponent = ProjektZPlayerState->GetAbilitySystemComponent();
	AttributeSet = ProjektZPlayerState->GetAttributeSet();
}


