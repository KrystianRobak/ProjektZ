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

	//=================================
	//     PRIMARY ATTRIBUTES
	//=================================

	FGameplayTag Attributes_Primary_Strength;
	FGameplayTag Attributes_Primary_Intelligence;
	FGameplayTag Attributes_Primary_Resilience;
	FGameplayTag Attributes_Primary_Vigor;

	//=================================
	//     SECONDARY ATTRIBUTES (ATTRIBUTES CALCULATED WITH PRIMARY ATTRIBUTES)
	//=================================

	FGameplayTag Attributes_Secondary_MaxHealth;
	FGameplayTag Attributes_Secondary_MaxMana;

	FGameplayTag Attributes_Secondary_WeaponDamage;
	FGameplayTag Attributes_Secondary_Armor;
	FGameplayTag Attributes_Secondary_ArmorPenetration;
	FGameplayTag Attributes_Secondary_BlockChance;
	FGameplayTag Attributes_Secondary_CriticalHitChance;
	FGameplayTag Attributes_Secondary_CriticalHitResistance;
	FGameplayTag Attributes_Secondary_CriticalHitDamage;
	FGameplayTag Attributes_Secondary_HealthRegeneration;
	FGameplayTag Attributes_Secondary_ManaRegeneration;
	FGameplayTag Attributes_Secondary_MovementSpeed;


	//=================================
	//     RESISTANCES
	//=================================

	FGameplayTag Attributes_Resistance_Fire;
	FGameplayTag Attributes_Resistance_Frost;
	FGameplayTag Attributes_Resistance_Lightning;
	FGameplayTag Attributes_Resistance_Physical;
	FGameplayTag Attributes_Resistance_Poison;
	FGameplayTag Attributes_Resistance_Light;

	//=================================
	//     RESISTANCES
	//=================================

	FGameplayTag Element_Fire;
	FGameplayTag Element_Frost;
	FGameplayTag Element_Lightning;
	FGameplayTag Element_Light;
	FGameplayTag Element_Poison;

	TMap<FGameplayTag, FGameplayTag> ElementTypesToDamageTypes;
	TMap<FGameplayTag, FGameplayTag> ElementTypesToConditionType;
	TMap<FGameplayTag, FGameplayTag> ElementTypesToResistances;

	//=================================
	//     DAMAGE TYPES
	//=================================

	FGameplayTag Damage;
	FGameplayTag Damage_Fire;
	FGameplayTag Damage_Frost;
	FGameplayTag Damage_Lightning;
	FGameplayTag Damage_Light;
	FGameplayTag Damage_Physical;
	FGameplayTag Damage_Poison;

	//=================================
	//     CONDITIONS
	//=================================

	FGameplayTag Condition_Fire;
	FGameplayTag Condition_Frost;
	FGameplayTag Condition_Poison;
	FGameplayTag Condition_Lightning;
	FGameplayTag Condition_Light;
	FGameplayTag Condition_Wet;
	FGameplayTag Condition_Corroded;
	FGameplayTag Condition_Petrified;
	FGameplayTag Condition_Rooted;

	//=================================
	//     INVENTORY SLOTS
	//=================================

	FGameplayTag Inventory_Head;
	FGameplayTag Inventory_Armor;
	FGameplayTag Inventory_FirstHand;
	FGameplayTag Inventory_SecondHand;
	FGameplayTag Inventory_LeftRing;
	FGameplayTag Inventory_RightRing;
	FGameplayTag Inventory_Necless;

	FGameplayTag Inventory_Empty;

	//=================================
	//     DEBUFFS
	//=================================

	FGameplayTag Debuff_Stun;
	FGameplayTag Debuff_Slow;
	FGameplayTag Debuff_DamageOverTime;
	FGameplayTag Debuff_Silence;
	FGameplayTag Debuff_ManaDrain;

	FGameplayTag Debuff_Stun_Chance;
	FGameplayTag Debuff_Stun_Damage;
	FGameplayTag Debuff_Stun_Duration;
	FGameplayTag Debuff_Stun_Frequency;

	FGameplayTag Debuff_Slow_Chance;
	FGameplayTag Debuff_Slow_Damage;
	FGameplayTag Debuff_Slow_Duration;
	FGameplayTag Debuff_Slow_Frequency;

	FGameplayTag Debuff_DamageOverTime_Chance;
	FGameplayTag Debuff_DamageOverTime_Magnitude;
	FGameplayTag Debuff_DamageOverTime_Duration;
	FGameplayTag Debuff_DamageOverTime_Frequency;

	FGameplayTag Debuff_Silence_Chance;
	FGameplayTag Debuff_Silence_Damage;
	FGameplayTag Debuff_Silence_Duration;
	FGameplayTag Debuff_Silence_Frequency;

	FGameplayTag Debuff_ManaDrain_Chance;
	FGameplayTag Debuff_ManaDrain_Damage;
	FGameplayTag Debuff_ManaDrain_Duration;
	FGameplayTag Debuff_ManaDrain_Frequency;

	//=================================
	//     ABILITIES
	//=================================

	FGameplayTag Ability_ConfirmState;

	FGameplayTag Abilities_Attack;
	FGameplayTag Abilities_Summon;

	FGameplayTag CombatSocket_Weapon;
	FGameplayTag CombatSocket_RightHand;
	FGameplayTag CombatSocket_LeftHand;
	FGameplayTag CombatSocket_Tail;
	FGameplayTag CombatSocket_Ground;

	FGameplayTag Montage_Attack_1;
	FGameplayTag Montage_Attack_2;
	FGameplayTag Montage_Attack_3;
	FGameplayTag Montage_Attack_4;

	FGameplayTag Montage_Attack_Weapon;
	FGameplayTag Montage_Attack_RightHand;
	FGameplayTag Montage_Attack_LeftHand;

	FGameplayTag Abilities_AOE_TEST;
	FGameplayTag Abilities_HEAL_TEST;

	FGameplayTag Abilities_Basic_Attack_1;
	FGameplayTag Abilities_Basic_Attack_2;

	FGameplayTag Abilities_Fire_FireAura;
	FGameplayTag Abilities_Fire_FireBolt;
	FGameplayTag Abilities_Fire_FireRing;
	FGameplayTag Abilities_Fire_FirePillars;

	FGameplayTag Abilities_Frost_Icycle;
	FGameplayTag Abilities_Frost_FrostArea;
	FGameplayTag Abilities_Frost_Blizzard;

	FGameplayTag Abilities_Poison_CloudStrike;
	FGameplayTag Abilities_Poison_Injection;
	FGameplayTag Abilities_Poison_DragonsBreath;

	FGameplayTag Abilities_Light_DivineShot;
	FGameplayTag Abilities_Light_DivineAmnesty;
	FGameplayTag Abilities_Light_DivineStrike;

	FGameplayTag Abilities_Electro_ShockBeam;
	FGameplayTag Abilities_Electro_Eleprison;
	FGameplayTag Abilities_Electro_ElectroStrike;

	FGameplayTag Abilities_Bow_ShotArrow;
	FGameplayTag Abilities_Bow_ChargedShot;

	FGameplayTag Abilities_Sword_ComboAttack_1;
	FGameplayTag Abilities_Sword_ComboAttack_2;
	FGameplayTag Abilities_Sword_ComboAttack_3;
	FGameplayTag Abilities_Sword_ComboAttack_4;
	FGameplayTag Abilities_Sword_GroundSlam;

	FGameplayTag Cooldown_Fire_FireBolt;
	FGameplayTag Cooldown_Frost_FrostBolt;
	FGameplayTag Cooldown_Poison_PoisonBolt;
	FGameplayTag Cooldown_Light_LightBolt;
	FGameplayTag Cooldown_Electro_ElctroBolt;

	FGameplayTag Effects_HitReact;

	//=================================
	//     MOVEMENT
	//=================================

	FGameplayTag Abilities_BasicMovement_Dash;
	FGameplayTag Abilities_BasicMovement_Jump;
	FGameplayTag Abilities_BasicMovement_Sprint;

	//=================================
	//     BOSSES ABILITITES
	//=================================

	FGameplayTag Abilities_Boss_Jungle_LightningStrikes;
	FGameplayTag Abilities_Boss_Jungle_SummonHelpers;
	FGameplayTag Abilities_Boss_Jungle_ToxicClouds;
	FGameplayTag Abilities_Boss_Jungle_PlantStrike;
	FGameplayTag Abilities_Boss_Jungle_Earthquake;
	FGameplayTag Abilities_Boss_Jungle_EarthShatter;



	//=================================
	//     STATS TRACK
	//=================================

	FGameplayTag STATSTRACK_DamageDealt;
	FGameplayTag STATSTRACK_FireDamageDealt;
	FGameplayTag STATSTRACK_FrostDamageDealt;
	FGameplayTag STATSTRACK_LightningDamageDealt;
	FGameplayTag STATSTRACK_PhysicalDamageDealt;
	FGameplayTag STATSTRACK_PoisonDamageDealt;
	FGameplayTag STATSTRACK_LightDamageDealt;
	FGameplayTag STATSTRACK_DamageTanked;
	FGameplayTag STATSTRACK_HealthRecovered;

	//=================================
	//     INPUT
	//=================================
	
	FGameplayTag InputTag_Confirm;
	FGameplayTag InputTag_Cancel;

	FGameplayTag InputTag_Move;
	FGameplayTag InputTag_Look;

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
	FGameplayTag InputTag_SPACE;
	FGameplayTag InputTag_SHIFT;

private:
	static FProjektZGameplayTags GameplayTags;
};