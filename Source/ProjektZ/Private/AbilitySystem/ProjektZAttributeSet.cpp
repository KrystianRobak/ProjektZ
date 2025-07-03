// Fill out your copyright notice in the Description page of Project Settings.

#include "AbilitySystem/ProjektZAttributeSet.h"
#include "GameFramework/Character.h"
#include "AbilitySystemComponent.h"
#include "GameplayEffectExtension.h"
#include <Net/UnrealNetwork.h>
#include <AbilitySystemBlueprintLibrary.h>
#include <ProjektZGameplayTags.h>
#include <Interaction/CombatInterface.h>
#include <AbilitySystem/ProjektZAbilitySystemLibrary.h>
#include <Kismet/GameplayStatics.h>
#include <Player/PC_PlayerController.h>

UProjektZAttributeSet::UProjektZAttributeSet()
{
	PopulateTagsToAttributesMap();
}

void UProjektZAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	// --- Primary Attributes ---
	DOREPLIFETIME_CONDITION_NOTIFY(UProjektZAttributeSet, Strength, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UProjektZAttributeSet, Vitality, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UProjektZAttributeSet, Dexterity, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UProjektZAttributeSet, Intelligence, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UProjektZAttributeSet, Willpower, COND_None, REPNOTIFY_Always);

	// --- Secondary Attributes ---
	DOREPLIFETIME_CONDITION_NOTIFY(UProjektZAttributeSet, PhysicalDamage, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UProjektZAttributeSet, MagicPower, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UProjektZAttributeSet, SpellCriticalChance, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UProjektZAttributeSet, SpellCriticalDamage, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UProjektZAttributeSet, CooldownReduction, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UProjektZAttributeSet, AttackSpeed, COND_None, REPNOTIFY_Always);

	DOREPLIFETIME_CONDITION_NOTIFY(UProjektZAttributeSet, Armor, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UProjektZAttributeSet, ArmorPenetration, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UProjektZAttributeSet, BlockChance, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UProjektZAttributeSet, CriticalHitChance, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UProjektZAttributeSet, CriticalHitDamage, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UProjektZAttributeSet, CriticalHitResistance, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UProjektZAttributeSet, HealthRegeneration, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UProjektZAttributeSet, ManaRegeneration, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UProjektZAttributeSet, StaminaRegeneration, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UProjektZAttributeSet, MaxHealth, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UProjektZAttributeSet, MaxMana, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UProjektZAttributeSet, MaxStamina, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UProjektZAttributeSet, MovementSpeed, COND_None, REPNOTIFY_Always);

	// --- Secondary Attributes: Amplification ---
	DOREPLIFETIME_CONDITION_NOTIFY(UProjektZAttributeSet, FireAmplification, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UProjektZAttributeSet, FrostAmplification, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UProjektZAttributeSet, LightningAmplification, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UProjektZAttributeSet, LightAmplification, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UProjektZAttributeSet, PoisonAmplification, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UProjektZAttributeSet, OverallMagicAmplification, COND_None, REPNOTIFY_Always);

	// --- Resistance Attributes ---
	DOREPLIFETIME_CONDITION_NOTIFY(UProjektZAttributeSet, FireResistance, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UProjektZAttributeSet, FrostResistance, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UProjektZAttributeSet, LightningResistance, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UProjektZAttributeSet, LightResistance, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UProjektZAttributeSet, PhysicalResistance, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UProjektZAttributeSet, PoisonResistance, COND_None, REPNOTIFY_Always);

	// --- Vital Attributes ---
	DOREPLIFETIME_CONDITION_NOTIFY(UProjektZAttributeSet, Health, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UProjektZAttributeSet, Mana, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UProjektZAttributeSet, Stamina, COND_None, REPNOTIFY_Always);

	// --- Stat Tracking ---
	DOREPLIFETIME_CONDITION_NOTIFY(UProjektZAttributeSet, DamageDealt, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UProjektZAttributeSet, FireDamageDealt, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UProjektZAttributeSet, FrostDamageDealt, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UProjektZAttributeSet, LightningDamageDealt, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UProjektZAttributeSet, PhysicalDamageDealt, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UProjektZAttributeSet, PoisonDamageDealt, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UProjektZAttributeSet, LightDamageDealt, COND_None, REPNOTIFY_Always); // New
	DOREPLIFETIME_CONDITION_NOTIFY(UProjektZAttributeSet, DamageTanked, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UProjektZAttributeSet, HealthRecovered, COND_None, REPNOTIFY_Always);
}

void UProjektZAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);

	// Clamping Vital Attributes
	if (Attribute == GetHealthAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.f, GetMaxHealth());
	}
	else if (Attribute == GetManaAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.f, GetMaxMana());
	}
	else if (Attribute == GetStaminaAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.f, GetMaxStamina());
	}
}

void UProjektZAttributeSet::SetEffectProperties(const FGameplayEffectModCallbackData& Data, FEffectProperties& Props) const
{
	// Source = causer of effect | Target = target of effect (owner of THIS AttributeSet) 

	Props.EffectContextHandler = Data.EffectSpec.GetContext();
	Props.SourceAbilitySystemComponent = Props.EffectContextHandler.GetOriginalInstigatorAbilitySystemComponent();

	if (IsValid(Props.SourceAbilitySystemComponent) && Props.SourceAbilitySystemComponent->AbilityActorInfo.IsValid() && Props.SourceAbilitySystemComponent->AbilityActorInfo->AvatarActor.IsValid())
	{
		Props.SourceAvatarActor = Props.SourceAbilitySystemComponent->AbilityActorInfo->AvatarActor.Get();
		Props.SourceController = Props.SourceAbilitySystemComponent->AbilityActorInfo->PlayerController.Get();
		if (Props.SourceController == nullptr && Props.SourceAvatarActor != nullptr)
		{
			if (const APawn* Pawn = Cast<APawn>(Props.SourceAvatarActor))
			{
				Props.SourceController = Pawn->GetController();
			}
		}

		if (Props.SourceController)
		{
			Props.SourceCharacter = Cast<ACharacter>(Props.SourceController->GetPawn());
		}
	}

	if (Data.Target.AbilityActorInfo.IsValid() && Data.Target.AbilityActorInfo->AvatarActor.IsValid())
	{
		Props.TargetAvatarActor = Data.Target.AbilityActorInfo->AvatarActor.Get();
		Props.TargetController = Data.Target.AbilityActorInfo->PlayerController.Get();
		Props.TargetCharacter = Cast<ACharacter>(Props.TargetAvatarActor);
		Props.TargetAbilitySystemComponent = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(Props.TargetAvatarActor);
	}
}

void UProjektZAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	FEffectProperties Props;
	SetEffectProperties(Data, Props);

	if (Data.EvaluatedData.Attribute == GetHealthAttribute())
	{
		SetHealth(FMath::Clamp(GetHealth(), 0.f, GetMaxHealth()));
		UE_LOG(LogTemp, Warning, TEXT("Changed Health on %s, Health: %f"), *Props.TargetAvatarActor->GetName(), GetHealth());
	}
	else if (Data.EvaluatedData.Attribute == GetManaAttribute())
	{
		SetMana(FMath::Clamp(GetMana(), 0.f, GetMaxMana()));
	}
	else if (Data.EvaluatedData.Attribute == GetStaminaAttribute())
	{
		SetStamina(FMath::Clamp(GetStamina(), 0.f, GetMaxStamina()));
	}
	else if (Data.EvaluatedData.Attribute == GetIncomingDamageAttribute())
	{
		const float LocalIncomingDamage = GetIncomingDamage();
		SetIncomingDamage(0);

		if (LocalIncomingDamage > 0)
		{
			const float NewHealth = GetHealth() - LocalIncomingDamage;
			SetHealth(FMath::Clamp(NewHealth, 0, GetMaxHealth()));

			const bool bFatal = NewHealth <= 0.f;
			if (bFatal)
			{
				ICombatInterface* CombatInterface = Cast<ICombatInterface>(Props.TargetAvatarActor);
				if (CombatInterface)
				{
					CombatInterface->Die();
				}
			}
			else
			{
				FGameplayTagContainer TagContainer;
				TagContainer.AddTag(FProjektZGameplayTags::Get().Effects_HitReact);
				Props.TargetAbilitySystemComponent->TryActivateAbilitiesByTag(TagContainer);
			}

			const bool bBlockedHit = UProjektZAbilitySystemLibrary::IsBlockedHit(Props.EffectContextHandler);
			const bool bCriticalHit = UProjektZAbilitySystemLibrary::IsCriticalHit(Props.EffectContextHandler);
			ShowFloatingText(Props, LocalIncomingDamage, bBlockedHit, bCriticalHit);
		}
	}
}

