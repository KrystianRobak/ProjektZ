// Fill out your copyright notice in the Description page of Project Settings.

#include "AbilitySystem/ExecCalc/ExecCalc_Damage.h"


#include "ProjektZGameplayTags.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystem/ProjektZAttributeSet.h"
#include <AbilitySystem/Data/CharacterClassInfo.h>
#include <AbilitySystem/ProjektZAbilitySystemLibrary.h>
#include <Interaction/CombatInterface.h>
#include "ProjektZAbilityTypes.h"
#include <ProjektZGameInstance.h>


bool CheckReactivness(AActor* Target, const UAbilitySystemComponent* TargetASC, FGameplayTag TagToCheck, const FGameplayTagContainer* TargetTags)
{
	FGameplayTagContainer Tags = TargetASC->GetOwnedGameplayTags();

	UProjektZGameInstance* GameInstance = Cast<UProjektZGameInstance>(Target->GetWorld()->GetGameInstance());

	return GameInstance->GetElementsReaction()->IsTagReactive(TagToCheck, *TargetTags);
}

struct ProjektZDamageStatics
{
	// TARGET ATTRIBUTES
	DECLARE_ATTRIBUTE_CAPTUREDEF(Armor);
	DECLARE_ATTRIBUTE_CAPTUREDEF(BlockChance);
	DECLARE_ATTRIBUTE_CAPTUREDEF(CriticalHitResistance);

	DECLARE_ATTRIBUTE_CAPTUREDEF(FireResistance);
	DECLARE_ATTRIBUTE_CAPTUREDEF(FrostResistance);
	DECLARE_ATTRIBUTE_CAPTUREDEF(LightningResistance);
	DECLARE_ATTRIBUTE_CAPTUREDEF(LightResistance);
	DECLARE_ATTRIBUTE_CAPTUREDEF(PhysicalResistance);
	DECLARE_ATTRIBUTE_CAPTUREDEF(PoisonResistance);

	// SOURCE ATTRIBUTES
	DECLARE_ATTRIBUTE_CAPTUREDEF(PhysicalDamage); // Replaces WeaponDamage
	DECLARE_ATTRIBUTE_CAPTUREDEF(MagicPower);     // New: for magic attacks
	DECLARE_ATTRIBUTE_CAPTUREDEF(ArmorPenetration);
	DECLARE_ATTRIBUTE_CAPTUREDEF(CriticalHitChance);
	DECLARE_ATTRIBUTE_CAPTUREDEF(CriticalHitDamage);

	DECLARE_ATTRIBUTE_CAPTUREDEF(FireAmplification);
	DECLARE_ATTRIBUTE_CAPTUREDEF(FrostAmplification);
	DECLARE_ATTRIBUTE_CAPTUREDEF(LightningAmplification);
	DECLARE_ATTRIBUTE_CAPTUREDEF(LightAmplification);
	DECLARE_ATTRIBUTE_CAPTUREDEF(PoisonAmplification);
	DECLARE_ATTRIBUTE_CAPTUREDEF(OverallMagicAmplification);


	// STAT TRACKING ATTRIBUTES (Assuming these are still relevant)
	DECLARE_ATTRIBUTE_CAPTUREDEF(DamageTanked); // Target stat
	DECLARE_ATTRIBUTE_CAPTUREDEF(DamageDealt); // Source stat
	// Specific damage dealt types are now harder to track with one damage type per ability,
	// but we can keep them if you still want to sum total elemental damage dealt.
	DECLARE_ATTRIBUTE_CAPTUREDEF(FireDamageDealt);
	DECLARE_ATTRIBUTE_CAPTUREDEF(FrostDamageDealt);
	DECLARE_ATTRIBUTE_CAPTUREDEF(LightningDamageDealt);
	DECLARE_ATTRIBUTE_CAPTUREDEF(PhysicalDamageDealt);
	DECLARE_ATTRIBUTE_CAPTUREDEF(PoisonDamageDealt);
	DECLARE_ATTRIBUTE_CAPTUREDEF(LightDamageDealt); // Assuming you'll have this for Light damage

