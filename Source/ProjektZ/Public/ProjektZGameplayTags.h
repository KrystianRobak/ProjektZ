// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include "GameplayTagContainer.h"

/**
 * ProjektZGameplayTags
 * 
 * Singleton containing native Gameplay Tags
 */

struct FProjektZGameplayTags {
public:
	static const FProjektZGameplayTags& Get() { return GameplayTags;}
	static void InitializeNativeGameplayTags();

	FGameplayTag Attributes_Primary_Strength;
	FGameplayTag Attributes_Primary_Intelligence;
	FGameplayTag Attributes_Primary_Resilience;
	FGameplayTag Attributes_Primary_Vigor;

	FGameplayTag Attributes_Secondary_MaxHealth;
	FGameplayTag Attributes_Secondary_MaxMana;

	FGameplayTag Attributes_Secondary_Armor;
	FGameplayTag Attributes_Secondary_ArmorPenetration;
	FGameplayTag Attributes_Secondary_BlockChance;
	FGameplayTag Attributes_Secondary_CriticalHitChance;
	FGameplayTag Attributes_Secondary_CriticalHitResistance;
	FGameplayTag Attributes_Secondary_CriticalHitDamage;
	FGameplayTag Attributes_Secondary_HealthRegeneration;
	FGameplayTag Attributes_Secondary_ManaRegeneration;

	FGameplayTag InputTag_LMB;
	FGameplayTag InputTag_RMB;
	FGameplayTag InputTag_W;
	FGameplayTag InputTag_S;
	FGameplayTag InputTag_A;
	FGameplayTag InputTag_D;
	FGameplayTag InputTag_F;
	FGameplayTag InputTag_R;
	FGameplayTag InputTag_Q;
	FGameplayTag InputTag_E;

	FGameplayTag Attributes_Resistance_Fire;
	FGameplayTag Attributes_Resistance_Frost;
	FGameplayTag Attributes_Resistance_Lightning;
	FGameplayTag Attributes_Resistance_Physical;
	FGameplayTag Attributes_Resistance_Poison;

	FGameplayTag Damage;
	FGameplayTag Damage_Fire;
	FGameplayTag Damage_Frost;
	FGameplayTag Damage_Lightning;
	FGameplayTag Damage_Physical;
	FGameplayTag Damage_Poison;

	FGameplayTag Debuff_Stun;
	FGameplayTag Debuff_Slow;
	FGameplayTag Debuff_DamageOverTime;
	FGameplayTag Debuff_Silence;
	FGameplayTag Debuff_ManaDrain;

	FGameplayTag Debuff_Chance;
	FGameplayTag Debuff_Damage;
	FGameplayTag Debuff_Duration;
	FGameplayTag Debuff_Frequency;


	FGameplayTag Abilities_Fire_FireBolt;
	FGameplayTag Abilities_Frost_FrostBolt;

	FGameplayTag Cooldown_Fire_FireBolt;
	FGameplayTag Cooldown_Frost_FrostBolt;

	TMap<FGameplayTag, FGameplayTag> DamageTypesToResistances;

	FGameplayTag Effects_HitReact;


private:
	static FProjektZGameplayTags GameplayTags;
};