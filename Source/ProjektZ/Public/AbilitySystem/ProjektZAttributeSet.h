// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "ProjektZAttributeSet.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
 	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
 	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
 	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

USTRUCT()
struct FEffectProperties {

	GENERATED_BODY()

	FEffectProperties() {}

	UPROPERTY()
	UAbilitySystemComponent* SourceAbilitySystemComponent = nullptr;

	UPROPERTY()
	AActor* SourceAvatarActor = nullptr;

	UPROPERTY()
	AController* SourceController = nullptr;

	UPROPERTY()
	ACharacter* SourceCharacter = nullptr;

	FGameplayEffectContextHandle EffectContextHandler;

	UPROPERTY()
	UAbilitySystemComponent* TargetAbilitySystemComponent = nullptr;

	UPROPERTY()
	AActor* TargetAvatarActor = nullptr;

	UPROPERTY()
	AController* TargetController = nullptr;

	UPROPERTY()
	ACharacter* TargetCharacter = nullptr;
};

/**
 * 
 */

UCLASS()
class PROJEKTZ_API UProjektZAttributeSet : public UAttributeSet
{
	GENERATED_BODY()
public:
	
	UProjektZAttributeSet();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;

	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;

	TMap<FGameplayTag, FGameplayAttribute> TagsToAttributes;

	void PopulateTagsToAttributesMap();

	 /*
	 *	Meta Attributes
	 */

	UPROPERTY(BlueprintReadOnly, Category = "Meta Attributes")
	FGameplayAttributeData IncomingDamage;
	ATTRIBUTE_ACCESSORS(UProjektZAttributeSet, IncomingDamage)

