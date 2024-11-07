// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/ProjektZDmgDebufGameplayAbility.h"
#include "AbilitySystemBlueprintLibrary.h"

FDebuffEffectParams UProjektZDmgDebufGameplayAbility::MakeEffectParamsFromClassDefaults(AActor* TargetActor) const
{
    FDebuffEffectParams Params;
    Params.WorldContextObject = GetAvatarActorFromActorInfo();
    Params.DamageGameplayEffectClass = DamageEffectClass;
    Params.SourceAbilitySystemComponent = GetAbilitySystemComponentFromActorInfo();
    Params.TargetAbilitySystemComponent = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);

    Params.DamageType = ElementType;
    
    return Params;
}
