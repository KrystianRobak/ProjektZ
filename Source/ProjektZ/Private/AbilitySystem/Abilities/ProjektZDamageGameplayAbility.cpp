// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/ProjektZDamageGameplayAbility.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include <AbilitySystem/ProjektZAbilitySystemLibrary.h>

void UProjektZDamageGameplayAbility::CauseDamage(AActor* TargetActor)
{
    FGameplayEffectSpecHandle DamageSpecHandle = MakeOutgoingGameplayEffectSpec(DamageEffectClass, 1.f);
    const float ScaledDamage = Damage.GetValueAtLevel(GetAbilityLevel());
    UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(DamageSpecHandle, *FProjektZGameplayTags::Get().ElementTypesToDamageTypes.Find(ElementType), ScaledDamage);
    GetAbilitySystemComponentFromActorInfo()->ApplyGameplayEffectSpecToTarget(*DamageSpecHandle.Data.Get(), UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor));
}

void UProjektZDamageGameplayAbility::PlayerDealDamage(AActor* TargetActor)
{
    if(HasAuthority(&CurrentActivationInfo))
    {
        if (UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor))
        {
            FDamageEffectParams DamageEffectParams = MakeDamageEffectParamsFromClassDefaults();
            DamageEffectParams.TargetAbilitySystemComponent = TargetASC;
            UProjektZAbilitySystemLibrary::ApplyDamageEffect(DamageEffectParams);
             if (EffectParams.Num() > 0)
            {
                for (FEffectParams& Param : EffectParams)
                {
                    UProjektZAbilitySystemLibrary::ApplyEffect(Param, TargetASC, GetAvatarActorFromActorInfo());
                }
            }
        }
    }
}

FTaggedMontage UProjektZDamageGameplayAbility::GetRandomTaggedMontageFromArray(const TArray<FTaggedMontage>& TaggedMontages) const
{
    if (TaggedMontages.Num() > 0)
    {
        const int32 Selection = FMath::RandRange(0, TaggedMontages.Num() - 1);
        return TaggedMontages[Selection];

    }

    return FTaggedMontage();
}

FDamageEffectParams UProjektZDamageGameplayAbility::MakeDamageEffectParamsFromClassDefaults(AActor* TargetActor) const
{
    FDamageEffectParams Params;
    Params.WorldContextObject = GetAvatarActorFromActorInfo();
    Params.DamageGameplayEffectClass = DamageEffectClass;
    Params.ElementApplierEffectClass = ElementApplier;
    Params.SourceAbilitySystemComponent = GetAbilitySystemComponentFromActorInfo();
    Params.TargetAbilitySystemComponent = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);

    Params.BaseDamage = Damage.GetValueAtLevel(GetAbilityLevel());
    Params.AbilityLevel = GetAbilityLevel(); 
    Params.DamageType = *FProjektZGameplayTags::Get().ElementTypesToDamageTypes.Find(ElementType);
    Params.ConditionType = *FProjektZGameplayTags::Get().ElementTypesToConditionType.Find(ElementType);
    Params.ElementTag = ElementType;

    return Params;
}

void UProjektZDamageGameplayAbility::ApplyCooldown(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo) const
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
