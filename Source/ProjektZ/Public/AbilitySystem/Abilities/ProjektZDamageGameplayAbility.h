// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/ProjektZGameplayAbility.h"
#include "ProjektZDamageGameplayAbility.generated.h"

/**
 * 
 */
UCLASS()
class PROJEKTZ_API UProjektZDamageGameplayAbility : public UProjektZGameplayAbility
{
	GENERATED_BODY()
	
public:

	UFUNCTION(BlueprintCallable)
	void CauseDamage(AActor* TargetActor);

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UGameplayEffect> DamageEffectClass;

	UPROPERTY(EditDefaultsOnly, Category = "Damage")
	TMap<FGameplayTag, FScalableFloat> DamageTypes;
};
