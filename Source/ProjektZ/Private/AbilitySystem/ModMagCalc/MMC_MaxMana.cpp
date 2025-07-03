// Fill out your copyright notice in the Description page of Project Settings.

#include "AbilitySystem/ModMagCalc/MMC_MaxMana.h"
#include "./AbilitySystem/ProjektZAttributeSet.h"
#include <Interaction/CombatInterface.h>

UMMC_MaxMana::UMMC_MaxMana()
{
    IntelligenceDef.AttributeToCapture = UProjektZAttributeSet::GetIntelligenceAttribute();
    IntelligenceDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;
    IntelligenceDef.bSnapshot = false;

    RelevantAttributesToCapture.Add(IntelligenceDef);
}

float UMMC_MaxMana::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
    // Gather tags from source and target
    const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
    const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();

    FAggregatorEvaluateParameters EvaulationParameters;
    EvaulationParameters.SourceTags = SourceTags;
    EvaulationParameters.TargetTags = TargetTags;

    float Intelligence = 0.f;
 
    GetCapturedAttributeMagnitude(IntelligenceDef, Spec, EvaulationParameters, Intelligence);
    Intelligence = FMath::Max<float>(Intelligence, 0);


    ICombatInterface* CombatInterface = Cast<ICombatInterface>(Spec.GetContext().GetSourceObject());
    int32 PlayerLevel = 1;
    if (CombatInterface)
    {
        PlayerLevel = CombatInterface->GetPlayerLevel();
    }

    return 50.f + 5.f * Intelligence;
}
