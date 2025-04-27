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
	// TARGET

	DECLARE_ATTRIBUTE_CAPTUREDEF(Armor);
	DECLARE_ATTRIBUTE_CAPTUREDEF(ArmorPenetration);
	DECLARE_ATTRIBUTE_CAPTUREDEF(BlockChance);
	DECLARE_ATTRIBUTE_CAPTUREDEF(CriticalHitChance);
	DECLARE_ATTRIBUTE_CAPTUREDEF(CriticalHitDamage);
	DECLARE_ATTRIBUTE_CAPTUREDEF(CriticalHitResistance);
	
	// SOURCE

	DECLARE_ATTRIBUTE_CAPTUREDEF(FireResistance);
	DECLARE_ATTRIBUTE_CAPTUREDEF(FrostResistance);
	DECLARE_ATTRIBUTE_CAPTUREDEF(LightningResistance);
	DECLARE_ATTRIBUTE_CAPTUREDEF(LightResistance);
	DECLARE_ATTRIBUTE_CAPTUREDEF(PhysicalResistance);
	DECLARE_ATTRIBUTE_CAPTUREDEF(PoisonResistance);
	DECLARE_ATTRIBUTE_CAPTUREDEF(WeaponDamage);

	// TARGET STAT TRACK

	DECLARE_ATTRIBUTE_CAPTUREDEF(DamageTanked);

	// SOURCE STAT TRACK

	DECLARE_ATTRIBUTE_CAPTUREDEF(DamageDealt);
	DECLARE_ATTRIBUTE_CAPTUREDEF(FireDamageDealt);
	DECLARE_ATTRIBUTE_CAPTUREDEF(FrostDamageDealt);
	DECLARE_ATTRIBUTE_CAPTUREDEF(LightningDamageDealt);
	DECLARE_ATTRIBUTE_CAPTUREDEF(PhysicalDamageDealt);
	DECLARE_ATTRIBUTE_CAPTUREDEF(PoisonDamageDealt);

	TMap<FGameplayTag, FGameplayEffectAttributeCaptureDefinition> TagsToCaptureDef;

	ProjektZDamageStatics()
	{
		// TARGET

		DEFINE_ATTRIBUTE_CAPTUREDEF(UProjektZAttributeSet, Armor, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UProjektZAttributeSet, BlockChance, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UProjektZAttributeSet, CriticalHitResistance, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UProjektZAttributeSet, FireResistance, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UProjektZAttributeSet, FrostResistance, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UProjektZAttributeSet, LightningResistance, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UProjektZAttributeSet, LightResistance, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UProjektZAttributeSet, PhysicalResistance, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UProjektZAttributeSet, PoisonResistance, Target, false);

		// SOURCE

		DEFINE_ATTRIBUTE_CAPTUREDEF(UProjektZAttributeSet, ArmorPenetration, Source, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UProjektZAttributeSet, CriticalHitChance, Source, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UProjektZAttributeSet, CriticalHitDamage, Source, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UProjektZAttributeSet, WeaponDamage, Source, false);

		// TARGET STAT TRACK

		DEFINE_ATTRIBUTE_CAPTUREDEF(UProjektZAttributeSet, DamageTanked, Target, false);

		// SOURCE STAT TRACK

		DEFINE_ATTRIBUTE_CAPTUREDEF(UProjektZAttributeSet, DamageDealt, Source, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UProjektZAttributeSet, FireDamageDealt, Source, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UProjektZAttributeSet, FrostDamageDealt, Source, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UProjektZAttributeSet, LightningDamageDealt, Source, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UProjektZAttributeSet, PhysicalDamageDealt, Source, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UProjektZAttributeSet, PoisonDamageDealt, Source, false);

		const FProjektZGameplayTags& Tags = FProjektZGameplayTags::Get();

		// TARGET

		TagsToCaptureDef.Add(Tags.Attributes_Secondary_Armor, ArmorDef);
		TagsToCaptureDef.Add(Tags.Attributes_Secondary_BlockChance, BlockChanceDef);
		TagsToCaptureDef.Add(Tags.Attributes_Secondary_CriticalHitResistance, CriticalHitResistanceDef);
		TagsToCaptureDef.Add(Tags.Attributes_Resistance_Fire, FireResistanceDef);
		TagsToCaptureDef.Add(Tags.Attributes_Resistance_Frost, FrostResistanceDef);
		TagsToCaptureDef.Add(Tags.Attributes_Resistance_Lightning, LightningResistanceDef);
		TagsToCaptureDef.Add(Tags.Attributes_Resistance_Light, LightResistanceDef);
		TagsToCaptureDef.Add(Tags.Attributes_Resistance_Physical, PhysicalResistanceDef);
		TagsToCaptureDef.Add(Tags.Attributes_Resistance_Poison, PoisonResistanceDef);

		// SOURCE

		TagsToCaptureDef.Add(Tags.Attributes_Secondary_WeaponDamage, WeaponDamageDef);
		TagsToCaptureDef.Add(Tags.Attributes_Secondary_ArmorPenetration, ArmorPenetrationDef);
		TagsToCaptureDef.Add(Tags.Attributes_Secondary_CriticalHitChance, CriticalHitChanceDef);
		TagsToCaptureDef.Add(Tags.Attributes_Secondary_CriticalHitDamage, CriticalHitDamageDef);

		// TARGET STAT TRACK

		TagsToCaptureDef.Add(Tags.STATSTRACK_DamageTanked, DamageTankedDef);

		// SOURCE STAT TRACK

		TagsToCaptureDef.Add(Tags.STATSTRACK_DamageDealt, DamageDealtDef);
		TagsToCaptureDef.Add(Tags.STATSTRACK_FireDamageDealt, FireDamageDealtDef);
		TagsToCaptureDef.Add(Tags.STATSTRACK_FrostDamageDealt, FrostDamageDealtDef);
		TagsToCaptureDef.Add(Tags.STATSTRACK_LightningDamageDealt, LightningDamageDealtDef);
		TagsToCaptureDef.Add(Tags.STATSTRACK_PhysicalDamageDealt, PhysicalDamageDealtDef);
		TagsToCaptureDef.Add(Tags.STATSTRACK_PoisonDamageDealt, PoisonDamageDealtDef);
	}


};

