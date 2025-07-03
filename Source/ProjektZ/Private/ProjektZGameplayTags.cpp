// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjektZGameplayTags.h"
#include "GameplayTagsManager.h"

FProjektZGameplayTags FProjektZGameplayTags::GameplayTags;

void FProjektZGameplayTags::InitializeNativeGameplayTags()
{
	/*
	* Secondary Resources Attributes
	*/

	GameplayTags.Attributes_Secondary_MaxHealth = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Secondary.MaxHealth"),
		FString("Maximum amount of Health obtainable.")
	);

	GameplayTags.Attributes_Secondary_HealthRegeneration = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Secondary.HealthRegeneration"),
		FString("Amount of Health regenerated per second.")
	);

	GameplayTags.Attributes_Secondary_MaxMana = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Secondary.MaxMana"),
		FString("Maximum amount of Mana obtainable.")
	);

	GameplayTags.Attributes_Secondary_ManaRegeneration = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Secondary.ManaRegeneration"),
		FString("Amount of Mana regenerated per second.")
	);

	GameplayTags.Attributes_Secondary_MaxStamina = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Secondary.MaxStamina"),
		FString("Maximum amount of Stamina obtainable.")
	);

	GameplayTags.Attributes_Secondary_StaminaRegeneration = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Secondary.StaminaRegeneration"),
		FString("Amount of Stamina regenerated per second.")
	);

	/*
	* Secondary Combat Attributes
	*/

	GameplayTags.Attributes_Secondary_PhysicalDamage = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Secondary.PhysicalDamage"),
		FString("Bonus physical damage added to weapon and melee attacks.")
	);

	GameplayTags.Attributes_Secondary_WeaponDamage = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Secondary.WeaponDamage"),
		FString("Base damage of the equipped weapon, used for scaling physical attacks.")
	);

	GameplayTags.Attributes_Secondary_MagicPower = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Secondary.MagicPower"),
		FString("Base stat used for scaling all spell damage.")
	);

	GameplayTags.Attributes_Secondary_SpellCriticalChance = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Secondary.SpellCriticalChance"),
		FString("Chance for spells to deal critical hits.")
	);

	GameplayTags.Attributes_Secondary_SpellCriticalDamage = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Secondary.SpellCriticalDamage"),
		FString("Bonus damage dealt by spells on critical hits.")
	);

	GameplayTags.Attributes_Secondary_CooldownReduction = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Secondary.CooldownReduction"),
		FString("Percentage reduction to all skill cooldowns.")
	);

	GameplayTags.Attributes_Secondary_AttackSpeed = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Secondary.AttackSpeed"),
		FString("Increases speed of physical and ranged attacks.")
	);

	GameplayTags.Attributes_Secondary_MovementSpeed = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Secondary.MovementSpeed"),
		FString("Controls how fast the character moves.")
	);

	/*
	* Secondary defensive Attributes
	*/

	GameplayTags.Attributes_Secondary_Armor = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Secondary.Armor"),
		FString("Reduces physical damage taken; improves block effectiveness.")
	);

	GameplayTags.Attributes_Secondary_ArmorPenetration = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Secondary.ArmorPenetration"),
		FString("Ignores a portion of enemy armor.")
	);

	GameplayTags.Attributes_Secondary_BlockChance = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Secondary.BlockChance"),
		FString("Chance to block and reduce incoming damage.")
	);

	GameplayTags.Attributes_Secondary_CriticalHitChance = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Secondary.CriticalHitChance"),
		FString("Chance for attacks to deal critical damage.")
	);

	GameplayTags.Attributes_Secondary_CriticalHitDamage = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Secondary.CriticalHitDamage"),
		FString("Bonus damage dealt on critical hits.")
	);

	GameplayTags.Attributes_Secondary_CriticalHitResistance = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Secondary.CriticalHitResistance"),
		FString("Reduces the chance of receiving critical hits.")
	);

	/*
	* Amplifination Attributes
	*/

	GameplayTags.Attributes_Secondary_FireAmplification = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Secondary.FireAmplification"),
		FString("Increases damage of all fire-based spells and effects.")
	);

	GameplayTags.Attributes_Secondary_FrostAmplification = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Secondary.FrostAmplification"),
		FString("Increases damage of all frost-based spells and effects.")
	);

	GameplayTags.Attributes_Secondary_LightningAmplification = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Secondary.LightningAmplification"),
		FString("Increases damage of all lightning-based spells and effects.")
	);

	GameplayTags.Attributes_Secondary_LightAmplification = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Secondary.LightAmplification"),
		FString("Increases damage of all light-based spells and effects.")
	);

	GameplayTags.Attributes_Secondary_PoisonAmplification = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Secondary.PoisonAmplification"),
		FString("Increases damage of all poison-based effects and spells.")
	);

	GameplayTags.Attributes_Secondary_OverallMagicAmplification = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Secondary.OverallMagicAmplification"),
		FString("Increases all spell damage regardless of element.")
	);

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
	GameplayTags.InputTag_SHIFT = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.SHIFT"), FString("Input Tag for SHIFT key"));

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
	GameplayTags.Condition_NoJump = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Condition.NoJump"), FString("Condition"));
	GameplayTags.Condition_NoDash = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Condition.NoDash"), FString("Condition"));
	GameplayTags.Condition_NoSprint= UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Condition.NoSprint"), FString("Condition"));

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
	* Primary Attributes
	*/

	GameplayTags.Cost_Health = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Cost.Health"), FString("Cost Health"));
	GameplayTags.Cost_Mana = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Cost.Mana"), FString("Cost Mana"));
	GameplayTags.Cost_Stamina = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Cost.Stamina"), FString("Cost Stamina"));

	/*
	* Abilities Tags
	*/

	GameplayTags.Ability_ConfirmState = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Ability.ConfirmState"), FString("Run when ability starts so no other ability is beeing cast"));
	
	GameplayTags.Abilities_Basic_Attack_1 = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Abilities.Basic.Attack_1"), FString("FireBolt Ability"));
	GameplayTags.Abilities_Basic_Attack_2 = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Abilities.Basic.Attack_2"), FString("FireBolt Ability"));

	GameplayTags.Abilities_Fire_FireBolt = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Abilities.Fire.FireBolt"), FString("FireBolt Ability"));
	GameplayTags.Abilities_Fire_FireRing = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Abilities.Fire.FireRing"), FString("Abilities_Fire_FireRing"));
	GameplayTags.Abilities_Fire_FirePillars = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Abilities.Fire.FirePillars"), FString("Abilities_Fire_FirePillars"));

	GameplayTags.Abilities_Frost_Icycle = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Abilities.Frost.Icycle"), FString("Abilities_Frost_Icycle"));
	GameplayTags.Abilities_Frost_FrostArea = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Abilities.Frost.FrostArea"), FString("Abilities_Frost_FrostArea"));
	GameplayTags.Abilities_Frost_Blizzard = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Abilities.Frost.Blizzard"), FString("Abilities_Frost_Blizzard"));

	GameplayTags.Abilities_Poison_CloudStrike = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Abilities.Poison.CloudStrike"), FString("Abilities_Poison_CloudStrike"));
	GameplayTags.Abilities_Poison_Injection = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Abilities.Poison.Injection"), FString("Abilities_Poison_Injection"));
	GameplayTags.Abilities_Poison_DragonsBreath = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Abilities.Poison.DragonsBreath"), FString("Abilities_Poison_DragonsBreath"));

	GameplayTags.Abilities_Light_DivineShot = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Abilities.Light.DivineShot"), FString("Abilities_Light_DivineShot"));
	GameplayTags.Abilities_Light_DivineAmnesty = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Abilities.Light.DivineAmnesty"), FString("Abilities_Light_DivineAmnesty"));
	GameplayTags.Abilities_Light_DivineStrike = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Abilities.Light.DivineStrike"), FString("Abilities_Light_DivineStrike"));
	GameplayTags.Abilities_Light_LightBeam = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Abilities.Light.LightBeam"), FString("Abilities_Light_LightBeam"));

	GameplayTags.Abilities_Electro_ShockBeam = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Abilities.Electro.ShockBeam"), FString("Abilities_Electro_ShockBeam"));
	GameplayTags.Abilities_Electro_Eleprison = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Abilities.Electro.Eleprison"), FString("Abilities_Electro_Eleprison"));
	GameplayTags.Abilities_Electro_ElectroStrike = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Abilities.Electro.ElectroStrike"), FString("Abilities_Electro_ElectroStrike"));

	GameplayTags.Abilities_Bow_ShotArrow = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Abilities.Bow.ShotArrow"), FString("Abilities_Bow_ShotArrow"));
	GameplayTags.Abilities_Bow_ChargedShot = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Abilities.Bow.ChargedShot"), FString("Abilities_Bow_ChargedShot"));

	GameplayTags.Abilities_Sword_ComboAttack_1 = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Abilities.Sword.ComboAttack.1"), FString("Abilities_Sword_ComboAttack_1"));
	GameplayTags.Abilities_Sword_ComboAttack_2 = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Abilities.Sword.ComboAttack.2"), FString("Abilities_Sword_ComboAttack_2"));
	GameplayTags.Abilities_Sword_ComboAttack_3 = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Abilities.Sword.ComboAttack.3"), FString("Abilities_Sword_ComboAttack_3"));
	GameplayTags.Abilities_Sword_ComboAttack_4 = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Abilities.Sword.ComboAttack.4"), FString("Abilities_Sword_ComboAttack_4"));
	GameplayTags.Abilities_Sword_GroundSlam = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Abilities.Sword.GroundSlam"), FString("Abilities_Sword_GroundSlam"));
	
	/*
	* Basic Movement tags
	*/

	GameplayTags.Abilities_BasicMovement_Dash = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Abilities.BasicMovement.Dash"), FString("Abilities_BasicMovement_Dash"));
	GameplayTags.Abilities_BasicMovement_Jump = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Abilities.BasicMovement.Jump"), FString("Abilities_BasicMovement_Jump"));
	GameplayTags.Abilities_BasicMovement_Sprint = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Abilities.BasicMovement.Sprint"), FString("Abilities_BasicMovement_Sprint"));

	/*
	* Boss Abilities tags
	*/

	GameplayTags.Abilities_Boss_Jungle_LightningStrikes = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Abilities.Boss.Jungle.LightningStrikes"), FString("Abilities_Boss_Jungle_LightningStrikes"));
	GameplayTags.Abilities_Boss_Jungle_SummonHelpers = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Abilities.Boss.Jungle.SummonHelpers"), FString("Abilities_Boss_Jungle_SummonHelpers"));
	GameplayTags.Abilities_Boss_Jungle_ToxicClouds = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Abilities.Boss.Jungle.ToxicClouds"), FString("Abilities_Boss_Jungle_ToxicClouds"));
	GameplayTags.Abilities_Boss_Jungle_PlantStrike = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Abilities.Boss.Jungle.PlantStrike"), FString("Abilities_Boss_Jungle_PlantStrike"));
	GameplayTags.Abilities_Boss_Jungle_Earthquake = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Abilities.Boss.Jungle.Earthquake"), FString("Abilities_Boss_Jungle_Earthquake"));
	GameplayTags.Abilities_Boss_Jungle_EarthShatter = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Abilities.Boss.Jungle.EarthShatter"), FString("Abilities_Boss_Jungle_EarthShatter"));

	/*
	* Abilities Cooldowns Tags
	*/

	GameplayTags.Cooldown_Fire_FireBolt = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Cooldown.Fire.FireBolt"), FString("FireBolt Ability Cooldown"));
	GameplayTags.Cooldown_Frost_FrostBolt = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Cooldown.Frost.FrostBolt"), FString("FireBolt Ability Cooldown"));
	GameplayTags.Cooldown_Poison_PoisonBolt = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Cooldown.Poison.PoisonBolt"), FString("FireBolt Ability Cooldown"));
	GameplayTags.Cooldown_Light_LightBolt = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Cooldown.Light.LightBolt"), FString("FireBolt Ability Cooldown"));
	GameplayTags.Cooldown_Electro_ElctroBolt = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Cooldown.Electro.ElctroBolt"), FString("FireBolt Ability Cooldown"));
	GameplayTags.Cooldown_Light_LightBeam = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Cooldown.Light.LightBeam"), FString("LightBeam Ability Cooldown"));

	//Fire

	GameplayTags.Cooldown_Fire_FireBolt = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Cooldown.Fire.FireBolt"), FString("FireBolt Ability Cooldown"));

	//Frost

	GameplayTags.Cooldown_Frost_FrostBolt = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Cooldown.Frost.FrostBolt"), FString("FrostBolt Ability Cooldown"));
	GameplayTags.Cooldown_Frost_EternalWinter = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Cooldown.Frost.EternalWinter"), FString("Eternal Winter Ability Cooldown"));

	GameplayTags.Effects_HitReact = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Effects.HitReact"), FString("Reaction to beeing hit"));

	/*
	* Abilities 
	*/

	GameplayTags.Abilities_AOE_TEST = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Abilities.AOE.Test"), FString("Attack Ability Tag"));
	GameplayTags.Abilities_HEAL_TEST = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Abilities.Heal.Test"), FString("Attack Ability Tag"));;
	//Frost

	GameplayTags.Abilities_Attack = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Abilities.Attack"), FString("Attack Ability Tag"));

	GameplayTags.Abilities_Summon = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Abilities.Summon"), FString("Summon Ability Tag"));

	/*
	* Combat Sockets
	*/


	GameplayTags.CombatSocket_Weapon = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("CombatSocket.Weapon"), FString("Weapon"));
	GameplayTags.CombatSocket_RightHand = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("CombatSocket.RightHand"), FString("Right Hand"));
	GameplayTags.CombatSocket_LeftHand = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("CombatSocket.LeftHand"), FString("Left Hand"));
	GameplayTags.CombatSocket_Tail = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("CombatSocket.Tail"), FString("Tail"));
	GameplayTags.CombatSocket_Ground = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("CombatSocket.Ground"), FString("Ground"));

	/*
	* Montage Tags
	*/

	GameplayTags.Montage_Attack_1 = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Montage.Attack.1"), FString("Attack 1"));
	GameplayTags.Montage_Attack_2 = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Montage.Attack.2"), FString("Attack 2"));
	GameplayTags.Montage_Attack_3 = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Montage.Attack.3"), FString("Attack 3"));
	GameplayTags.Montage_Attack_4 = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Montage.Attack.4"), FString("Attack 4"));

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