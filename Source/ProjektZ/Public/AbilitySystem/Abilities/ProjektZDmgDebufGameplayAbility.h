// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/ProjektZGameplayAbility.h"
#include <ProjektZAbilityTypes.h>
#include "ProjektZDmgDebufGameplayAbility.generated.h"

/**
 * 
 */
UCLASS()
class PROJEKTZ_API UProjektZDmgDebufGameplayAbility : public UProjektZGameplayAbility
{
	GENERATED_BODY()
public:

	FDebuffEffectParams MakeEffectParamsFromClassDefaults(AActor* TargetActor = nullptr) const;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UGameplayEffect> DamageEffectClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UGameplayEffect> DebuffEffectClass;

	UPROPERTY(EditDefaultsOnly, Category = "Damage")
	FGameplayTag DamageType;

	UPROPERTY(EditDefaultsOnly, Category = "Damage")
	FScalableFloat Damage;

	UPROPERTY(EditDefaultsOnly, Category = "Damage")
	TArray<FEffectParams> DebuffEffectParams;
};