	TMap<FGameplayTag, FGameplayEffectAttributeCaptureDefinition> TagsToCaptureDef;

	ProjektZDamageStatics()
	{
		// TARGET ATTRIBUTE DEFINITIONS
		DEFINE_ATTRIBUTE_CAPTUREDEF(UProjektZAttributeSet, Armor, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UProjektZAttributeSet, BlockChance, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UProjektZAttributeSet, CriticalHitResistance, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UProjektZAttributeSet, FireResistance, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UProjektZAttributeSet, FrostResistance, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UProjektZAttributeSet, LightningResistance, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UProjektZAttributeSet, LightResistance, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UProjektZAttributeSet, PhysicalResistance, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UProjektZAttributeSet, PoisonResistance, Target, false);

		// SOURCE ATTRIBUTE DEFINITIONS
		DEFINE_ATTRIBUTE_CAPTUREDEF(UProjektZAttributeSet, PhysicalDamage, Source, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UProjektZAttributeSet, MagicPower, Source, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UProjektZAttributeSet, ArmorPenetration, Source, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UProjektZAttributeSet, CriticalHitChance, Source, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UProjektZAttributeSet, CriticalHitDamage, Source, false);

		DEFINE_ATTRIBUTE_CAPTUREDEF(UProjektZAttributeSet, FireAmplification, Source, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UProjektZAttributeSet, FrostAmplification, Source, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UProjektZAttributeSet, LightningAmplification, Source, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UProjektZAttributeSet, LightAmplification, Source, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UProjektZAttributeSet, PoisonAmplification, Source, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UProjektZAttributeSet, OverallMagicAmplification, Source, false);


		// TARGET STAT TRACK DEFINITIONS
		DEFINE_ATTRIBUTE_CAPTUREDEF(UProjektZAttributeSet, DamageTanked, Target, false);

		// SOURCE STAT TRACK DEFINITIONS
		DEFINE_ATTRIBUTE_CAPTUREDEF(UProjektZAttributeSet, DamageDealt, Source, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UProjektZAttributeSet, FireDamageDealt, Source, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UProjektZAttributeSet, FrostDamageDealt, Source, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UProjektZAttributeSet, LightningDamageDealt, Source, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UProjektZAttributeSet, PhysicalDamageDealt, Source, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UProjektZAttributeSet, PoisonDamageDealt, Source, false);
		//DEFINE_ATTRIBUTE_CAPTUREDEF(UProjektZAttributeSet, LightDamageDealt, Source, false); // Make sure this is also defined in your AttributeSet


		const FProjektZGameplayTags& Tags = FProjektZGameplayTags::Get();

		// Populate TagsToCaptureDef Map (Target)
		TagsToCaptureDef.Add(Tags.Attributes_Secondary_Armor, ArmorDef);
		TagsToCaptureDef.Add(Tags.Attributes_Secondary_BlockChance, BlockChanceDef);
		TagsToCaptureDef.Add(Tags.Attributes_Secondary_CriticalHitResistance, CriticalHitResistanceDef);
		TagsToCaptureDef.Add(Tags.Attributes_Resistance_Fire, FireResistanceDef);
		TagsToCaptureDef.Add(Tags.Attributes_Resistance_Frost, FrostResistanceDef);
		TagsToCaptureDef.Add(Tags.Attributes_Resistance_Lightning, LightningResistanceDef);
		TagsToCaptureDef.Add(Tags.Attributes_Resistance_Light, LightResistanceDef);
		TagsToCaptureDef.Add(Tags.Attributes_Resistance_Physical, PhysicalResistanceDef);
		TagsToCaptureDef.Add(Tags.Attributes_Resistance_Poison, PoisonResistanceDef);

		// Populate TagsToCaptureDef Map (Source)
		TagsToCaptureDef.Add(Tags.Attributes_Secondary_PhysicalDamage, PhysicalDamageDef);
		TagsToCaptureDef.Add(Tags.Attributes_Secondary_MagicPower, MagicPowerDef);
		TagsToCaptureDef.Add(Tags.Attributes_Secondary_ArmorPenetration, ArmorPenetrationDef);
		TagsToCaptureDef.Add(Tags.Attributes_Secondary_CriticalHitChance, CriticalHitChanceDef);
		TagsToCaptureDef.Add(Tags.Attributes_Secondary_CriticalHitDamage, CriticalHitDamageDef);

		TagsToCaptureDef.Add(Tags.Attributes_Secondary_FireAmplification, FireAmplificationDef);
		TagsToCaptureDef.Add(Tags.Attributes_Secondary_FrostAmplification, FrostAmplificationDef);
		TagsToCaptureDef.Add(Tags.Attributes_Secondary_LightningAmplification, LightningAmplificationDef);
		TagsToCaptureDef.Add(Tags.Attributes_Secondary_LightAmplification, LightAmplificationDef);
		TagsToCaptureDef.Add(Tags.Attributes_Secondary_PoisonAmplification, PoisonAmplificationDef);
		TagsToCaptureDef.Add(Tags.Attributes_Secondary_OverallMagicAmplification, OverallMagicAmplificationDef);

		// Populate TagsToCaptureDef Map (Stat Tracking)
		TagsToCaptureDef.Add(Tags.STATSTRACK_DamageTanked, DamageTankedDef);
		TagsToCaptureDef.Add(Tags.STATSTRACK_DamageDealt, DamageDealtDef);
		TagsToCaptureDef.Add(Tags.STATSTRACK_FireDamageDealt, FireDamageDealtDef);
		TagsToCaptureDef.Add(Tags.STATSTRACK_FrostDamageDealt, FrostDamageDealtDef);
		TagsToCaptureDef.Add(Tags.STATSTRACK_LightningDamageDealt, LightningDamageDealtDef);
		TagsToCaptureDef.Add(Tags.STATSTRACK_PhysicalDamageDealt, PhysicalDamageDealtDef);
		TagsToCaptureDef.Add(Tags.STATSTRACK_PoisonDamageDealt, PoisonDamageDealtDef);
		//TagsToCaptureDef.Add(Tags.STATSTRACK_LightDamageDealt, LightDamageDealtDef);
	}
};

