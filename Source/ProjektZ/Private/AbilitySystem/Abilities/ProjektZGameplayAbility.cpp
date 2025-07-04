// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/ProjektZGameplayAbility.h"
#include <AbilitySystemBlueprintLibrary.h>
#include <AbilitySystemComponent.h>
#include <ProjektZGameInstance.h>
#include "AbilitySystemGlobals.h"
#include "AbilitySystem/ProjektZAttributeSet.h"

void UProjektZGameplayAbility::ApplyCooldown(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo) const
{
	UGameplayEffect* CooldownGE = GetCooldownGameplayEffect();
	if (CooldownGE)
	{
		FGameplayEffectSpecHandle SpecHandle = MakeOutgoingGameplayEffectSpec(CooldownGE->GetClass(), GetAbilityLevel());
		SpecHandle.Data.Get()->DynamicGrantedTags.AppendTags(CooldownTag);

		SpecHandle.Data.Get()->SetSetByCallerMagnitude(FGameplayTag::RequestGameplayTag(FName("Cooldown")), CooldownDuration);
		ApplyGameplayEffectSpecToOwner(Handle, ActorInfo, ActivationInfo, SpecHandle);
	}
}

bool UProjektZGameplayAbility::CheckCooldown(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, OUT FGameplayTagContainer* OptionalRelevantTags) const
{
	if (!ensure(ActorInfo))
	{
		return true;
	}
	
	if (!CooldownTag.IsEmpty())
	{
		if (UAbilitySystemComponent* AbilitySystemComponent = ActorInfo->AbilitySystemComponent.Get())
		{
			if (AbilitySystemComponent->HasAnyMatchingGameplayTags(CooldownTag))
			{
				if (OptionalRelevantTags)
				{
					const FGameplayTag& FailCooldownTag = UAbilitySystemGlobals::Get().ActivateFailCooldownTag;
					if (FailCooldownTag.IsValid())
					{
						OptionalRelevantTags->AddTag(FailCooldownTag);
					}

					// Let the caller know which tags were blocking
					OptionalRelevantTags->AppendMatchingTags(AbilitySystemComponent->GetOwnedGameplayTags(), CooldownTag);
				}

				return false;
			}
		}
	}
	return true;
}

void UProjektZGameplayAbility::ApplyCost(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo) const
{
	UGameplayEffect* CostGE = GetCostGameplayEffect();
	if (CostGE)
	{
		FGameplayEffectSpecHandle SpecHandle = MakeOutgoingGameplayEffectSpec(CostGE->GetClass(), GetAbilityLevel());
		SpecHandle.Data.Get()->DynamicGrantedTags.AppendTags(CooldownTag);

		SpecHandle.Data.Get()->SetSetByCallerMagnitude(FGameplayTag::RequestGameplayTag(FName("Cost.Health")), Health);
		SpecHandle.Data.Get()->SetSetByCallerMagnitude(FGameplayTag::RequestGameplayTag(FName("Cost.Mana")), Mana);
		SpecHandle.Data.Get()->SetSetByCallerMagnitude(FGameplayTag::RequestGameplayTag(FName("Cost.Stamina")), Stamina);

		ApplyGameplayEffectSpecToOwner(Handle, ActorInfo, ActivationInfo, SpecHandle);
	}
}

bool UProjektZGameplayAbility::CheckCost(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, OUT FGameplayTagContainer* OptionalRelevantTags) const
{
	UGameplayEffect* CostGE = GetCostGameplayEffect();
	if (CostGE)
	{
		UAbilitySystemComponent* AbilitySystemComponent = ActorInfo ? ActorInfo->AbilitySystemComponent.Get() : nullptr;
		if (ensure(AbilitySystemComponent))
		{
			if (!CanApplyAttributeModifiers(CostGE, GetAbilityLevel(Handle, ActorInfo), MakeEffectContext(Handle, ActorInfo), AbilitySystemComponent))
			{
				const FGameplayTag& CostTag = UAbilitySystemGlobals::Get().ActivateFailCostTag;

				if (OptionalRelevantTags && CostTag.IsValid())
				{
					OptionalRelevantTags->AddTag(CostTag);
				}
				return false;
			}
		}
	}
	return true;
}

bool UProjektZGameplayAbility::CanApplyAttributeModifiers(const UGameplayEffect* GameplayEffect, float Level, const FGameplayEffectContextHandle& EffectContext, UAbilitySystemComponent* AbilitySystemComponent) const
{
	FGameplayEffectSpec Spec(GameplayEffect, EffectContext, Level);

	for (int32 ModIdx = 0; ModIdx < Spec.Modifiers.Num(); ++ModIdx)
	{
		const FGameplayModifierInfo& ModDef = Spec.Def->Modifiers[ModIdx];
		const FModifierSpec& ModSpec = Spec.Modifiers[ModIdx];

		if (ModDef.ModifierOp == EGameplayModOp::Additive)
		{
			if (!ModDef.Attribute.IsValid())
			{
				continue;
			}

			float CurrentValue = 0;
			float CostValue = 0;

			if (ModDef.Attribute.AttributeName == UProjektZAttributeSet::GetManaAttribute().AttributeName)
			{
				CurrentValue = AbilitySystemComponent->GetNumericAttribute(UProjektZAttributeSet::GetManaAttribute());
				CostValue = Mana;
			}
			else if (ModDef.Attribute.AttributeName == UProjektZAttributeSet::GetHealthAttribute().AttributeName)
			{
				CurrentValue = AbilitySystemComponent->GetNumericAttribute(UProjektZAttributeSet::GetHealthAttribute());
				CostValue = Health;
			}
			else if (ModDef.Attribute.AttributeName == UProjektZAttributeSet::GetStaminaAttribute().AttributeName)
			{
				CurrentValue = AbilitySystemComponent->GetNumericAttribute(UProjektZAttributeSet::GetStaminaAttribute());
				CostValue = Stamina;
			}

			if (CurrentValue + CostValue < 0.f)
			{
				return false;
			}
		}
	}
	return true;
}


void UProjektZGameplayAbility::CheckReactivness(FGameplayTag TagToCheck)
{
	AActor* Actor = this->GetAvatarActorFromActorInfo();

	UAbilitySystemComponent* ASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(Actor);

	FGameplayTagContainer Tags = ASC->GetOwnedGameplayTags();

	UProjektZGameInstance* GameInstance = Cast<UProjektZGameInstance>(this->GetWorld()->GetGameInstance());
}

void UProjektZGameplayAbility::SetInputTag(FGameplayTag InTag)
{
	this->StartupInputTag = InTag;
}
