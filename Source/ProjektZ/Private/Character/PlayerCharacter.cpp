// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/PlayerCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Player/ProjektZPlayerState.h"
#include "Player/PC_PlayerController.h"
#include <UI/HUD/ProjektZHUD.h>
#include <AbilitySystem/ProjektZAbilitySystemComponent.h>

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

int32 APlayerCharacter::GetPlayerLevel()
{
	AProjektZPlayerState* ProjektZPlayerState = GetPlayerState<AProjektZPlayerState>();
	check(ProjektZPlayerState);
	return ProjektZPlayerState->GetPlayerLevel();
}

void APlayerCharacter::InitAbilityActorInfo()
{
	AProjektZPlayerState* ProjektZPlayerState = GetPlayerState<AProjektZPlayerState>();
	check(ProjektZPlayerState);
	ProjektZPlayerState->GetAbilitySystemComponent()->InitAbilityActorInfo(ProjektZPlayerState, this);
	Cast<UProjektZAbilitySystemComponent>(ProjektZPlayerState->GetAbilitySystemComponent())->AbilityActorInfoSet();
	AbilitySystemComponent = ProjektZPlayerState->GetAbilitySystemComponent();
	AttributeSet = ProjektZPlayerState->GetAttributeSet();

	if (APC_PlayerController* ProjektZPlayerController = Cast<APC_PlayerController>(GetController())) 
	{
		if (AProjektZHUD* ProjektZHUD = Cast<AProjektZHUD>(ProjektZPlayerController->GetHUD()))
		{
			ProjektZHUD->InitOverlay(ProjektZPlayerController, ProjektZPlayerState, AbilitySystemComponent, AttributeSet);
		}
	}
	InitializeDefaultAttributes();
}