// Static helper to get the singleton instance
static const ProjektZDamageStatics& DamageStatics()
{
	static ProjektZDamageStatics DStatics;
	return DStatics;
}

UExecCalc_Damage::UExecCalc_Damage()
{
    // --- Target Attributes to Capture ---
    // These are attributes on the *target* that affect how much damage they take.
    RelevantAttributesToCapture.Add(DamageStatics().ArmorDef);
    RelevantAttributesToCapture.Add(DamageStatics().BlockChanceDef); // Target's chance to block
    RelevantAttributesToCapture.Add(DamageStatics().CriticalHitResistanceDef);

    RelevantAttributesToCapture.Add(DamageStatics().FireResistanceDef);
    RelevantAttributesToCapture.Add(DamageStatics().FrostResistanceDef);
    RelevantAttributesToCapture.Add(DamageStatics().LightningResistanceDef);
    RelevantAttributesToCapture.Add(DamageStatics().LightResistanceDef);    // Don't forget LightResistance if you have it!
    RelevantAttributesToCapture.Add(DamageStatics().PhysicalResistanceDef);
    RelevantAttributesToCapture.Add(DamageStatics().PoisonResistanceDef);

    // --- Source Attributes to Capture ---
    // These are attributes on the *source* that affect how much damage they deal.
    // Replaced WeaponDamage with PhysicalDamage and MagicPower
    RelevantAttributesToCapture.Add(DamageStatics().PhysicalDamageDef);    // For physical abilities
    RelevantAttributesToCapture.Add(DamageStatics().MagicPowerDef);       // For magic abilities
    RelevantAttributesToCapture.Add(DamageStatics().ArmorPenetrationDef);
    RelevantAttributesToCapture.Add(DamageStatics().CriticalHitChanceDef);
    RelevantAttributesToCapture.Add(DamageStatics().CriticalHitDamageDef);

    // Amplification attributes (Source)
    RelevantAttributesToCapture.Add(DamageStatics().FireAmplificationDef);
    RelevantAttributesToCapture.Add(DamageStatics().FrostAmplificationDef);
    RelevantAttributesToCapture.Add(DamageStatics().LightningAmplificationDef);
    RelevantAttributesToCapture.Add(DamageStatics().LightAmplificationDef);
    RelevantAttributesToCapture.Add(DamageStatics().PoisonAmplificationDef);
    RelevantAttributesToCapture.Add(DamageStatics().OverallMagicAmplificationDef);

    // --- Stat Tracking Attributes ---
    // These are attributes used purely for tracking purposes, often added to the target/source's stats.

    // Target Stat Tracking (e.g., how much damage the target *took*)
    RelevantAttributesToCapture.Add(DamageStatics().DamageTankedDef);

    // Source Stat Tracking (e.g., how much damage the source *dealt*)
    RelevantAttributesToCapture.Add(DamageStatics().DamageDealtDef);
    RelevantAttributesToCapture.Add(DamageStatics().FireDamageDealtDef);
    RelevantAttributesToCapture.Add(DamageStatics().FrostDamageDealtDef);
    RelevantAttributesToCapture.Add(DamageStatics().LightningDamageDealtDef);
    RelevantAttributesToCapture.Add(DamageStatics().PhysicalDamageDealtDef);
    RelevantAttributesToCapture.Add(DamageStatics().PoisonDamageDealtDef);
    //RelevantAttributesToCapture.Add(DamageStatics().LightDamageDealtDef); // Make sure this is correctly defined in your DStatics
}

