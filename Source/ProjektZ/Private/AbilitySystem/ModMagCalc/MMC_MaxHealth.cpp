// Fill out your copyright notice in the Description page of Project Settings.

#include "AbilitySystem/ModMagCalc/MMC_MaxHealth.h"
#include "./AbilitySystem/ProjektZAttributeSet.h"
#include <Interaction/CombatInterface.h>

UMMC_MaxHealth::UMMC_MaxHealth()
{
    VitalityDef.AttributeToCapture = UProjektZAttributeSet::GetVitalityAttribute();
    VitalityDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;
    VitalityDef.bSnapshot = false;

    RelevantAttributesToCapture.Add(VitalityDef);
}

float UMMC_MaxHealth::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
    // Gather tags from source and target
    const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
    const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();

    FAggregatorEvaluateParameters EvaulationParameters;
    EvaulationParameters.SourceTags = SourceTags;
    EvaulationParameters.TargetTags = TargetTags;

    float Vitality = 0.f;

    GetCapturedAttributeMagnitude(VitalityDef, Spec, EvaulationParameters, Vitality);
    Vitality = FMath::Max<float>(Vitality, 0);

    ICombatInterface* CombatInterface = Cast<ICombatInterface>(Spec.GetContext().GetSourceObject());
    int32 PlayerLevel = 1;
    if (CombatInterface)
    {
        PlayerLevel = CombatInterface->GetPlayerLevel();
    }

    return 100.f + 10.f * Vitality;
}