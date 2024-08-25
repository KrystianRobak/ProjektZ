// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjektZGameplayTags.h"
#include "GameplayTagsManager.h"

FProjektZGameplayTags FProjektZGameplayTags::GameplayTags;

void FProjektZGameplayTags::InitializeNativeGameplayTags()
{

	/*
	* Primary Attributes
	*/
	GameplayTags.Attributes_Primary_Strength = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Primary.Strength"), FString("Increases physical damage"));
	GameplayTags.Attributes_Primary_Intelligence = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Primary.Intelligence"), FString("Increases magical damage"));
	GameplayTags.Attributes_Primary_Resilience = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Primary.Resilience"), FString("Increases Armor and Armor Penetration"));
	GameplayTags.Attributes_Primary_Vigor = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Primary.Vigor"), FString("Increases health"));

	/*
	* Secondary Attributes
	*/

	GameplayTags.Attributes_Secondary_Armor =  UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.Armor"), FString("Reduces damage taken, improves block chance"));
	GameplayTags.Attributes_Secondary_ArmorPenetration = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.ArmorPenetration"), FString("Ignores armor of enemy"));
	GameplayTags.Attributes_Secondary_BlockChance = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.BlockChance"), FString("Chance to cut incoming damage in half"));
	GameplayTags.Attributes_Secondary_CriticalHitChance = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.CriticalHitChance"), FString("Chance to double damage plus critical hit bonus"));
	GameplayTags.Attributes_Secondary_CriticalHitDamage = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.CriticalHitDamage"), FString("Bonus damage adden when a critical hit is scored"));
	GameplayTags.Attributes_Secondary_CriticalHitResistance = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.CriticalHitResistance"), FString("Reduces Critical Hit Chance of attacking enemies"));
	GameplayTags.Attributes_Secondary_HealthRegeneration = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.HealthRegeneration"), FString("Amout of Health regenerated every 1 second"));
	GameplayTags.Attributes_Secondary_ManaRegeneration = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.ManaRegeneration"), FString("Amout of Mana regenerated every 1 second"));
	GameplayTags.Attributes_Secondary_MaxHealth = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.MaxHealth"), FString("Maximum amount of Health obtainable"));
	GameplayTags.Attributes_Secondary_MaxMana = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.MaxMana"), FString("Maximum amount of Mana obtainable"));

	/*
	* Resistance Types Tags
	*/

	GameplayTags.Attributes_Resistance_Fire = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Resistance.Fire"), FString("Resistance to fire"));
	GameplayTags.Attributes_Resistance_Frost = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Resistance.Frost"), FString("Resistance to frost"));
	GameplayTags.Attributes_Resistance_Lightning = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Resistance.Lightning"), FString("Resistance to lighting"));
	GameplayTags.Attributes_Resistance_Physical = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Resistance.Physical"), FString("Resistance to physical"));
	GameplayTags.Attributes_Resistance_Poison = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Resistance.Poison"), FString("Resistance to poison"));

	/*
	* Debuffs Tags
	*/

	GameplayTags.Debuff_DamageOverTime = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Debuff.DamageOverTime"), FString("Damage over Time"));
	GameplayTags.Debuff_Silence = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Debuff.Silence"), FString("Can't use spells"));
	GameplayTags.Debuff_Slow = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Debuff.Slow"), FString("Reduced movementspeed"));
	GameplayTags.Debuff_Stun = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Debuff.Stun"), FString("Can't do any actions"));
	GameplayTags.Debuff_ManaDrain = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Debuff.ManaDrain"), FString("Draining mana from target"));


	GameplayTags.Debuff_Chance = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Debuff.Chance"), FString("Chance to apply debuff"));
	GameplayTags.Debuff_Damage = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Debuff.Damage"), FString("Damage for damage over time debuffs"));
	GameplayTags.Debuff_Duration = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Debuff.Duration"), FString("Duration of debuff"));
	GameplayTags.Debuff_Frequency = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Debuff.Frequency"), FString("Frequency of applying debuff to target"));

	/*
	* Input Tags
	*/

	GameplayTags.InputTag_LMB = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.LMB"), FString("Input Tag for Left Mouse Button"));
	GameplayTags.InputTag_RMB = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.RMB"), FString("Input Tag for Right Mouse Button"));
	GameplayTags.InputTag_W = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.W"), FString("Input Tag for W key"));
	GameplayTags.InputTag_S = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.S"), FString("Input Tag for S key"));
	GameplayTags.InputTag_A = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.A"), FString("Input Tag for A key"));
	GameplayTags.InputTag_D = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.D"), FString("Input Tag for D key"));

	GameplayTags.InputTag_F = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.F"), FString("Input Tag for F key"));
	GameplayTags.InputTag_R = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.R"), FString("Input Tag for R key"));
	GameplayTags.InputTag_Q = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.Q"), FString("Input Tag for Q key"));
	GameplayTags.InputTag_E = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.E"), FString("Input Tag for E key"));

	/*
	* Damage Types Tags
	*/

	GameplayTags.Damage = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Damage"), FString("Damage"));
	GameplayTags.Damage_Fire = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Damage.Fire"), FString("Fire Damage Type"));
	GameplayTags.Damage_Frost = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Damage.Frost"), FString("Frost Damage Type"));
	GameplayTags.Damage_Lightning = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Damage.Lightning"), FString("Lightning Damage Type"));
	GameplayTags.Damage_Physical = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Damage.Physical"), FString("Physical Damage Type"));
	GameplayTags.Damage_Poison = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Damage.Poison"), FString("Poison Damage Type"));

	/*
	* Map of Damage to Resistance Tags
	*/

	GameplayTags.DamageTypesToResistances.Add(GameplayTags.Damage_Fire, GameplayTags.Attributes_Resistance_Fire);
	GameplayTags.DamageTypesToResistances.Add(GameplayTags.Damage_Frost, GameplayTags.Attributes_Resistance_Frost);
	GameplayTags.DamageTypesToResistances.Add(GameplayTags.Damage_Lightning, GameplayTags.Attributes_Resistance_Lightning);
	GameplayTags.DamageTypesToResistances.Add(GameplayTags.Damage_Physical , GameplayTags.Attributes_Resistance_Physical);
	GameplayTags.DamageTypesToResistances.Add(GameplayTags.Damage_Poison, GameplayTags.Attributes_Resistance_Poison);

	/*
	* Abilities Tags
	*/
	
	//Fire
	
	GameplayTags.Abilities_Fire_FireBolt = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Abilities.Fire.FireBolt"), FString("FireBolt Ability"));
	
	//Frost
	
	GameplayTags.Abilities_Frost_FrostBolt = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Abilities.Frost.FrostBolt"), FString("FrostBolt Ability"));

	/*
	* Abilities Cooldowns Tags
	*/

	//Fire

	GameplayTags.Cooldown_Fire_FireBolt = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Cooldown.Fire.FireBolt"), FString("FireBolt Ability Cooldown"));

	//Frost

	GameplayTags.Cooldown_Frost_FrostBolt = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Cooldown.Frost.FrostBolt"), FString("FrostBolt Ability Cooldown"));

	GameplayTags.Effects_HitReact = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Effects.HitReact"), FString("Reaction to beeing hit"));
}