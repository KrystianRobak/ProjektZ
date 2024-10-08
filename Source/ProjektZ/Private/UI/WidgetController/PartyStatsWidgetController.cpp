// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/WidgetController/PartyStatsWidgetController.h"
#include "AbilitySystem/ProjektZAttributeSet.h"
#include "GameFramework/GameStateBase.h"
#include "Player/ProjektZPlayerState.h"

void UPartyStatsWidgetController::BroadcastInitialValues()
{
	AGameStateBase* GameState = GetWorld()->GetGameState();

	for (auto Player : GameState->PlayerArray)
	{
		AProjektZPlayerState* RemotePlayerState = Cast<AProjektZPlayerState>(Player);
		const UProjektZAttributeSet* ProjektZAttributeSet = CastChecked<UProjektZAttributeSet>(RemotePlayerState->GetAttributeSet());

		OnHealthChanged.Broadcast(ProjektZAttributeSet->GetHealth(), ProjektZAttributeSet->GetMaxHealth(), RemotePlayerState->GetPlayerId());
		OnMaxHealthChanged.Broadcast(ProjektZAttributeSet->GetHealth(), ProjektZAttributeSet->GetMaxHealth(), RemotePlayerState->GetPlayerId());

		OnManaChanged.Broadcast(ProjektZAttributeSet->GetMana(), ProjektZAttributeSet->GetMaxMana(), RemotePlayerState->GetPlayerId());
		OnMaxManaChanged.Broadcast(ProjektZAttributeSet->GetMaxMana(), ProjektZAttributeSet->GetMana(), RemotePlayerState->GetPlayerId());
	}
}

void UPartyStatsWidgetController::BindCallbackToDependencies()
{
	AGameStateBase* GameState = GetWorld()->GetGameState();

	for (auto Player : GameState->PlayerArray)
	{
		AProjektZPlayerState* RemotePlayerState = Cast<AProjektZPlayerState>(Player);
		UAbilitySystemComponent* PlayerASC = RemotePlayerState->GetAbilitySystemComponent();
		const UProjektZAttributeSet* ProjektZAttributeSet = CastChecked<UProjektZAttributeSet>(RemotePlayerState->GetAttributeSet());
		
		PlayerASC->GetGameplayAttributeValueChangeDelegate(ProjektZAttributeSet->GetHealthAttribute()).AddLambda(
			[this, RemotePlayerState, ProjektZAttributeSet](const FOnAttributeChangeData& Data)
			{
				ProjektZAttributeSet->GetMaxHealth();
				OnHealthChanged.Broadcast(Data.NewValue, ProjektZAttributeSet->GetMaxHealth(), RemotePlayerState->GetPlayerId());
			}
		);

		PlayerASC->GetGameplayAttributeValueChangeDelegate(ProjektZAttributeSet->GetMaxHealthAttribute()).AddLambda(
			[this, RemotePlayerState, ProjektZAttributeSet](const FOnAttributeChangeData& Data)
			{
				OnMaxHealthChanged.Broadcast(ProjektZAttributeSet->GetHealth(), Data.NewValue, RemotePlayerState->GetPlayerId());
			}
		);

		PlayerASC->GetGameplayAttributeValueChangeDelegate(ProjektZAttributeSet->GetManaAttribute()).AddLambda(
			[this, RemotePlayerState, ProjektZAttributeSet](const FOnAttributeChangeData& Data)
			{
				OnManaChanged.Broadcast(Data.NewValue, ProjektZAttributeSet->GetMaxMana(), RemotePlayerState->GetPlayerId());
			}
		);

		PlayerASC->GetGameplayAttributeValueChangeDelegate(ProjektZAttributeSet->GetMaxManaAttribute()).AddLambda(
			[this, RemotePlayerState, ProjektZAttributeSet](const FOnAttributeChangeData& Data)
			{
				OnMaxManaChanged.Broadcast(ProjektZAttributeSet->GetMana(), Data.NewValue, RemotePlayerState->GetPlayerId());
			}
		);
	}

}