void UProjektZAttributeSet::ShowFloatingText(const FEffectProperties& Props, float Damage, bool bBlockedHit, bool bCriticalHit) const
{
	if (Props.SourceCharacter != Props.TargetCharacter) {
		if (APC_PlayerController* PC = Cast<APC_PlayerController>(UGameplayStatics::GetPlayerController(Props.SourceCharacter, 0)))
		{
			PC->ShowDamageNumber(Damage, Props.TargetCharacter);
			return;
		}
		if (APC_PlayerController* PC = Cast<APC_PlayerController>(UGameplayStatics::GetPlayerController(Props.TargetCharacter, 0)))
		{
			PC->ShowDamageNumber(Damage, Props.TargetCharacter);
		}
	}
}

// --- Primary Attribute OnRep Functions ---
void UProjektZAttributeSet::OnRep_Strength(const FGameplayAttributeData& OldStrength) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UProjektZAttributeSet, Strength, OldStrength);
}

void UProjektZAttributeSet::OnRep_Vitality(const FGameplayAttributeData& OldVitality) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UProjektZAttributeSet, Vitality, OldVitality);
}

void UProjektZAttributeSet::OnRep_Dexterity(const FGameplayAttributeData& OldDexterity) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UProjektZAttributeSet, Dexterity, OldDexterity);
}

void UProjektZAttributeSet::OnRep_Intelligence(const FGameplayAttributeData& OldIntelligence) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UProjektZAttributeSet, Intelligence, OldIntelligence);
}

void UProjektZAttributeSet::OnRep_Willpower(const FGameplayAttributeData& OldWillpower) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UProjektZAttributeSet, Willpower, OldWillpower);
}

// --- Secondary Attribute OnRep Functions ---
void UProjektZAttributeSet::OnRep_PhysicalDamage(const FGameplayAttributeData& OldPhysicalDamage) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UProjektZAttributeSet, PhysicalDamage, OldPhysicalDamage);
}

void UProjektZAttributeSet::OnRep_MagicPower(const FGameplayAttributeData& OldMagicPower) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UProjektZAttributeSet, MagicPower, OldMagicPower);
}

void UProjektZAttributeSet::OnRep_SpellCriticalChance(const FGameplayAttributeData& OldSpellCriticalChance) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UProjektZAttributeSet, SpellCriticalChance, OldSpellCriticalChance);
}

void UProjektZAttributeSet::OnRep_SpellCriticalDamage(const FGameplayAttributeData& OldSpellCriticalDamage) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UProjektZAttributeSet, SpellCriticalDamage, OldSpellCriticalDamage);
}

void UProjektZAttributeSet::OnRep_CooldownReduction(const FGameplayAttributeData& OldCooldownReduction) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UProjektZAttributeSet, CooldownReduction, OldCooldownReduction);
}

void UProjektZAttributeSet::OnRep_AttackSpeed(const FGameplayAttributeData& OldAttackSpeed) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UProjektZAttributeSet, AttackSpeed, OldAttackSpeed);
}

void UProjektZAttributeSet::OnRep_Armor(const FGameplayAttributeData& OldArmor) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UProjektZAttributeSet, Armor, OldArmor);
}

void UProjektZAttributeSet::OnRep_ArmorPenetration(const FGameplayAttributeData& OldArmorPenetration) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UProjektZAttributeSet, ArmorPenetration, OldArmorPenetration);
}

void UProjektZAttributeSet::OnRep_BlockChance(const FGameplayAttributeData& OldBlockChance) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UProjektZAttributeSet, BlockChance, OldBlockChance);
}

void UProjektZAttributeSet::OnRep_CriticalHitChance(const FGameplayAttributeData& OldCriticalHitChance) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UProjektZAttributeSet, CriticalHitChance, OldCriticalHitChance);
}

void UProjektZAttributeSet::OnRep_CriticalHitDamage(const FGameplayAttributeData& OldCriticalHitDamage) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UProjektZAttributeSet, CriticalHitDamage, OldCriticalHitDamage);
}

