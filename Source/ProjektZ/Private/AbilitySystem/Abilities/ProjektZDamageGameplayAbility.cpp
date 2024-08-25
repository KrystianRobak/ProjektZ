// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/ProjektZDamageGameplayAbility.h"
#include "AbilitySystemBlueprintLibrary.h"

FDamageEffectParams UProjektZDamageGameplayAbility::MakeDamageEffectParamsFromClassDefaults(AActor* TargetActor) const
{
    FDamageEffectParams Params;
    Params.WorldContextObject = GetAvatarActorFromActorInfo();
    Params.DamageGameplayEffectClass = DamageEffectClass;
    Params.SourceAbilitySystemComponent = GetAbilitySystemComponentFromActorInfo();
    Params.TargetAbilitySystemComponent = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);

    Params.BaseDamage = Damage.GetValueAtLevel(GetAbilityLevel());
    Params.AbilityLevel = GetAbilityLevel();
    Params.DamageType = DamageType;
    
    return Params;
}