void UExecCalc_Damage::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
    UAbilitySystemComponent* SourceASC = ExecutionParams.GetSourceAbilitySystemComponent();
    UAbilitySystemComponent* TargetASC = ExecutionParams.GetTargetAbilitySystemComponent();

    // --- CRITICAL NULL CHECKS ---
    if (!SourceASC || !TargetASC)
    {
        UE_LOG(LogTemp, Error, TEXT("ExecCalc_Damage: SourceASC or TargetASC is null. Aborting damage calculation."));
        return;
    }

    AActor* SourceActor = SourceASC->GetAvatarActor();
    AActor* TargetActor = TargetASC->GetAvatarActor();

    if (!SourceActor || !TargetActor)
    {
        UE_LOG(LogTemp, Error, TEXT("ExecCalc_Damage: SourceActor or TargetActor is null. Aborting damage calculation."));
        return;
    }

    ICombatInterface* SourceCombatInterface = Cast<ICombatInterface>(SourceActor);
    ICombatInterface* TargetCombatInterface = Cast<ICombatInterface>(TargetActor);

    if (!SourceCombatInterface)
    {
        UE_LOG(LogTemp, Warning, TEXT("ExecCalc_Damage: SourceActor (%s) does not implement ICombatInterface. Some calculations may be inaccurate or default levels will be used."), *SourceActor->GetName());
    }
    if (!TargetCombatInterface)
    {
        UE_LOG(LogTemp, Warning, TEXT("ExecCalc_Damage: TargetActor (%s) does not implement ICombatInterface. Some calculations may be inaccurate or default levels will be used."), *TargetActor->GetName());
    }

    const FGameplayEffectSpec& Spec = ExecutionParams.GetOwningSpec();
    const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
    const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();

    FAggregatorEvaluateParameters EvaulationParameters;
    EvaulationParameters.SourceTags = SourceTags;
    EvaulationParameters.TargetTags = TargetTags;

    FGameplayEffectContextHandle EffectContextHandle = Spec.GetContext();

    // ===================================
    // Capture Common Attributes
    // ===================================
    float CriticalHitChance = 0.f;
    ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().CriticalHitChanceDef, EvaulationParameters, CriticalHitChance);
    CriticalHitChance = FMath::Max(0.f, CriticalHitChance);

    float CriticalHitDamage = 0.f;
    ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().CriticalHitDamageDef, EvaulationParameters, CriticalHitDamage);
    CriticalHitDamage = FMath::Max(0.f, CriticalHitDamage);

    float CriticalHitResistance = 0.f;
    ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().CriticalHitResistanceDef, EvaulationParameters, CriticalHitResistance);
    CriticalHitResistance = FMath::Max(0.f, CriticalHitResistance);

    float BlockChance = 0.f; // This is a target attribute.
    ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().BlockChanceDef, EvaulationParameters, BlockChance);
    BlockChance = FMath::Max(0.f, BlockChance);

    float TargetArmor = 0.f;
    ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().ArmorDef, EvaulationParameters, TargetArmor);
    TargetArmor = FMath::Max(0.f, TargetArmor);

    float SourceArmorPenetration = 0.f;
    ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().ArmorPenetrationDef, EvaulationParameters, SourceArmorPenetration);
    SourceArmorPenetration = FMath::Max(0.f, SourceArmorPenetration);

    // ===================================
    // Get Coefficients
    // ===================================
    const UCharacterClassInfo* CharacterClassInfo = UProjektZAbilitySystemLibrary::GetCharacterClassInfo(SourceActor);
    if (!CharacterClassInfo || !CharacterClassInfo->DamageCalculationCoefficients)
    {
        UE_LOG(LogTemp, Error, TEXT("ExecCalc_Damage: CharacterClassInfo or DamageCalculationCoefficients is null for SourceActor: %s. Cannot calculate damage coefficients."), *SourceActor->GetName());
        // Abort or use sensible defaults if critical
        return;
    }

    const FRealCurve* ArmorPenetrationCurve = CharacterClassInfo->DamageCalculationCoefficients->FindCurve(FName("ArmorPenetration"), FString());
    const FRealCurve* EffectiveArmorCurve = CharacterClassInfo->DamageCalculationCoefficients->FindCurve(FName("EffectiveArmor"), FString());
    const FRealCurve* EffectiveCriticalHitResistanceCurve = CharacterClassInfo->DamageCalculationCoefficients->FindCurve(FName("EffectiveCriticalHitResistance"), FString());

    float ArmorPenetrationCoefficient = 1.0f;
    if (ArmorPenetrationCurve)
    {
        ArmorPenetrationCoefficient = ArmorPenetrationCurve->Eval(SourceCombatInterface ? SourceCombatInterface->GetPlayerLevel() : 1.f);
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("ExecCalc_Damage: ArmorPenetration curve not found. Using default coefficient."));
    }

    float EffectiveArmorCoefficient = 1.0f;
    if (EffectiveArmorCurve)
    {
        EffectiveArmorCoefficient = EffectiveArmorCurve->Eval(TargetCombatInterface ? TargetCombatInterface->GetPlayerLevel() : 1.f);
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("ExecCalc_Damage: EffectiveArmor curve not found. Using default coefficient."));
    }

    float EffectiveCriticalHitResistanceCoefficient = 1.0f;
    if (EffectiveCriticalHitResistanceCurve)
    {
        EffectiveCriticalHitResistanceCoefficient = EffectiveCriticalHitResistanceCurve->Eval(TargetCombatInterface ? TargetCombatInterface->GetPlayerLevel() : 1.f);
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("ExecCalc_Damage: EffectiveCriticalHitResistance curve not found. Using default coefficient."));
    }

    // ===================================
    // Determine Base Damage and Type
    // ===================================
    float BaseDamage = 0.f;
    FGameplayTag DamageTypeTag; // This will hold the specific damage type of the ability.

    const FProjektZGameplayTags& Tags = FProjektZGameplayTags::Get();

    // Iterate through all possible damage types to find which one has a SetByCallerMagnitude
    // Assuming only ONE damage type will be set per ability
    for (const auto& Pair : Tags.ElementTypesToDamageTypes)
    {
        float DamageMagnitude = Spec.GetSetByCallerMagnitude(Pair.Value, 0.f);
        if (DamageMagnitude > KINDA_SMALL_NUMBER) // Check if the magnitude is significant
        {
            BaseDamage = DamageMagnitude;
            DamageTypeTag = Pair.Value; // Assign the found damage type
            UE_LOG(LogTemp, Log, TEXT("ExecCalc_Damage: Ability Base Damage: %f, Type: %s"), BaseDamage, *DamageTypeTag.ToString());
            break; // Found the damage type, exit loop
        }
    }

    // If no specific damage type was set, assume it's Physical and use PhysicalDamage attribute
    if (!DamageTypeTag.IsValid() || BaseDamage <= KINDA_SMALL_NUMBER)
    {
        DamageTypeTag = Tags.Damage_Physical;
        // Fallback to PhysicalDamage attribute if no specific damage type magnitude was provided
        ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().PhysicalDamageDef, EvaulationParameters, BaseDamage);
        BaseDamage = FMath::Max(0.f, BaseDamage); // Ensure non-negative
        UE_LOG(LogTemp, Warning, TEXT("ExecCalc_Damage: No specific damage type magnitude found. Defaulting to Physical Damage: %f"), BaseDamage);
    }

    // ===================================
    // Apply Amplification (Source)
    // ===================================
    float Amplification = 0.f;
    if (DamageTypeTag.MatchesTag(Tags.Damage_Physical))
    {
        // Physical damage is direct, no amplification attribute for it.
        // You might have a specific "PhysicalDamageAmplification" if needed.
    }
    else if (Tags.ElementTypesToDamageTypes.Contains(DamageTypeTag)) // It's an elemental or magic damage type
    {
        // First, check for overall magic amplification if it applies to all elemental types
        float OverallMagicAmp = 0.f;
        ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().OverallMagicAmplificationDef, EvaulationParameters, OverallMagicAmp);
        Amplification += OverallMagicAmp;

        // Then, check for specific elemental amplification
        if (DamageTypeTag.MatchesTag(Tags.Damage_Fire))
        {
            float FireAmp = 0.f;
            ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().FireAmplificationDef, EvaulationParameters, FireAmp);
            Amplification += FireAmp;
        }
        else if (DamageTypeTag.MatchesTag(Tags.Damage_Frost))
        {
            float FrostAmp = 0.f;
            ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().FrostAmplificationDef, EvaulationParameters, FrostAmp);
            Amplification += FrostAmp;
        }
        else if (DamageTypeTag.MatchesTag(Tags.Damage_Lightning))
        {
            float LightningAmp = 0.f;
            ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().LightningAmplificationDef, EvaulationParameters, LightningAmp);
            Amplification += LightningAmp;
        }
        else if (DamageTypeTag.MatchesTag(Tags.Damage_Light))
        {
            float LightAmp = 0.f;
            ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().LightAmplificationDef, EvaulationParameters, LightAmp);
            Amplification += LightAmp;
        }
        else if (DamageTypeTag.MatchesTag(Tags.Damage_Poison))
        {
            float PoisonAmp = 0.f;
            ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().PoisonAmplificationDef, EvaulationParameters, PoisonAmp);
            Amplification += PoisonAmp;
        }

        // Add Source MagicPower to the base damage if it's a magic attack.
        // You might have a system where PhysicalDamage is used for physical attacks and MagicPower for magic attacks.
        // If a magic ability has a base damage, we'll add MagicPower to it.
        float MagicPower = 0.f;
        ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().MagicPowerDef, EvaulationParameters, MagicPower);
        MagicPower = FMath::Max(0.f, MagicPower);
        BaseDamage += MagicPower;
    }

    BaseDamage *= (100.f + Amplification) / 100.f; // Apply total amplification

    // ===================================
    // Apply Resistance (Target)
    // ===================================
    float Resistance = 0.f;
    // Find the corresponding resistance tag for the current damage type
    FGameplayTag ResistanceTag;
    bool bFoundResistanceTag = false;
    for (const auto& Pair : Tags.ElementTypesToResistances)
    {
        if (Tags.ElementTypesToDamageTypes.Contains(Pair.Key) && *Tags.ElementTypesToDamageTypes.Find(Pair.Key) == DamageTypeTag)
        {
            ResistanceTag = Pair.Value;
            bFoundResistanceTag = true;
            break;
        }
    }

    if (bFoundResistanceTag)
    {
        FGameplayEffectAttributeCaptureDefinition* ResistanceCaptureDefPtr = ProjektZDamageStatics().TagsToCaptureDef.Find(ResistanceTag);
        if (ResistanceCaptureDefPtr)
        {
            ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(*ResistanceCaptureDefPtr, EvaulationParameters, Resistance);
            Resistance = FMath::Clamp(Resistance, 0.f, 100.f); // Resistances typically capped at 100%
            BaseDamage *= (100.f - Resistance) / 100.f;
            UE_LOG(LogTemp, Log, TEXT("ExecCalc_Damage: Applied %s Resistance: %f. Damage after resistance: %f"), *ResistanceTag.ToString(), Resistance, BaseDamage);
        }
        else
        {
            UE_LOG(LogTemp, Warning, TEXT("ExecCalc_Damage: Resistance Capture Definition not found for Tag: %s. No resistance applied for this type."), *ResistanceTag.ToString());
        }
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("ExecCalc_Damage: No corresponding resistance tag found for Damage Type: %s. No resistance applied."), *DamageTypeTag.ToString());
    }

    // --- Optional: Reactivity Check (Re-enable if needed, with null checks) ---
    /*
    FGameplayTag ElementTagForDamageType; // You'd need to map DamageTypeTag back to Element_X tag
    for (const auto& Pair : Tags.ElementTypesToDamageTypes)
    {
        if (*Pair.Value == DamageTypeTag)
        {
            ElementTagForDamageType = Pair.Key;
            break;
        }
    }

    if (ElementTagForDamageType.IsValid() && BaseDamage > KINDA_SMALL_NUMBER)
    {
        if (CheckReactivness(TargetActor, TargetASC, ElementTagForDamageType, TargetTags))
        {
            BaseDamage *= 1.3f; // Example reaction bonus
            UE_LOG(LogTemp, Log, TEXT("Reaction damage modifier applied for %s. New damage: %f"), *ElementTagForDamageType.ToString(), BaseDamage);
        }
    }
    */

    // ===================================
    // Armor and Armor Penetration
    // ===================================
    float EffectiveArmor = TargetArmor * (100 - SourceArmorPenetration * ArmorPenetrationCoefficient) / 100;
    EffectiveArmor = FMath::Max(0.f, EffectiveArmor);

    // Apply armor reduction (assuming linear reduction)
    BaseDamage *= (100.f - EffectiveArmor) / 100.f; // This assumes armor also reduces damage by a percentage. Adjust if your formula is different.
    BaseDamage = FMath::Max(0.f, BaseDamage); // Ensure damage does not go negative after armor

    // ===================================
    // Critical Hit and Block Calculations
    // ===================================
    float EffectiveCriticalHitChance = CriticalHitChance - (CriticalHitResistance * EffectiveCriticalHitResistanceCoefficient);
    EffectiveCriticalHitChance = FMath::Max(0.f, EffectiveCriticalHitChance);

    bool bCriticalHit = FMath::RandRange(0, 100) < EffectiveCriticalHitChance;
    UProjektZAbilitySystemLibrary::SetIsCriticalHit(EffectContextHandle, bCriticalHit);

    bool bBlocked = false;
    if (TargetCombatInterface)
    {
        bBlocked = TargetCombatInterface->Execute_GetIsBlocking(TargetActor);
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("ExecCalc_Damage: TargetCombatInterface is null. Cannot determine if target is blocking. Assuming not blocked."));
    }
    UProjektZAbilitySystemLibrary::SetIsBlockedHit(EffectContextHandle, bBlocked);

    // Apply critical hit bonus
    if (bCriticalHit) {
        BaseDamage *= 2.0f; // Double damage on crit
        BaseDamage += CriticalHitDamage; // Add flat crit damage bonus
        UE_LOG(LogTemp, Log, TEXT("Critical Hit! Damage before block: %f"), BaseDamage);
    }

    // Apply block resistance
    if (bBlocked) {
        BaseDamage /= 2.0f; // Halve damage on block
        UE_LOG(LogTemp, Log, TEXT("Blocked Hit! Final Damage: %f"), BaseDamage);
    }

    // Ensure final damage is non-negative
    BaseDamage = FMath::Max(0.f, BaseDamage);

    // ===================================
    // Apply Output Modifiers
    // ===================================
    const FGameplayModifierEvaluatedData IncomingDamageModData(UProjektZAttributeSet::GetIncomingDamageAttribute(), EGameplayModOp::Additive, BaseDamage);
    OutExecutionOutput.AddOutputModifier(IncomingDamageModData);

    // Target Stat Tracking (Damage Tanked)
    const FGameplayModifierEvaluatedData DamageTankedModData(UProjektZAttributeSet::GetDamageTankedAttribute(), EGameplayModOp::Additive, BaseDamage);
    OutExecutionOutput.AddOutputModifier(DamageTankedModData);

    // Source Stat Tracking (Damage Dealt)
    const FGameplayModifierEvaluatedData DamageDealtModData(UProjektZAttributeSet::GetDamageDealtAttribute(), EGameplayModOp::Additive, BaseDamage);
    OutExecutionOutput.AddOutputModifier(DamageDealtModData);

    // Source Stat Tracking (Specific Damage Dealt Type)
    // This requires mapping the `DamageTypeTag` back to the correct stat track attribute.
    // Assuming your stat tracking tags are consistent with damage types, e.g., Tags.STATSTRACK_FireDamageDealt.
    FGameplayAttribute SpecificDamageDealtAttribute;
    if (DamageTypeTag == Tags.Damage_Fire) SpecificDamageDealtAttribute = UProjektZAttributeSet::GetFireDamageDealtAttribute();
    else if (DamageTypeTag == Tags.Damage_Frost) SpecificDamageDealtAttribute = UProjektZAttributeSet::GetFrostDamageDealtAttribute();
    else if (DamageTypeTag == Tags.Damage_Lightning) SpecificDamageDealtAttribute = UProjektZAttributeSet::GetLightningDamageDealtAttribute();
    //else if (DamageTypeTag == Tags.Damage_Light) SpecificDamageDealtAttribute = UProjektZAttributeSet::GetLightDamageDealtAttribute();
    else if (DamageTypeTag == Tags.Damage_Physical) SpecificDamageDealtAttribute = UProjektZAttributeSet::GetPhysicalDamageDealtAttribute();
    else if (DamageTypeTag == Tags.Damage_Poison) SpecificDamageDealtAttribute = UProjektZAttributeSet::GetPoisonDamageDealtAttribute();

    if (SpecificDamageDealtAttribute.IsValid())
    {
        OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(SpecificDamageDealtAttribute, EGameplayModOp::Additive, BaseDamage));
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("ExecCalc_Damage: No specific stat tracking attribute found for Damage Type: %s"), *DamageTypeTag.ToString());
    }

    // Lifesteal (if still desired, keep in mind how it should be applied as discussed)
    // For immediate lifesteal on the Source, you'd apply a modifier to the SourceASC's health,
    // which is not directly part of the OutExecutionOutput for the Target.
    // Example (requires capturing Source's Health in RelevantAttributesToCapture for Source):
    // float LifestealAmount = BaseDamage * LifestealPercent;
    // OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(UProjektZAttributeSet::GetHealthAttribute(), EGameplayModOp::Additive, LifestealAmount, true)); // 'true' for bIs=(Source)
    // This 'bIs' parameter is not directly exposed for FGameplayModifierEvaluatedData constructor.
    // You'd typically need to get the FGameplayAttribute for Health specifically from the SOURCE's attribute set,
    // and then add it as a modifier, or use a separate GE for lifesteal.
}

