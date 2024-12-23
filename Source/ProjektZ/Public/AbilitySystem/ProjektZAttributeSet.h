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
	 *	Primary Attributes
	 */
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Strength, Category = "Primary Attributes")
	FGameplayAttributeData Strength;
	ATTRIBUTE_ACCESSORS(UProjektZAttributeSet, Strength)

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Intelligence, Category = "Primary Attributes")
	FGameplayAttributeData Intelligence;
	ATTRIBUTE_ACCESSORS(UProjektZAttributeSet, Intelligence)

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Resilience, Category = "Primary Attributes")
	FGameplayAttributeData Resilience;
	ATTRIBUTE_ACCESSORS(UProjektZAttributeSet, Resilience)
	 
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Vigor, Category = "Primary Attributes")
	FGameplayAttributeData Vigor;
	ATTRIBUTE_ACCESSORS(UProjektZAttributeSet, Vigor)

	 /*
	 *	Meta Attributes
	 */

	UPROPERTY(BlueprintReadOnly, Category = "Meta Attributes")
	FGameplayAttributeData IncomingDamage;
	ATTRIBUTE_ACCESSORS(UProjektZAttributeSet, IncomingDamage)

	 /*
	  *	Secondary Attributes
	  */

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_WeaponDamage, Category = "Secondary Attributes")
	FGameplayAttributeData WeaponDamage;
	ATTRIBUTE_ACCESSORS(UProjektZAttributeSet, WeaponDamage)

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Armor, Category = "Secondary Attributes")
	FGameplayAttributeData Armor;
	ATTRIBUTE_ACCESSORS(UProjektZAttributeSet, Armor)

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_ArmorPenetration, Category = "Secondary Attributes")
	FGameplayAttributeData ArmorPenetration;
	ATTRIBUTE_ACCESSORS(UProjektZAttributeSet, ArmorPenetration)

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_BlockChance, Category = "Secondary Attributes")
	FGameplayAttributeData BlockChance;
	ATTRIBUTE_ACCESSORS(UProjektZAttributeSet, BlockChance)

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_CriticalHitChance, Category = "Secondary Attributes")
	FGameplayAttributeData CriticalHitChance;
	ATTRIBUTE_ACCESSORS(UProjektZAttributeSet, CriticalHitChance)

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_CriticalHitDamage, Category = "Secondary Attributes")
	FGameplayAttributeData CriticalHitDamage;
	ATTRIBUTE_ACCESSORS(UProjektZAttributeSet, CriticalHitDamage)

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_CriticalHitResistance, Category = "Secondary Attributes")
	FGameplayAttributeData CriticalHitResistance;
	ATTRIBUTE_ACCESSORS(UProjektZAttributeSet, CriticalHitResistance)

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_HealthRegeneration, Category = "Secondary Attributes")
	FGameplayAttributeData HealthRegeneration;
	ATTRIBUTE_ACCESSORS(UProjektZAttributeSet, HealthRegeneration)

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_ManaRegeneration, Category = "Secondary Attributes")
	FGameplayAttributeData ManaRegeneration;
	ATTRIBUTE_ACCESSORS(UProjektZAttributeSet, ManaRegeneration)
		
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxHealth, Category = "Secondary Attributes")
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(UProjektZAttributeSet, MaxHealth)

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxMana, Category = "Secondary Attributes")
	FGameplayAttributeData MaxMana;
	ATTRIBUTE_ACCESSORS(UProjektZAttributeSet, MaxMana)

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MovementSpeed, Category = "Secondary Attributes")
	FGameplayAttributeData MovementSpeed;
	ATTRIBUTE_ACCESSORS(UProjektZAttributeSet, MovementSpeed)

	 /*
	 *  Secondary Attributes
	 */

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_FireResistance, Category = "Secondary Attributes")
	FGameplayAttributeData FireResistance;
	ATTRIBUTE_ACCESSORS(UProjektZAttributeSet, FireResistance)

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_FrostResistance, Category = "Secondary Attributes")
	FGameplayAttributeData FrostResistance;
	ATTRIBUTE_ACCESSORS(UProjektZAttributeSet, FrostResistance)

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_LightningResistance, Category = "Secondary Attributes")
	FGameplayAttributeData LightningResistance;
	ATTRIBUTE_ACCESSORS(UProjektZAttributeSet, LightningResistance)

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_PhysicalResistance, Category = "Secondary Attributes")
	FGameplayAttributeData PhysicalResistance;
	ATTRIBUTE_ACCESSORS(UProjektZAttributeSet, PhysicalResistance)

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_PoisonResistance, Category = "Secondary Attributes")
	FGameplayAttributeData PoisonResistance;
	ATTRIBUTE_ACCESSORS(UProjektZAttributeSet, PoisonResistance)

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_LightResistance, Category = "Secondary Attributes")
	FGameplayAttributeData LightResistance;
	ATTRIBUTE_ACCESSORS(UProjektZAttributeSet, LightResistance)
		

	 /*
	  *	Vital Attributes
	  */

	UPROPERTY(BlueprintReadOnly,ReplicatedUsing = OnRep_Health, Category = "Vital Attributes")
	FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS(UProjektZAttributeSet, Health)

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Mana, Category = "Vital Attributes")
	FGameplayAttributeData Mana;
	ATTRIBUTE_ACCESSORS(UProjektZAttributeSet, Mana)

	 /*
	  *	Stat Tracking
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


	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_DamageTanked, Category = "Stats Tracker")
	FGameplayAttributeData DamageTanked;
	ATTRIBUTE_ACCESSORS(UProjektZAttributeSet, DamageTanked)


	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_HealthRecovered, Category = "Stats Tracker")
	FGameplayAttributeData HealthRecovered;
	ATTRIBUTE_ACCESSORS(UProjektZAttributeSet, HealthRecovered)

	UFUNCTION()
	void OnRep_Health(const FGameplayAttributeData& OldMana) const;

	UFUNCTION()
	void OnRep_Mana(const FGameplayAttributeData& OldMana) const;

	UFUNCTION()
	void OnRep_Strength(const FGameplayAttributeData& OldStrength) const;

	UFUNCTION()
	void OnRep_Intelligence(const FGameplayAttributeData& OldIntelligence) const;
	
	UFUNCTION()
	void OnRep_Resilience(const FGameplayAttributeData& OldResilience) const;

	UFUNCTION()
	void OnRep_Vigor(const FGameplayAttributeData& OldVigor) const;

	UFUNCTION()
	void OnRep_WeaponDamage(const FGameplayAttributeData& OldWeaponDamage) const;

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
	void OnRep_MaxMana(const FGameplayAttributeData& OldMaxMana) const;

	UFUNCTION()
	void OnRep_MovementSpeed(const FGameplayAttributeData& OldMovementSpeed) const;

	UFUNCTION()
	void OnRep_MaxHealth(const FGameplayAttributeData& OldMaxMana) const;

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
	void OnRep_DamageTanked(const FGameplayAttributeData& OldDamageTanked) const;

	UFUNCTION()
	void OnRep_HealthRecovered(const FGameplayAttributeData& OldHealthRecovered) const;
private:

	void SetEffectProperties(const FGameplayEffectModCallbackData& Data, FEffectProperties& Props) const;

	void ShowFloatingText(const FEffectProperties& Props, float Damage, bool bBlockedHit, bool bCriticalHit) const;
};
