// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "../Data/ElementsReactionMap.h"
#include "ProjektZGameplayAbility.generated.h"

/**
 * 
 */
UCLASS()
class PROJEKTZ_API UProjektZGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()
public:

	virtual void ApplyCooldown(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo) const;

	virtual bool CheckCooldown(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, OUT FGameplayTagContainer* OptionalRelevantTags) const;

	virtual void ApplyCost(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo) const;

	virtual bool CheckCost(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, OUT FGameplayTagContainer* OptionalRelevantTags) const;

	bool CanApplyAttributeModifiers(const UGameplayEffect* GameplayEffect, float Level, const FGameplayEffectContextHandle& EffectContext, UAbilitySystemComponent* AbilitySystemComponent) const;

	UFUNCTION(BlueprintCallable)
	void CheckReactivness(FGameplayTag TagToCheck);

public:
	UPROPERTY(EditDefaultsOnly, Category="Input")
	FGameplayTag StartupInputTag;

	UFUNCTION(BlueprintCallable)
	void SetInputTag(FGameplayTag InTag);

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Damage")
	FGameplayTag ElementType;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Cooldown")
	float CooldownDuration;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Cost")
	float Mana;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Cost")
	float Health;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Cost")
	float Stamina;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Cooldown")
	FGameplayTagContainer CooldownTag;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UGameplayEffect> ElementApplier;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	bool IsLockedInPlace = false;
};