void UProjektZAttributeSet::OnRep_CriticalHitResistance(const FGameplayAttributeData& OldCriticalHitResistance) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UProjektZAttributeSet, CriticalHitResistance, OldCriticalHitResistance);
}

void UProjektZAttributeSet::OnRep_HealthRegeneration(const FGameplayAttributeData& OldHealthRegeneration) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UProjektZAttributeSet, HealthRegeneration, OldHealthRegeneration);
}

void UProjektZAttributeSet::OnRep_ManaRegeneration(const FGameplayAttributeData& OldManaRegeneration) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UProjektZAttributeSet, ManaRegeneration, OldManaRegeneration);
}

void UProjektZAttributeSet::OnRep_StaminaRegeneration(const FGameplayAttributeData& OldStaminaRegeneration) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UProjektZAttributeSet, StaminaRegeneration, OldStaminaRegeneration);
}

void UProjektZAttributeSet::OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UProjektZAttributeSet, MaxHealth, OldMaxHealth);
}

void UProjektZAttributeSet::OnRep_MaxMana(const FGameplayAttributeData& OldMaxMana) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UProjektZAttributeSet, MaxMana, OldMaxMana);
}

void UProjektZAttributeSet::OnRep_MaxStamina(const FGameplayAttributeData& OldMaxStamina) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UProjektZAttributeSet, MaxStamina, OldMaxStamina);
}

void UProjektZAttributeSet::OnRep_MovementSpeed(const FGameplayAttributeData& OldMovementSpeed) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UProjektZAttributeSet, MovementSpeed, OldMovementSpeed);
}

// --- Amplification OnRep Functions ---
void UProjektZAttributeSet::OnRep_FireAmplification(const FGameplayAttributeData& OldFireAmplification) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UProjektZAttributeSet, FireAmplification, OldFireAmplification);
}

void UProjektZAttributeSet::OnRep_FrostAmplification(const FGameplayAttributeData& OldFrostAmplification) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UProjektZAttributeSet, FrostAmplification, OldFrostAmplification);
}

void UProjektZAttributeSet::OnRep_LightningAmplification(const FGameplayAttributeData& OldLightningAmplification) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UProjektZAttributeSet, LightningAmplification, OldLightningAmplification);
}

void UProjektZAttributeSet::OnRep_LightAmplification(const FGameplayAttributeData& OldLightAmplification) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UProjektZAttributeSet, LightAmplification, OldLightAmplification);
}

void UProjektZAttributeSet::OnRep_PoisonAmplification(const FGameplayAttributeData& OldPoisonAmplification) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UProjektZAttributeSet, PoisonAmplification, OldPoisonAmplification);
}

void UProjektZAttributeSet::OnRep_OverallMagicAmplification(const FGameplayAttributeData& OldOverallMagicAmplification) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UProjektZAttributeSet, OverallMagicAmplification, OldOverallMagicAmplification);
}

// --- Resistance OnRep Functions ---
void UProjektZAttributeSet::OnRep_FireResistance(const FGameplayAttributeData& OldFireResistance) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UProjektZAttributeSet, FireResistance, OldFireResistance);
}

void UProjektZAttributeSet::OnRep_FrostResistance(const FGameplayAttributeData& OldFrostResistance) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UProjektZAttributeSet, FrostResistance, OldFrostResistance);
}

void UProjektZAttributeSet::OnRep_LightningResistance(const FGameplayAttributeData& OldLightningResistance) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UProjektZAttributeSet, LightningResistance, OldLightningResistance);
}

void UProjektZAttributeSet::OnRep_LightResistance(const FGameplayAttributeData& OldLightResistance) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UProjektZAttributeSet, LightResistance, OldLightResistance);
}

void UProjektZAttributeSet::OnRep_PhysicalResistance(const FGameplayAttributeData& OldPhysicalResistance) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UProjektZAttributeSet, PhysicalResistance, OldPhysicalResistance);
}

void UProjektZAttributeSet::OnRep_PoisonResistance(const FGameplayAttributeData& OldPoisonResistance) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UProjektZAttributeSet, PoisonResistance, OldPoisonResistance);
}

// --- Vital Attribute OnRep Functions ---
void UProjektZAttributeSet::OnRep_Health(const FGameplayAttributeData& OldHealth) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UProjektZAttributeSet, Health, OldHealth);
}

void UProjektZAttributeSet::OnRep_Mana(const FGameplayAttributeData& OldMana) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UProjektZAttributeSet, Mana, OldMana);
}

