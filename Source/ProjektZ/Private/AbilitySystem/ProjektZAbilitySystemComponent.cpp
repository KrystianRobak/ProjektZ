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

	AbilitiesGivenDelegate.Broadcast(this);
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

FGameplayTag UProjektZAbilitySystemComponent::GetAbilityTagByInputTag(const FGameplayTag& InputTag)
{
	if (!InputTag.IsValid()) return FGameplayTag();

	for (FGameplayAbilitySpec& AbilitySpec : GetActivatableAbilities())
	{
		if (AbilitySpec.DynamicAbilityTags.HasTagExact(InputTag))
		{
			return 	AbilitySpec.Ability.Get()->AbilityTags.First();
		}
	}
	return FGameplayTag();
}

FGameplayAbilitySpec* UProjektZAbilitySystemComponent::GetAbilitySpecByInputTag(const FGameplayTag& InputTag)
{
	if (!InputTag.IsValid()) return nullptr;

	for (FGameplayAbilitySpec& AbilitySpec : GetActivatableAbilities())
	{
		if (AbilitySpec.DynamicAbilityTags.HasTagExact(InputTag))
		{
			return &AbilitySpec;
		}
	}
	return nullptr;
}

bool UProjektZAbilitySystemComponent::ChangeAbilitySpecInputTag(const FGameplayTag& AbilityInputTag, const FGameplayTag& NewInputTag)
{
	if (!AbilityInputTag.IsValid()) return false;

	for (FGameplayAbilitySpec& AbilitySpec : GetActivatableAbilities())
	{
		if (AbilitySpec.Ability.Get()->AbilityTags.First() == AbilityInputTag)
		{
			AbilitySpec.DynamicAbilityTags.RemoveTag(AbilitySpec.DynamicAbilityTags.First());
			AbilitySpec.DynamicAbilityTags.AddTag(NewInputTag);
			return true;
		}
	}
	return false;
}

void UProjektZAbilitySystemComponent::AbilityInputTagReleased(const FGameplayTag& InputTag)
{
	if (!InputTag.IsValid()) return;

	for (FGameplayAbilitySpec& AbilitySpec : GetActivatableAbilities())
	{
		if (AbilitySpec.DynamicAbilityTags.HasTagExact(InputTag))
		{
			AbilitySpecInputReleased(AbilitySpec);
			if (!AbilitySpec.IsActive())
			{
				TryActivateAbility(AbilitySpec.Handle);
			}
		}
	}
}

void UProjektZAbilitySystemComponent::ForEachAbility(const FForEachAbility& Delegate)
{
	FScopedAbilityListLock ActivableScopeLock(*this);
	for (const FGameplayAbilitySpec& AbilitySpec : GetActivatableAbilities())
	{
		if (!Delegate.ExecuteIfBound(AbilitySpec))
		{
			UE_LOG(LogTemp, Error, TEXT("Failed to execute delegate in %hs"), __FUNCTION__);
		}
	}
}

FGameplayTag UProjektZAbilitySystemComponent::GetAbilityTagFromSpec(const FGameplayAbilitySpec& AbilitySpec)
{
	if (AbilitySpec.Ability)
	{
		for (FGameplayTag Tag : AbilitySpec.Ability.Get()->AbilityTags)
		{
			if (Tag.MatchesTag(FGameplayTag::RequestGameplayTag(FName("Abilities"))))
			{
				return Tag;
			}
		}
	}
	
	return FGameplayTag();
}

FGameplayTag UProjektZAbilitySystemComponent::GetInputTagFromSpec(const FGameplayAbilitySpec& AbilitySpec)
{
	for (FGameplayTag Tag : AbilitySpec.DynamicAbilityTags)
	{
		if (Tag.MatchesTag(FGameplayTag::RequestGameplayTag(FName("InputTag"))))
		{
			return Tag;
		}
	}
	return FGameplayTag();
}

void UProjektZAbilitySystemComponent::OnRep_ActivateAbilities()
{
	Super::OnRep_ActivateAbilities();

	AbilitiesGivenDelegate.Broadcast(this);
}

void UProjektZAbilitySystemComponent::EffectApplied_Implementation(UAbilitySystemComponent* AbilitySystemComponent, const FGameplayEffectSpec& EffectSpec, FActiveGameplayEffectHandle ActiveEffectHandle)
{
	FGameplayTagContainer TagContainer;
	EffectSpec.GetAllAssetTags(TagContainer);

	EffectAssetTags.Broadcast(TagContainer);
}
