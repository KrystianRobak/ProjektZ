// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/ExecCalc/ExecCalc_Effect.h"

#include "ProjektZGameplayTags.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystem/ProjektZAttributeSet.h"
#include <AbilitySystem/Data/CharacterClassInfo.h>
#include <AbilitySystem/ProjektZAbilitySystemLibrary.h>
#include <Interaction/CombatInterface.h>
#include "ProjektZAbilityTypes.h"

//struct ProjektZDamageStatics
//{
//	DECLARE_ATTRIBUTE_CAPTUREDEF(Armor);
//	DECLARE_ATTRIBUTE_CAPTUREDEF(ArmorPenetration);
//	DECLARE_ATTRIBUTE_CAPTUREDEF(BlockChance);
//	DECLARE_ATTRIBUTE_CAPTUREDEF(CriticalHitChance);
//	DECLARE_ATTRIBUTE_CAPTUREDEF(CriticalHitDamage);
//	DECLARE_ATTRIBUTE_CAPTUREDEF(CriticalHitResistance);
//
//	DECLARE_ATTRIBUTE_CAPTUREDEF(FireResistance);
//	DECLARE_ATTRIBUTE_CAPTUREDEF(FrostResistance);
//	DECLARE_ATTRIBUTE_CAPTUREDEF(LightningResistance);
//	DECLARE_ATTRIBUTE_CAPTUREDEF(PhysicalResistance);
//	DECLARE_ATTRIBUTE_CAPTUREDEF(PoisonResistance);
//
//	TMap<FGameplayTag, FGameplayEffectAttributeCaptureDefinition> TagsToCaptureDef;
//
//	ProjektZDamageStatics()
//	{
//		DEFINE_ATTRIBUTE_CAPTUREDEF(UProjektZAttributeSet, Armor, Target, false);
//		DEFINE_ATTRIBUTE_CAPTUREDEF(UProjektZAttributeSet, BlockChance, Target, false);
//		DEFINE_ATTRIBUTE_CAPTUREDEF(UProjektZAttributeSet, CriticalHitResistance, Target, false);
//		DEFINE_ATTRIBUTE_CAPTUREDEF(UProjektZAttributeSet, FireResistance, Target, false);
//		DEFINE_ATTRIBUTE_CAPTUREDEF(UProjektZAttributeSet, FrostResistance, Target, false);
//		DEFINE_ATTRIBUTE_CAPTUREDEF(UProjektZAttributeSet, LightningResistance, Target, false);
//		DEFINE_ATTRIBUTE_CAPTUREDEF(UProjektZAttributeSet, PhysicalResistance, Target, false);
//		DEFINE_ATTRIBUTE_CAPTUREDEF(UProjektZAttributeSet, PoisonResistance, Target, false);
//
//		DEFINE_ATTRIBUTE_CAPTUREDEF(UProjektZAttributeSet, ArmorPenetration, Source, false);
//		DEFINE_ATTRIBUTE_CAPTUREDEF(UProjektZAttributeSet, CriticalHitChance, Source, false);
//		DEFINE_ATTRIBUTE_CAPTUREDEF(UProjektZAttributeSet, CriticalHitDamage, Source, false);
//
//		const FProjektZGameplayTags& Tags = FProjektZGameplayTags::Get();
//
//		TagsToCaptureDef.Add(Tags.Attributes_Secondary_Armor, ArmorDef);
//		TagsToCaptureDef.Add(Tags.Attributes_Secondary_BlockChance, BlockChanceDef);
//		TagsToCaptureDef.Add(Tags.Attributes_Secondary_CriticalHitResistance, CriticalHitResistanceDef);
//		TagsToCaptureDef.Add(Tags.Attributes_Resistance_Fire, FireResistanceDef);
//		TagsToCaptureDef.Add(Tags.Attributes_Resistance_Frost, FrostResistanceDef);
//		TagsToCaptureDef.Add(Tags.Attributes_Resistance_Lightning, LightningResistanceDef);
//		TagsToCaptureDef.Add(Tags.Attributes_Resistance_Physical, PhysicalResistanceDef);
//		TagsToCaptureDef.Add(Tags.Attributes_Resistance_Poison, PoisonResistanceDef);
//
//		TagsToCaptureDef.Add(Tags.Attributes_Secondary_ArmorPenetration, ArmorPenetrationDef);
//		TagsToCaptureDef.Add(Tags.Attributes_Secondary_CriticalHitChance, CriticalHitChanceDef);
//		TagsToCaptureDef.Add(Tags.Attributes_Secondary_CriticalHitDamage, CriticalHitDamageDef);
//	}
//};
//
//static const ProjektZDamageStatics DamageStatics()
//{
//	static ProjektZDamageStatics DStatics;
//	return DStatics;
//}
//
//UExecCalc_Effect::UExecCalc_Effect()
//{
//	 Target
//
//	RelevantAttributesToCapture.Add(DamageStatics().ArmorDef);
//	RelevantAttributesToCapture.Add(DamageStatics().ArmorPenetrationDef);
//	RelevantAttributesToCapture.Add(DamageStatics().CriticalHitResistanceDef);
//
//	RelevantAttributesToCapture.Add(DamageStatics().FireResistanceDef);
//	RelevantAttributesToCapture.Add(DamageStatics().FrostResistanceDef);
//	RelevantAttributesToCapture.Add(DamageStatics().LightningResistanceDef);
//	RelevantAttributesToCapture.Add(DamageStatics().PhysicalResistanceDef);
//	RelevantAttributesToCapture.Add(DamageStatics().PoisonResistanceDef);
//
//	 Source
//
//	RelevantAttributesToCapture.Add(DamageStatics().BlockChanceDef);
//	RelevantAttributesToCapture.Add(DamageStatics().CriticalHitChanceDef);
//	RelevantAttributesToCapture.Add(DamageStatics().CriticalHitDamageDef);
//}
//
//void UExecCalc_Effect::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
//{
//	const UAbilitySystemComponent* SourceASC = ExecutionParams.GetSourceAbilitySystemComponent();
//	const UAbilitySystemComponent* TargetASC = ExecutionParams.GetTargetAbilitySystemComponent();
//
//	AActor* SourceActor = SourceASC ? SourceASC->GetAvatarActor() : nullptr;
//	AActor* TargetActor = SourceASC ? TargetASC->GetAvatarActor() : nullptr;
//
//	ICombatInterface* SourceCombatInterface = Cast<ICombatInterface>(SourceActor);
//	ICombatInterface* TargetCombatInterface = Cast<ICombatInterface>(TargetActor);
//
//	const FGameplayEffectSpec& Spec = ExecutionParams.GetOwningSpec();
//
//	const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
//	const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();
//
//	FAggregatorEvaluateParameters EvaulationParameters;
//	EvaulationParameters.SourceTags = SourceTags;
//	EvaulationParameters.TargetTags = TargetTags;
//
//	FGameplayEffectContextHandle EffectContextHandle = Spec.GetContext();
//
//
//	float Damage = Spec.GetSetByCallerMagnitude(FProjektZGameplayTags::Get().Debuff_DamageOverTime_Magnitude, 0.f);
//	GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Yellow, TEXT("NAPIERDALAMY DAMAGE OVER TIME AUUUUU"));
//
//	const FGameplayModifierEvaluatedData EvaulatedData(UProjektZAttributeSet::GetIncomingDamageAttribute(), EGameplayModOp::Additive, Damage);
//	OutExecutionOutput.AddOutputModifier(EvaulatedData);
//}