void UProjektZAttributeSet::OnRep_Stamina(const FGameplayAttributeData& OldStamina) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UProjektZAttributeSet, Stamina, OldStamina);
}

// --- Stat Tracking OnRep Functions ---
void UProjektZAttributeSet::OnRep_DamageDealt(const FGameplayAttributeData& OldDamageDealt) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UProjektZAttributeSet, DamageDealt, OldDamageDealt);
}

void UProjektZAttributeSet::OnRep_FireDamageDealt(const FGameplayAttributeData& OldFireDamageDealt) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UProjektZAttributeSet, FireDamageDealt, OldFireDamageDealt);
}

void UProjektZAttributeSet::OnRep_FrostDamageDealt(const FGameplayAttributeData& OldFrostDamageDealt) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UProjektZAttributeSet, FrostDamageDealt, OldFrostDamageDealt);
}

void UProjektZAttributeSet::OnRep_LightningDamageDealt(const FGameplayAttributeData& OldLightningDamageDealt) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UProjektZAttributeSet, LightningDamageDealt, OldLightningDamageDealt);
}

void UProjektZAttributeSet::OnRep_PhysicalDamageDealt(const FGameplayAttributeData& OldPhysicalDamageDealt) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UProjektZAttributeSet, PhysicalDamageDealt, OldPhysicalDamageDealt);
}

void UProjektZAttributeSet::OnRep_PoisonDamageDealt(const FGameplayAttributeData& OldPoisonDamageDealt) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UProjektZAttributeSet, PoisonDamageDealt, OldPoisonDamageDealt);
}

void UProjektZAttributeSet::OnRep_LightDamageDealt(const FGameplayAttributeData& OldLightDamageDealt) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UProjektZAttributeSet, LightDamageDealt, OldLightDamageDealt);
}

void UProjektZAttributeSet::OnRep_DamageTanked(const FGameplayAttributeData& OldDamageTanked) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UProjektZAttributeSet, DamageTanked, OldDamageTanked);
}

void UProjektZAttributeSet::OnRep_HealthRecovered(const FGameplayAttributeData& OldHealthRecovered) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UProjektZAttributeSet, HealthRecovered, OldHealthRecovered);
}

