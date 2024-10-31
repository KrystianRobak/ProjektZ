// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/ProjektZGameplayAbility.h"
#include <AbilitySystemBlueprintLibrary.h>
#include <AbilitySystemComponent.h>
#include <ProjektZGameInstance.h>

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

void UProjektZGameplayAbility::CheckReactivness(FGameplayTag TagToCheck)
{
	AActor* Actor = this->GetAvatarActorFromActorInfo();

	UAbilitySystemComponent* ASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(Actor);

	FGameplayTagContainer Tags = ASC->GetOwnedGameplayTags();

	UProjektZGameInstance* GameInstance = Cast<UProjektZGameInstance>(this->GetWorld()->GetGameInstance());

	this->damage

	if (Tags.HasTagExact(TagToCheck))
	{

	}
	else
	{

	}
}

void UProjektZGameplayAbility::SetInputTag(FGameplayTag InTag)
{
	this->StartupInputTag = InTag;
}
