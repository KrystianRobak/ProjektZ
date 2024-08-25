// Fill out your copyright notice in the Description page of Project Settings.

#include "Character/PlayerCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Player/ProjektZPlayerState.h"
#include "Player/PC_PlayerController.h"
#include <UI/HUD/ProjektZHUD.h>
#include <AbilitySystem/ProjektZAbilitySystemComponent.h>
#include <AbilitySystem/Abilities/ProjektZGameplayAbility.h>

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

float APlayerCharacter::GetFirstFreeSlot()
{
	for (int i = 0; i < MaxAbilities; i++)
	{
		if (!SlotsOccupancy[i])
			return i;
	}
	return -1;
}

void APlayerCharacter::RemoveCharacterAbility(float Slot)
{
	if (AbilitySystemComponent && HasAuthority())
	{
		UProjektZAbilitySystemComponent* ASC = CastChecked<UProjektZAbilitySystemComponent>(AbilitySystemComponent);
		ASC->ClearAbility(Abilities[Slot].AbilitySpecHandle);
		SlotsOccupancy[Slot] = false;
	}
}

void APlayerCharacter::AddCharacterAbility(TSubclassOf<UProjektZGameplayAbility>& Ability, float Level, float Slot)
{
	if (AbilitySystemComponent && HasAuthority())
	{
		if (SlotsOccupancy[Slot])
		{
			RemoveCharacterAbility(Slot);
		}
		UProjektZAbilitySystemComponent* ASC = CastChecked<UProjektZAbilitySystemComponent>(AbilitySystemComponent);

		FAbilityData& Data = Abilities[Slot];
		ASC->AddAbility(Ability, Level, Data);
		SlotsOccupancy[Slot] = true;
	}
}

void APlayerCharacter::SwapSlotsAbilities(float Slot1, float Slot2)
{
	FAbilityData TempData = Abilities[Slot1];
	bool TempOccupancy = SlotsOccupancy[Slot1];

	Abilities[Slot1] = Abilities[Slot2];
	SlotsOccupancy[Slot1] = SlotsOccupancy[Slot2];

	Abilities[Slot2] = TempData;
	SlotsOccupancy[Slot2] = TempOccupancy;
}

int32 APlayerCharacter::GetPlayerLevel()
{
	AProjektZPlayerState* ProjektZPlayerState = GetPlayerState<AProjektZPlayerState>();
	check(ProjektZPlayerState);
	return ProjektZPlayerState->GetPlayerLevel();
}

void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	for (int i = 0; i < MaxAbilities; i++)
	{
		SlotsOccupancy.Add(false);
		Abilities.Add(FAbilityData());
	}
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


