// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "ProjektZAbilitySystemComponent.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FEffectAssetTags, const FGameplayTagContainer& /* AssetTags */);
DECLARE_MULTICAST_DELEGATE_OneParam(FAbilitiesGiven, UProjektZAbilitySystemComponent*);
DECLARE_DELEGATE_OneParam(FForEachAbility, const FGameplayAbilitySpec&);

USTRUCT()
struct FAbilityData
{
	GENERATED_BODY()

	UPROPERTY()
	FGameplayAbilitySpecHandle AbilitySpecHandle;

	UPROPERTY()
	TSubclassOf<UGameplayAbility> AbilityClass;
};
/**
 * 
 */
UCLASS()
class PROJEKTZ_API UProjektZAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()
public:
	void AbilityActorInfoSet();

	FEffectAssetTags EffectAssetTags;
	FAbilitiesGiven AbilitiesGivenDelegate;

	void AddAbility(const TSubclassOf<UGameplayAbility>& Ability, float Level, FAbilityData& Data);

	void AbilityInputTagHeld(const FGameplayTag& InputTag);

	FGameplayTag GetAbilityTagByInputTag(const FGameplayTag& InputTag);

	FGameplayAbilitySpec* GetAbilitySpecByInputTag(const FGameplayTag& InputTag);

	UFUNCTION(BlueprintCallable)
	bool ChangeAbilitySpecInputTag(const FGameplayTag& AbilityInputTag, const FGameplayTag& NewInputTag);

	void AbilityInputTagReleased(const FGameplayTag& InputTag);

	void ForEachAbility(const FForEachAbility& Delegate);

	static FGameplayTag GetAbilityTagFromSpec(const FGameplayAbilitySpec& AbilitySpec);
	static FGameplayTag GetInputTagFromSpec(const FGameplayAbilitySpec& AbilitySpec);

protected:

	virtual void OnRep_ActivateAbilities();
	
	UFUNCTION(Client, Reliable)
	void EffectApplied(UAbilitySystemComponent* AbilitySystemComponent, const FGameplayEffectSpec& EffectSpec, FActiveGameplayEffectHandle ActiveEffectHandle);
	
};