        /*
        * Secondary Attributes - Core Derived Stats
        */
        UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxHealth, Category = "Secondary Attributes|Core Derived")
    FGameplayAttributeData MaxHealth;
    ATTRIBUTE_ACCESSORS(UProjektZAttributeSet, MaxHealth)

        UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_HealthRegeneration, Category = "Secondary Attributes|Core Derived")
    FGameplayAttributeData HealthRegeneration;
    ATTRIBUTE_ACCESSORS(UProjektZAttributeSet, HealthRegeneration)

        UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxMana, Category = "Secondary Attributes|Core Derived")
    FGameplayAttributeData MaxMana;
    ATTRIBUTE_ACCESSORS(UProjektZAttributeSet, MaxMana)

        UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_ManaRegeneration, Category = "Secondary Attributes|Core Derived")
    FGameplayAttributeData ManaRegeneration;
    ATTRIBUTE_ACCESSORS(UProjektZAttributeSet, ManaRegeneration)

        UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxStamina, Category = "Secondary Attributes|Core Derived")
    FGameplayAttributeData MaxStamina;
    ATTRIBUTE_ACCESSORS(UProjektZAttributeSet, MaxStamina)

        UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_StaminaRegeneration, Category = "Secondary Attributes|Core Derived") // NEW: StaminaRegeneration
        FGameplayAttributeData StaminaRegeneration;
    ATTRIBUTE_ACCESSORS(UProjektZAttributeSet, StaminaRegeneration)


        /*
         * Secondary Attributes - Combat Stats
         */
        UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_PhysicalDamage, Category = "Secondary Attributes|Combat") // NEW: PhysicalDamage
        FGameplayAttributeData PhysicalDamage;
    ATTRIBUTE_ACCESSORS(UProjektZAttributeSet, PhysicalDamage)

        UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_WeaponDamage, Category = "Secondary Attributes|Combat") // NEW: WeaponDamage
        FGameplayAttributeData WeaponDamage;
    ATTRIBUTE_ACCESSORS(UProjektZAttributeSet, WeaponDamage)

        UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MagicPower, Category = "Secondary Attributes|Combat") // NEW: MagicPower
        FGameplayAttributeData MagicPower;
    ATTRIBUTE_ACCESSORS(UProjektZAttributeSet, MagicPower)

        UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_SpellCriticalChance, Category = "Secondary Attributes|Combat") // NEW: SpellCriticalChance
        FGameplayAttributeData SpellCriticalChance;
    ATTRIBUTE_ACCESSORS(UProjektZAttributeSet, SpellCriticalChance)

        UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_SpellCriticalDamage, Category = "Secondary Attributes|Combat") // NEW: SpellCriticalDamage
        FGameplayAttributeData SpellCriticalDamage;
    ATTRIBUTE_ACCESSORS(UProjektZAttributeSet, SpellCriticalDamage)

        UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_CooldownReduction, Category = "Secondary Attributes|Combat") // NEW: CooldownReduction
        FGameplayAttributeData CooldownReduction;
    ATTRIBUTE_ACCESSORS(UProjektZAttributeSet, CooldownReduction)

        UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_AttackSpeed, Category = "Secondary Attributes|Combat") // NEW: AttackSpeed
        FGameplayAttributeData AttackSpeed;
    ATTRIBUTE_ACCESSORS(UProjektZAttributeSet, AttackSpeed)

        UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MovementSpeed, Category = "Secondary Attributes|Combat")
    FGameplayAttributeData MovementSpeed;
    ATTRIBUTE_ACCESSORS(UProjektZAttributeSet, MovementSpeed)

        UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Armor, Category = "Secondary Attributes|Combat")
    FGameplayAttributeData Armor;
    ATTRIBUTE_ACCESSORS(UProjektZAttributeSet, Armor)

        UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_ArmorPenetration, Category = "Secondary Attributes|Combat")
    FGameplayAttributeData ArmorPenetration;
    ATTRIBUTE_ACCESSORS(UProjektZAttributeSet, ArmorPenetration)

        UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_BlockChance, Category = "Secondary Attributes|Combat")
    FGameplayAttributeData BlockChance;
    ATTRIBUTE_ACCESSORS(UProjektZAttributeSet, BlockChance)

        UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_CriticalHitChance, Category = "Secondary Attributes|Combat")
    FGameplayAttributeData CriticalHitChance;
    ATTRIBUTE_ACCESSORS(UProjektZAttributeSet, CriticalHitChance)

        UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_CriticalHitDamage, Category = "Secondary Attributes|Combat")
    FGameplayAttributeData CriticalHitDamage;
    ATTRIBUTE_ACCESSORS(UProjektZAttributeSet, CriticalHitDamage)

        UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_CriticalHitResistance, Category = "Secondary Attributes|Combat")
    FGameplayAttributeData CriticalHitResistance;
    ATTRIBUTE_ACCESSORS(UProjektZAttributeSet, CriticalHitResistance)


        /*
         * Secondary Attributes - Amplifications (Percentage based)
         */
        UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_FireAmplification, Category = "Secondary Attributes|Amplification") // NEW: FireAmplification
        FGameplayAttributeData FireAmplification;
    ATTRIBUTE_ACCESSORS(UProjektZAttributeSet, FireAmplification)

        UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_FrostAmplification, Category = "Secondary Attributes|Amplification") // NEW: FrostAmplification
        FGameplayAttributeData FrostAmplification;
    ATTRIBUTE_ACCESSORS(UProjektZAttributeSet, FrostAmplification)

        UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_LightningAmplification, Category = "Secondary Attributes|Amplification") // NEW: LightningAmplification
        FGameplayAttributeData LightningAmplification;
    ATTRIBUTE_ACCESSORS(UProjektZAttributeSet, LightningAmplification)

        UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_LightAmplification, Category = "Secondary Attributes|Amplification") // NEW: LightAmplification
        FGameplayAttributeData LightAmplification;
    ATTRIBUTE_ACCESSORS(UProjektZAttributeSet, LightAmplification)

        UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_PoisonAmplification, Category = "Secondary Attributes|Amplification") // NEW: PoisonAmplification
        FGameplayAttributeData PoisonAmplification;
    ATTRIBUTE_ACCESSORS(UProjektZAttributeSet, PoisonAmplification)

        UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_OverallMagicAmplification, Category = "Secondary Attributes|Amplification") // NEW: OverallMagicAmplification
        FGameplayAttributeData OverallMagicAmplification;
    ATTRIBUTE_ACCESSORS(UProjektZAttributeSet, OverallMagicAmplification)


        /*
         * Secondary Attributes - Resistances (moved to their own category for clarity)
         */
        UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_FireResistance, Category = "Secondary Attributes|Resistances")
    FGameplayAttributeData FireResistance;
    ATTRIBUTE_ACCESSORS(UProjektZAttributeSet, FireResistance)

        UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_FrostResistance, Category = "Secondary Attributes|Resistances")
    FGameplayAttributeData FrostResistance;
    ATTRIBUTE_ACCESSORS(UProjektZAttributeSet, FrostResistance)

        UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_LightningResistance, Category = "Secondary Attributes|Resistances")
    FGameplayAttributeData LightningResistance;
    ATTRIBUTE_ACCESSORS(UProjektZAttributeSet, LightningResistance)

        UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_PhysicalResistance, Category = "Secondary Attributes|Resistances")
    FGameplayAttributeData PhysicalResistance;
    ATTRIBUTE_ACCESSORS(UProjektZAttributeSet, PhysicalResistance)

        UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_PoisonResistance, Category = "Secondary Attributes|Resistances")
    FGameplayAttributeData PoisonResistance;
    ATTRIBUTE_ACCESSORS(UProjektZAttributeSet, PoisonResistance)

        UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_LightResistance, Category = "Secondary Attributes|Resistances")
    FGameplayAttributeData LightResistance;
    ATTRIBUTE_ACCESSORS(UProjektZAttributeSet, LightResistance)

        /*
         * Vital Attributes
         */
        UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Health, Category = "Vital Attributes")
    FGameplayAttributeData Health;
    ATTRIBUTE_ACCESSORS(UProjektZAttributeSet, Health)

        UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Mana, Category = "Vital Attributes")
    FGameplayAttributeData Mana;
    ATTRIBUTE_ACCESSORS(UProjektZAttributeSet, Mana)

        UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Stamina, Category = "Vital Attributes")
    FGameplayAttributeData Stamina;
    ATTRIBUTE_ACCESSORS(UProjektZAttributeSet, Stamina)

        /*
         * Stat Tracking Attributes
         */
        UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_DamageDealt, Category = "Stats Tracker")
    FGameplayAttributeData DamageDealt;
    ATTRIBUTE_ACCESSORS(UProjektZAttributeSet, DamageDealt)

        UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_FireDamageDealt, Category = "Stats Tracker")
    FGameplayAttributeData FireDamageDealt;
    ATTRIBUTE_ACCESSORS(UProjektZAttributeSet, FireDamageDealt)

        UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_FrostDamageDealt, Category = "Stats Tracker")
    FGameplayAttributeData FrostDamageDealt;
    ATTRIBUTE_ACCESSORS(UProjektZAttributeSet, FrostDamageDealt)

        UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_LightningDamageDealt, Category = "Stats Tracker")
    FGameplayAttributeData LightningDamageDealt;
    ATTRIBUTE_ACCESSORS(UProjektZAttributeSet, LightningDamageDealt)

        UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_PhysicalDamageDealt, Category = "Stats Tracker")
    FGameplayAttributeData PhysicalDamageDealt;
    ATTRIBUTE_ACCESSORS(UProjektZAttributeSet, PhysicalDamageDealt)

        UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_PoisonDamageDealt, Category = "Stats Tracker")
    FGameplayAttributeData PoisonDamageDealt;
    ATTRIBUTE_ACCESSORS(UProjektZAttributeSet, PoisonDamageDealt)

        UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_LightDamageDealt, Category = "Stats Tracker") // NEW: LightDamageDealt
        FGameplayAttributeData LightDamageDealt;
    ATTRIBUTE_ACCESSORS(UProjektZAttributeSet, LightDamageDealt)

        UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_DamageTanked, Category = "Stats Tracker")
    FGameplayAttributeData DamageTanked;
    ATTRIBUTE_ACCESSORS(UProjektZAttributeSet, DamageTanked)

        UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_HealthRecovered, Category = "Stats Tracker")
    FGameplayAttributeData HealthRecovered;
    ATTRIBUTE_ACCESSORS(UProjektZAttributeSet, HealthRecovered)

        UFUNCTION()
    void OnRep_Health(const FGameplayAttributeData& OldHealth) const; // Corrected parameter name from OldMana to OldHealth

    UFUNCTION()
    void OnRep_Mana(const FGameplayAttributeData& OldMana) const;

    UFUNCTION()
    void OnRep_Stamina(const FGameplayAttributeData& OldStamina) const;

    UFUNCTION()
    void OnRep_PhysicalDamage(const FGameplayAttributeData& OldPhysicalDamage) const; 

    UFUNCTION()
    void OnRep_WeaponDamage(const FGameplayAttributeData& OldWeaponDamage) const;

    UFUNCTION()
    void OnRep_MagicPower(const FGameplayAttributeData& OldMagicPower) const; // NEW OnRep

    UFUNCTION()
    void OnRep_SpellCriticalChance(const FGameplayAttributeData& OldSpellCriticalChance) const; // NEW OnRep

    UFUNCTION()
    void OnRep_SpellCriticalDamage(const FGameplayAttributeData& OldSpellCriticalDamage) const; // NEW OnRep

    UFUNCTION()
    void OnRep_CooldownReduction(const FGameplayAttributeData& OldCooldownReduction) const; // NEW OnRep

    UFUNCTION()
    void OnRep_AttackSpeed(const FGameplayAttributeData& OldAttackSpeed) const; // NEW OnRep

    UFUNCTION()
    void OnRep_Armor(const FGameplayAttributeData& OldArmor) const;

    UFUNCTION()
    void OnRep_ArmorPenetration(const FGameplayAttributeData& OldArmorPenetration) const;

    UFUNCTION()
    void OnRep_BlockChance(const FGameplayAttributeData& OldBlockChance) const;

    UFUNCTION()
    void OnRep_CriticalHitChance(const FGameplayAttributeData& OldCriticalHitChance) const;

    UFUNCTION()
    void OnRep_CriticalHitDamage(const FGameplayAttributeData& OldCriticalHitDamage) const;

    UFUNCTION()
    void OnRep_CriticalHitResistance(const FGameplayAttributeData& OldCriticalHitResistance) const;

    UFUNCTION()
    void OnRep_HealthRegeneration(const FGameplayAttributeData& OldHealthRegeneration) const;

    UFUNCTION()
    void OnRep_ManaRegeneration(const FGameplayAttributeData& OldManaRegeneration) const;

    UFUNCTION()
    void OnRep_StaminaRegeneration(const FGameplayAttributeData& OldStaminaRegeneration) const; // NEW OnRep

    UFUNCTION()
    void OnRep_MaxMana(const FGameplayAttributeData& OldMaxMana) const;

    UFUNCTION()
    void OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth) const;

    UFUNCTION()
    void OnRep_MaxStamina(const FGameplayAttributeData& OldMaxStamina) const;

    UFUNCTION()
    void OnRep_MovementSpeed(const FGameplayAttributeData& OldMovementSpeed) const;

    UFUNCTION()
    void OnRep_FireAmplification(const FGameplayAttributeData& OldFireAmplification) const; // NEW OnRep

    UFUNCTION()
    void OnRep_FrostAmplification(const FGameplayAttributeData& OldFrostAmplification) const; // NEW OnRep

    UFUNCTION()
    void OnRep_LightningAmplification(const FGameplayAttributeData& OldLightningAmplification) const; // NEW OnRep

    UFUNCTION()
    void OnRep_LightAmplification(const FGameplayAttributeData& OldLightAmplification) const; // NEW OnRep

    UFUNCTION()
    void OnRep_PoisonAmplification(const FGameplayAttributeData& OldPoisonAmplification) const; // NEW OnRep

    UFUNCTION()
    void OnRep_OverallMagicAmplification(const FGameplayAttributeData& OldOverallMagicAmplification) const; // NEW OnRep


    UFUNCTION()
    void OnRep_FireResistance(const FGameplayAttributeData& OldFireResistance) const;

    UFUNCTION()
    void OnRep_LightningResistance(const FGameplayAttributeData& OldLightningResistance) const;

    UFUNCTION()
    void OnRep_LightResistance(const FGameplayAttributeData& OldLightResistance) const;

    UFUNCTION()
    void OnRep_FrostResistance(const FGameplayAttributeData& OldFrostResistance) const;

    UFUNCTION()
    void OnRep_PhysicalResistance(const FGameplayAttributeData& OldPhysicalResistance) const;

    UFUNCTION()
    void OnRep_PoisonResistance(const FGameplayAttributeData& OldPoisonResistance) const;

    UFUNCTION()
    void OnRep_DamageDealt(const FGameplayAttributeData& OldDamageDealt) const;

    UFUNCTION()
    void OnRep_FireDamageDealt(const FGameplayAttributeData& OldFireDamageDealt) const;

    UFUNCTION()
    void OnRep_FrostDamageDealt(const FGameplayAttributeData& OldFrostDamageDealt) const;

    UFUNCTION()
    void OnRep_LightningDamageDealt(const FGameplayAttributeData& OldLightningDamageDealt) const;

    UFUNCTION()
    void OnRep_PhysicalDamageDealt(const FGameplayAttributeData& OldPhysicalDamageDealt) const;

    UFUNCTION()
    void OnRep_PoisonDamageDealt(const FGameplayAttributeData& OldPoisonDamageDealt) const;

    UFUNCTION()
    void OnRep_LightDamageDealt(const FGameplayAttributeData& OldLightDamageDealt) const; // NEW OnRep

    UFUNCTION()
    void OnRep_DamageTanked(const FGameplayAttributeData& OldDamageTanked) const;

    UFUNCTION()
    void OnRep_HealthRecovered(const FGameplayAttributeData& OldHealthRecovered) const;
private:
private:

	void SetEffectProperties(const FGameplayEffectModCallbackData& Data, FEffectProperties& Props) const;

	void ShowFloatingText(const FEffectProperties& Props, float Damage, bool bBlockedHit, bool bCriticalHit) const;
};