static const ProjektZDamageStatics DamageStatics()
{
	static ProjektZDamageStatics DStatics;
	return DStatics;
}

UExecCalc_Damage::UExecCalc_Damage()
{
	// Target

	RelevantAttributesToCapture.Add(DamageStatics().ArmorDef);
	RelevantAttributesToCapture.Add(DamageStatics().ArmorPenetrationDef);
	RelevantAttributesToCapture.Add(DamageStatics().CriticalHitResistanceDef);

	RelevantAttributesToCapture.Add(DamageStatics().FireResistanceDef);
	RelevantAttributesToCapture.Add(DamageStatics().FrostResistanceDef);
	RelevantAttributesToCapture.Add(DamageStatics().LightningResistanceDef);	
	RelevantAttributesToCapture.Add(DamageStatics().PhysicalResistanceDef);
	RelevantAttributesToCapture.Add(DamageStatics().PoisonResistanceDef);

	// Source

	RelevantAttributesToCapture.Add(DamageStatics().WeaponDamageDef);
	RelevantAttributesToCapture.Add(DamageStatics().BlockChanceDef);
	RelevantAttributesToCapture.Add(DamageStatics().CriticalHitChanceDef);
	RelevantAttributesToCapture.Add(DamageStatics().CriticalHitDamageDef);


	// SOURCE STAT TRACK

	RelevantAttributesToCapture.Add(DamageStatics().DamageTankedDef);

	// TARGET STAT TRACK

	RelevantAttributesToCapture.Add(DamageStatics().DamageDealtDef);
	RelevantAttributesToCapture.Add(DamageStatics().FireDamageDealtDef);
	RelevantAttributesToCapture.Add(DamageStatics().FrostDamageDealtDef);
	RelevantAttributesToCapture.Add(DamageStatics().LightningDamageDealtDef);
	RelevantAttributesToCapture.Add(DamageStatics().PhysicalDamageDealtDef);
	RelevantAttributesToCapture.Add(DamageStatics().PoisonDamageDealtDef);
}

