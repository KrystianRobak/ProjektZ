// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/ProjektZDamageGameplayAbility.h"
#include "ProjectZProjectileSpell.generated.h"


class AProjectile;
/**
 * 
 */
UCLASS()
class PROJEKTZ_API UProjectZProjectileSpell : public UProjektZDamageGameplayAbility
{
	GENERATED_BODY()
protected:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData);

	UFUNCTION(BlueprintCallable, Category = "Projectile")
	virtual void SpawnProjectile(const FVector& ProjectileTargetLocation);

protected:

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<AProjectile> ProjectileClass;
};
