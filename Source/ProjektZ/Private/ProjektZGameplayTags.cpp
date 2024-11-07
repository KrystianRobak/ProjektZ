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

	GameplayTags.Attributes_Secondary_WeaponDamage = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.WeaponDamage"), FString("Additional damage weapon gives"));
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
	GameplayTags.Attributes_Secondary_MovementSpeed = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.MovementSpeed"), FString("MovementSpeed of character"));

	/*
	* Resistance Types Tags
	*/

	GameplayTags.Attributes_Resistance_Fire = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Resistance.Fire"), FString("Resistance to fire"));
	GameplayTags.Attributes_Resistance_Frost = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Resistance.Frost"), FString("Resistance to frost"));
	GameplayTags.Attributes_Resistance_Lightning = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Resistance.Lightning"), FString("Resistance to lighting"));
	GameplayTags.Attributes_Resistance_Physical = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Resistance.Physical"), FString("Resistance to physical"));
	GameplayTags.Attributes_Resistance_Poison = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Resistance.Poison"), FString("Resistance to poison"));
	GameplayTags.Attributes_Resistance_Light = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Resistance.Light"), FString("Resistance to light"));
	/*
	* Debuffs Tags
	*/

	GameplayTags.Debuff_DamageOverTime = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Debuff.DamageOverTime"), FString("Damage over Time"));
	GameplayTags.Debuff_Silence = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Debuff.Silence"), FString("Can't use spells"));
	GameplayTags.Debuff_Slow = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Debuff.Slow"), FString("Reduced movementspeed"));
	GameplayTags.Debuff_Stun = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Debuff.Stun"), FString("Can't do any actions"));
	GameplayTags.Debuff_ManaDrain = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Debuff.ManaDrain"), FString("Draining mana from target"));


	GameplayTags.Debuff_Slow_Chance = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Debuff.Slow.Chance"), FString("Chance to apply debuff"));
	GameplayTags.Debuff_Slow_Damage = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Debuff.Slow.Damage"), FString("Damage for damage over time debuffs"));
	GameplayTags.Debuff_Slow_Duration = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Debuff.Slow.Duration"), FString("Duration of debuff"));
	GameplayTags.Debuff_Slow_Frequency = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Debuff.Slow.Frequency"), FString("Frequency of applying debuff to target"));

	GameplayTags.Debuff_DamageOverTime_Magnitude = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Debuff.DamageOverTime.Magnitude"), FString("Damage for damage over time debuffs"));

	/*
	* Input Tags
	*/

	GameplayTags.InputTag_Confirm = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.Confirm"), FString("Input Tag for confirming abilities"));
	GameplayTags.InputTag_Cancel = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.Cancel"), FString("Input Tag for cancleing abilities"));
	GameplayTags.InputTag_Move = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.Move"), FString("Input Tag for moving"));
	GameplayTags.InputTag_Look = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.Look"), FString("Input Tag for looking"));

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
	GameplayTags.InputTag_SPACE = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.SPACE"), FString("Input Tag for SPACE key"));

	/*
	* Elements Tags
	*/

	GameplayTags.Element_Fire = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Element.Fire"), FString("Element Fire"));
	GameplayTags.Element_Frost = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Element.Frost"), FString("Element Frost"));
	GameplayTags.Element_Poison = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Element.Poison"), FString("Element Poison"));
	GameplayTags.Element_Lightning = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Element.Electro"), FString("Element Electro"));
	GameplayTags.Element_Light = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Element.Light"), FString("Element Light"));

	/*
	* Condition Tags
	*/

	GameplayTags.Condition_Fire = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Condition.Fire"), FString("Condition"));
	GameplayTags.Condition_Frost = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Condition.Frost"), FString("Condition"));
	GameplayTags.Condition_Poison = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Condition.Poison"), FString("Condition"));
	GameplayTags.Condition_Lightning = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Condition.Electro"), FString("Condition"));
	GameplayTags.Condition_Light = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Condition.Light"), FString("Condition"));

	/*
	* Damage Types Tags
	*/

	GameplayTags.Damage = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Damage"), FString("Damage"));
	GameplayTags.Damage_Fire = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Damage.Fire"), FString("Fire Damage Type"));
	GameplayTags.Damage_Frost = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Damage.Frost"), FString("Frost Damage Type"));
	GameplayTags.Damage_Lightning = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Damage.Lightning"), FString("Lightning Damage Type"));
	GameplayTags.Damage_Physical = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Damage.Physical"), FString("Physical Damage Type"));
	GameplayTags.Damage_Poison = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Damage.Poison"), FString("Poison Damage Type"));
	GameplayTags.Damage_Light = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Damage.Light"), FString("Light Damage Type"));

	/*
	* Map of Damage to Resistance Tags
	*/

	GameplayTags.ElementTypesToResistances.Add(GameplayTags.Element_Fire, GameplayTags.Attributes_Resistance_Fire);
	GameplayTags.ElementTypesToResistances.Add(GameplayTags.Element_Frost, GameplayTags.Attributes_Resistance_Frost);
	GameplayTags.ElementTypesToResistances.Add(GameplayTags.Element_Light, GameplayTags.Attributes_Resistance_Light);
	GameplayTags.ElementTypesToResistances.Add(GameplayTags.Element_Lightning, GameplayTags.Attributes_Resistance_Lightning);
	GameplayTags.ElementTypesToResistances.Add(GameplayTags.Element_Poison, GameplayTags.Attributes_Resistance_Poison);

	/*
	* Map of Damage to Resistance Tags
	*/

	GameplayTags.ElementTypesToDamageTypes.Add(GameplayTags.Element_Fire, GameplayTags.Damage_Fire);
	GameplayTags.ElementTypesToDamageTypes.Add(GameplayTags.Element_Frost, GameplayTags.Damage_Frost);
	GameplayTags.ElementTypesToDamageTypes.Add(GameplayTags.Element_Light, GameplayTags.Damage_Light);
	GameplayTags.ElementTypesToDamageTypes.Add(GameplayTags.Element_Lightning, GameplayTags.Damage_Lightning);
	GameplayTags.ElementTypesToDamageTypes.Add(GameplayTags.Element_Poison, GameplayTags.Damage_Poison);

	GameplayTags.ElementTypesToConditionType.Add(GameplayTags.Element_Fire, GameplayTags.Condition_Fire);
	GameplayTags.ElementTypesToConditionType.Add(GameplayTags.Element_Frost, GameplayTags.Condition_Frost);
	GameplayTags.ElementTypesToConditionType.Add(GameplayTags.Element_Light, GameplayTags.Condition_Light);
	GameplayTags.ElementTypesToConditionType.Add(GameplayTags.Element_Lightning, GameplayTags.Condition_Lightning);
	GameplayTags.ElementTypesToConditionType.Add(GameplayTags.Element_Poison, GameplayTags.Condition_Poison);

	/*
	* Abilities Tags
	*/

	GameplayTags.Ability_ConfirmState = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Ability.ConfirmState"), FString("Run when ability starts so no other ability is beeing cast"));
	
	//Fire
	


	/*
	* Abilities Cooldowns Tags
	*/

	GameplayTags.Abilities_Basic_Attack_1 = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Abilities.Basic.Attack_1"), FString("FireBolt Ability"));
	GameplayTags.Abilities_Basic_Attack_2 = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Abilities.Basic.Attack_2"), FString("FireBolt Ability"));

	GameplayTags.Abilities_Fire_FireBolt = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Abilities.Fire.FireBolt"), FString("FireBolt Ability"));
	GameplayTags.Abilities_Frost_FrostBolt = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Abilities.Frost.FrostBolt"), FString("FrostBolt Ability"));
	GameplayTags.Abilities_Poison_PoisonBolt = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Abilities.Poison.PoisonBolt"), FString("FrostBolt Ability"));
	GameplayTags.Abilities_Light_LightBolt = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Abilities.Light.LightBolt"), FString("FrostBolt Ability"));
	GameplayTags.Abilities_Electro_ElctroBolt = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Abilities.Electro.ElctroBolt"), FString("FrostBolt Ability"));;

	GameplayTags.Cooldown_Fire_FireBolt = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Cooldown.Fire.FireBolt"), FString("FireBolt Ability Cooldown"));
	GameplayTags.Cooldown_Frost_FrostBolt = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Cooldown.Frost.FrostBolt"), FString("FireBolt Ability Cooldown"));
	GameplayTags.Cooldown_Poison_PoisonBolt = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Cooldown.Poison.PoisonBolt"), FString("FireBolt Ability Cooldown"));
	GameplayTags.Cooldown_Light_LightBolt = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Cooldown.Light.LightBolt"), FString("FireBolt Ability Cooldown"));
	GameplayTags.Cooldown_Electro_ElctroBolt = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Cooldown.Electro.ElctroBolt"), FString("FireBolt Ability Cooldown"));

	//Fire

	GameplayTags.Cooldown_Fire_FireBolt = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Cooldown.Fire.FireBolt"), FString("FireBolt Ability Cooldown"));

	//Frost

	GameplayTags.Cooldown_Frost_FrostBolt = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Cooldown.Frost.FrostBolt"), FString("FrostBolt Ability Cooldown"));

	GameplayTags.Effects_HitReact = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Effects.HitReact"), FString("Reaction to beeing hit"));

	/*
	* Abilities 
	*/

	GameplayTags.Abilities_AOE_TEST = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Abilities.AOE.Test"), FString("Attack Ability Tag"));
	GameplayTags.Abilities_HEAL_TEST = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Abilities.Heal.Test"), FString("Attack Ability Tag"));;
	//Frost

	GameplayTags.Abilities_Attack = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Abilities.Attack"), FString("Attack Ability Tag"));

	/*
	* Montage
	*/


	GameplayTags.Montage_Attack_Weapon = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Montage.Attack.Weapon"), FString("Weapon"));
	GameplayTags.Montage_Attack_RightHand = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Montage.Attack.RightHand"), FString("Right Hand"));
	GameplayTags.Montage_Attack_LeftHand = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Montage.Attack.LeftHand"), FString("Left Hand"));

	/*
	* Stat Track
	*/

	GameplayTags.STATSTRACK_DamageDealt = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("STATSTRACK.DamageDealt"), FString("Stat tracking DamageDealt"));
	GameplayTags.STATSTRACK_FireDamageDealt = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("STATSTRACK.FireDamageDealt"), FString("Stat tracking FireDamageDealt"));
	GameplayTags.STATSTRACK_FrostDamageDealt = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("STATSTRACK.FrostDamageDealt"), FString("Stat tracking FrostDamageDealt"));
	GameplayTags.STATSTRACK_LightningDamageDealt = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("STATSTRACK.LightningDamageDealt"), FString("Stat tracking LightningDamageDealt"));
	GameplayTags.STATSTRACK_PhysicalDamageDealt = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("STATSTRACK.PhysicalDamageDealt"), FString("Stat tracking PhysicalDamageDealt"));
	GameplayTags.STATSTRACK_PoisonDamageDealt = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("STATSTRACK.PoisonDamageDealt"), FString("Stat tracking PoisonDamageDealt"));
	GameplayTags.STATSTRACK_DamageTanked = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("STATSTRACK.DamageTanked"), FString("Stat tracking DamageTanked"));
	GameplayTags.STATSTRACK_HealthRecovered = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("STATSTRACK.HealthRecovered"), FString("Stat tracking HealthRecovered"));
}