void UExecCalc_Damage::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	UAbilitySystemComponent* SourceASC = ExecutionParams.GetSourceAbilitySystemComponent();
	UAbilitySystemComponent* TargetASC = ExecutionParams.GetTargetAbilitySystemComponent();

	AActor* SourceActor = SourceASC ? SourceASC->GetAvatarActor() : nullptr;
	AActor* TargetActor = SourceASC ? TargetASC->GetAvatarActor() : nullptr;

	ICombatInterface* SourceCombatInterface = Cast<ICombatInterface>(SourceActor);
	ICombatInterface* TargetCombatInterface = Cast<ICombatInterface>(TargetActor);

	const FGameplayEffectSpec& Spec = ExecutionParams.GetOwningSpec();
	
	const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();

	FAggregatorEvaluateParameters EvaulationParameters;
	EvaulationParameters.SourceTags = SourceTags;
	EvaulationParameters.TargetTags = TargetTags;

	FGameplayEffectContextHandle EffectContextHandle = Spec.GetContext();

	// ==================
	// Capture Needed Attributes
	// ==================
	
	//If Crit Double Damage and add additional damage
	float CriticalHitChance = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().CriticalHitChanceDef, EvaulationParameters, CriticalHitChance);
	CriticalHitChance = FMath::Max<float>(0.f, CriticalHitChance);
	int Chance = FMath::RandRange(0, 100);

	// Additional damage dealt with crit
	float WeaponDamage = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().WeaponDamageDef, EvaulationParameters, WeaponDamage);
	WeaponDamage = FMath::Max<float>(0.f, WeaponDamage);

	// Additional damage dealt with crit
	float CriticalHitDamage = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().CriticalHitDamageDef, EvaulationParameters, CriticalHitDamage);
	CriticalHitDamage = FMath::Max<float>(0.f, CriticalHitDamage);

	// Reduces sources chance to hit critticaly
	float CriticalHitResistance = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().CriticalHitResistanceDef, EvaulationParameters, CriticalHitResistance);
	CriticalHitResistance = FMath::Max<float>(0.f, CriticalHitResistance);

	// If Block, halve the damage
	float BlockChance = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().BlockChanceDef, EvaulationParameters, BlockChance);
	BlockChance = FMath::Max<float>(0.f, BlockChance);
	
	float TargetArmor = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().ArmorDef, EvaulationParameters, TargetArmor);
	TargetArmor = FMath::Max<float>(0.f, TargetArmor);

	// Armor Penetratrion Ignores a percentage of Target's armor
	float SourceArmorPenetration = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().ArmorPenetrationDef, EvaulationParameters, SourceArmorPenetration);
	SourceArmorPenetration = FMath::Max<float>(0.f, SourceArmorPenetration);
	
	// ==================
	// Get Coefficients
	// ==================

	const UCharacterClassInfo* CharacterClassInfo = UProjektZAbilitySystemLibrary::GetCharacterClassInfo(SourceActor);
	const FRealCurve* ArmorPenetrationCurve = CharacterClassInfo->DamageCalculationCoefficients->FindCurve(FName("ArmorPenetration"), FString());
	const FRealCurve* EffectiveArmorCurve = CharacterClassInfo->DamageCalculationCoefficients->FindCurve(FName("EffectiveArmor"), FString());
	const FRealCurve* EffectiveCriticalHitResistanceCurve = CharacterClassInfo->DamageCalculationCoefficients->FindCurve(FName("EffectiveCriticalHitResistance"), FString());

	const float ArmorPenetrationCoefficient = ArmorPenetrationCurve->Eval(SourceCombatInterface->GetPlayerLevel());
	const float EffectiveArmorCoefficient = EffectiveArmorCurve->Eval(TargetCombatInterface->GetPlayerLevel());
	const float EffectiveCriticalHitResistanceCoefficient = EffectiveCriticalHitResistanceCurve->Eval(TargetCombatInterface->GetPlayerLevel());


	// ==================
	// Damage Calulations
	// ==================
	
	// Get Damage Set By Caller Magnitude
	float Damage = 0.f;
	FString TheFloatStr = FString::SanitizeFloat(Damage);

	Damage += WeaponDamage;
	TheFloatStr = FString::SanitizeFloat(Damage);

	for (const TTuple<FGameplayTag, FGameplayTag>& Pair : FProjektZGameplayTags::Get().ElementTypesToResistances)
	{
		FGameplayTag DamageTypeTag = *FProjektZGameplayTags::Get().ElementTypesToDamageTypes.Find(Pair.Key);
		FGameplayTag ConditionTypeTag = *FProjektZGameplayTags::Get().ElementTypesToConditionType.Find(Pair.Key);
		FGameplayTag ResistanceTag = Pair.Value;

		checkf(ProjektZDamageStatics().TagsToCaptureDef.Contains(ResistanceTag), TEXT("TagsToCaptureDef doesn't contain Tag: [%s] in ExecCalc_Damage"), *ResistanceTag.ToString());

		FGameplayEffectAttributeCaptureDefinition CaptureDef = ProjektZDamageStatics().TagsToCaptureDef[ResistanceTag];

		float DamageTypeValue = Spec.GetSetByCallerMagnitude(DamageTypeTag, 0.f);

		float Resistance = 0.f;
		ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(CaptureDef, EvaulationParameters, Resistance);
		Resistance = FMath::Clamp(Resistance, 0.f, 100.f);

		if (DamageTypeValue != 0)
		{
			if (CheckReactivness(TargetActor, TargetASC, Pair.Key, TargetTags))
			{
				DamageTypeValue *= 1.3;
				GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Yellow, FString::Printf(TEXT("Reaction damage modifier applied")));
			}
		}

		DamageTypeValue *= (100.f - Resistance) / 100.f;
		//GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Yellow, FString::Printf(TEXT("Damage is: %f | Type of damage is %s"), DamageTypeValue, *DamageTypeTag.ToString()));
		Damage += DamageTypeValue;
	}

	//Calculate critical hit chance
	float EffectiveCriticalHitChance = CriticalHitChance - (CriticalHitResistance * EffectiveCriticalHitResistanceCoefficient);
	EffectiveCriticalHitChance = FMath::Max<float>(0.f, EffectiveCriticalHitChance);

	//Calculate armor vs armor penetration
	float EffectiveArmor = TargetArmor * (100 - SourceArmorPenetration * ArmorPenetrationCoefficient) / 100;
	EffectiveArmor = FMath::Max<float>(0.f, EffectiveArmor);
	
	// Check whether hit is critical
	bool bCriticalHit = FMath::RandRange(0, 100) < EffectiveCriticalHitChance;

	// Check whether hit is blocked
	//bool bBlocked = FMath::RandRange(0, 100) < BlockChance;
	bool bBlocked = TargetCombatInterface->Execute_GetIsBlocking(TargetActor);

	UProjektZAbilitySystemLibrary::SetIsCriticalHit(EffectContextHandle, bCriticalHit);
	UProjektZAbilitySystemLibrary::SetIsBlockedHit(EffectContextHandle, bBlocked);

	//Apply critical hit bonus to damage
	if (bCriticalHit) {
		Damage = Damage * 2;
		Damage += CriticalHitDamage;
		//GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Yellow, TEXT("Crit!"));
	}

	//Apply block resistance to damage
	if (bBlocked) {
		Damage = Damage / 2;
		//GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Yellow, TEXT("Zablokowałem!"));
	}

	//Calculate final damage
	Damage *= (100 - EffectiveArmor * EffectiveArmorCoefficient) / 100;



	const FGameplayModifierEvaluatedData EvaulatedData(UProjektZAttributeSet::GetIncomingDamageAttribute(), EGameplayModOp::Additive, Damage);
	OutExecutionOutput.AddOutputModifier(EvaulatedData);

	// Target stat tracking

	const FGameplayModifierEvaluatedData DamageTakenEvaulatedData(UProjektZAttributeSet::GetDamageTankedAttribute(), EGameplayModOp::Additive, Damage);
	OutExecutionOutput.AddOutputModifier(DamageTakenEvaulatedData);

	// Source stat tracking

	UGameplayEffect* GELifesteal = NewObject<UGameplayEffect>(GetTransientPackage(), FName(TEXT("DamageDealt")));
	GELifesteal->DurationPolicy = EGameplayEffectDurationType::Instant;

	int32 Idx = GELifesteal->Modifiers.Num();
	GELifesteal->Modifiers.SetNum(Idx + 1);
	FGameplayModifierInfo& Info = GELifesteal->Modifiers[Idx];
	Info.ModifierMagnitude = FScalableFloat(Damage);
	Info.ModifierOp = EGameplayModOp::Additive;
	Info.Attribute = UProjektZAttributeSet::GetDamageDealtAttribute();
	SourceASC->ApplyGameplayEffectToSelf(GELifesteal, 1.0f, SourceASC->MakeEffectContext());
}