// --- PopulateTagsToAttributesMap ---
void UProjektZAttributeSet::PopulateTagsToAttributesMap()
{
	FProjektZGameplayTags GameplayTags = FProjektZGameplayTags::Get();

	// Primary Attributes
	TagsToAttributes.Add(GameplayTags.Attributes_Primary_Strength, GetStrengthAttribute());
	TagsToAttributes.Add(GameplayTags.Attributes_Primary_Vitality, GetVitalityAttribute());
	TagsToAttributes.Add(GameplayTags.Attributes_Primary_Dexterity, GetDexterityAttribute());
	TagsToAttributes.Add(GameplayTags.Attributes_Primary_Intelligence, GetIntelligenceAttribute());
	TagsToAttributes.Add(GameplayTags.Attributes_Primary_Willpower, GetWillpowerAttribute());

	// Secondary Attributes - Core Derived Stats
	TagsToAttributes.Add(GameplayTags.Attributes_Secondary_MaxHealth, GetMaxHealthAttribute());
	TagsToAttributes.Add(GameplayTags.Attributes_Secondary_HealthRegeneration, GetHealthRegenerationAttribute());
	TagsToAttributes.Add(GameplayTags.Attributes_Secondary_MaxMana, GetMaxManaAttribute());
	TagsToAttributes.Add(GameplayTags.Attributes_Secondary_ManaRegeneration, GetManaRegenerationAttribute());
	TagsToAttributes.Add(GameplayTags.Attributes_Secondary_MaxStamina, GetMaxStaminaAttribute());
	TagsToAttributes.Add(GameplayTags.Attributes_Secondary_StaminaRegeneration, GetStaminaRegenerationAttribute());

	// Secondary Attributes - Combat Stats
	TagsToAttributes.Add(GameplayTags.Attributes_Secondary_PhysicalDamage, GetPhysicalDamageAttribute());
	TagsToAttributes.Add(GameplayTags.Attributes_Secondary_MagicPower, GetMagicPowerAttribute());
	TagsToAttributes.Add(GameplayTags.Attributes_Secondary_SpellCriticalChance, GetSpellCriticalChanceAttribute());
	TagsToAttributes.Add(GameplayTags.Attributes_Secondary_SpellCriticalDamage, GetSpellCriticalDamageAttribute());
	TagsToAttributes.Add(GameplayTags.Attributes_Secondary_CooldownReduction, GetCooldownReductionAttribute());
	TagsToAttributes.Add(GameplayTags.Attributes_Secondary_AttackSpeed, GetAttackSpeedAttribute());
	TagsToAttributes.Add(GameplayTags.Attributes_Secondary_MovementSpeed, GetMovementSpeedAttribute());

	TagsToAttributes.Add(GameplayTags.Attributes_Secondary_Armor, GetArmorAttribute());
	TagsToAttributes.Add(GameplayTags.Attributes_Secondary_ArmorPenetration, GetArmorPenetrationAttribute());
	TagsToAttributes.Add(GameplayTags.Attributes_Secondary_BlockChance, GetBlockChanceAttribute());
	TagsToAttributes.Add(GameplayTags.Attributes_Secondary_CriticalHitChance, GetCriticalHitChanceAttribute());
	TagsToAttributes.Add(GameplayTags.Attributes_Secondary_CriticalHitDamage, GetCriticalHitDamageAttribute());
	TagsToAttributes.Add(GameplayTags.Attributes_Secondary_CriticalHitResistance, GetCriticalHitResistanceAttribute());

	// Secondary Attributes - Amplifications
	TagsToAttributes.Add(GameplayTags.Attributes_Secondary_FireAmplification, GetFireAmplificationAttribute());
	TagsToAttributes.Add(GameplayTags.Attributes_Secondary_FrostAmplification, GetFrostAmplificationAttribute());
	TagsToAttributes.Add(GameplayTags.Attributes_Secondary_LightningAmplification, GetLightningAmplificationAttribute());
	TagsToAttributes.Add(GameplayTags.Attributes_Secondary_LightAmplification, GetLightAmplificationAttribute());
	TagsToAttributes.Add(GameplayTags.Attributes_Secondary_PoisonAmplification, GetPoisonAmplificationAttribute());
	TagsToAttributes.Add(GameplayTags.Attributes_Secondary_OverallMagicAmplification, GetOverallMagicAmplificationAttribute());

	// Resistances
	TagsToAttributes.Add(GameplayTags.Attributes_Resistance_Fire, GetFireResistanceAttribute());
	TagsToAttributes.Add(GameplayTags.Attributes_Resistance_Frost, GetFrostResistanceAttribute());
	TagsToAttributes.Add(GameplayTags.Attributes_Resistance_Lightning, GetLightningResistanceAttribute());
	TagsToAttributes.Add(GameplayTags.Attributes_Resistance_Light, GetLightResistanceAttribute());
	TagsToAttributes.Add(GameplayTags.Attributes_Resistance_Physical, GetPhysicalResistanceAttribute());
	TagsToAttributes.Add(GameplayTags.Attributes_Resistance_Poison, GetPoisonResistanceAttribute());

	// Stat Tracking
	TagsToAttributes.Add(GameplayTags.STATSTRACK_DamageDealt, GetDamageDealtAttribute());
	TagsToAttributes.Add(GameplayTags.STATSTRACK_FireDamageDealt, GetFireDamageDealtAttribute());
	TagsToAttributes.Add(GameplayTags.STATSTRACK_FrostDamageDealt, GetFrostDamageDealtAttribute());
	TagsToAttributes.Add(GameplayTags.STATSTRACK_LightningDamageDealt, GetLightningDamageDealtAttribute());
	TagsToAttributes.Add(GameplayTags.STATSTRACK_PhysicalDamageDealt, GetPhysicalDamageDealtAttribute());
	TagsToAttributes.Add(GameplayTags.STATSTRACK_PoisonDamageDealt, GetPoisonDamageDealtAttribute());
	TagsToAttributes.Add(GameplayTags.STATSTRACK_LightDamageDealt, GetLightDamageDealtAttribute());
	TagsToAttributes.Add(GameplayTags.STATSTRACK_DamageTanked, GetDamageTankedAttribute());
	TagsToAttributes.Add(GameplayTags.STATSTRACK_HealthRecovered, GetHealthRecoveredAttribute());
}
