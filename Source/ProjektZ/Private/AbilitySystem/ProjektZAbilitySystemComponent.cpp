// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/ProjektZAbilitySystemComponent.h"
#include "ProjektZGameplayTags.h"
#include <AbilitySystem/Abilities/ProjektZGameplayAbility.h>

void UProjektZAbilitySystemComponent::AbilityActorInfoSet()
{
	OnGameplayEffectAppliedDelegateToSelf.AddUObject(this, &UProjektZAbilitySystemComponent::EffectApplied);


}

void UProjektZAbilitySystemComponent::AddAbility(const TSubclassOf<UGameplayAbility>& Ability, float Level, FAbilityData &Data)
{
	FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(Ability, Level);
	Data.AbilityClass = Ability;
	if (const UProjektZGameplayAbility* CastedAbility = Cast<UProjektZGameplayAbility>(AbilitySpec.Ability))
	{
		AbilitySpec.DynamicAbilityTags.AddTag(CastedAbility->StartupInputTag);
		Data.AbilitySpecHandle = GiveAbility(AbilitySpec);
	}
}

void UProjektZAbilitySystemComponent::AbilityInputTagHeld(const FGameplayTag& InputTag)
{
	if (!InputTag.IsValid()) return;

	for (FGameplayAbilitySpec& AbilitySpec : GetActivatableAbilities())
	{
		if (AbilitySpec.DynamicAbilityTags.HasTagExact(InputTag))
		{
			AbilitySpecInputPressed(AbilitySpec);
			if (!AbilitySpec.IsActive())
			{
				TryActivateAbility(AbilitySpec.Handle);
			}
		}
	}
}

void UProjektZAbilitySystemComponent::AbilityInputTagReleased(const FGameplayTag& InputTag)
{
	if (!InputTag.IsValid()) return;

	for (FGameplayAbilitySpec& AbilitySpec : GetActivatableAbilities())
	{
		if (AbilitySpec.DynamicAbilityTags.HasTagExact(InputTag))
		{
			AbilitySpecInputReleased(AbilitySpec);
		}
	}
}

void UProjektZAbilitySystemComponent::EffectApplied(UAbilitySystemComponent* AbilitySystemComponent, const FGameplayEffectSpec& EffectSpec, FActiveGameplayEffectHandle ActiveEffectHandle)
{
	FGameplayTagContainer TagContainer;
	EffectSpec.GetAllAssetTags(TagContainer);

	EffectAssetTags.Broadcast(TagContainer);
}
