// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectTypes.h"
#include <GameplayEffect.h>
#include "ProjektZAbilityTypes.generated.h"

USTRUCT()
struct FEffectParams
{
	GENERATED_USTRUCT_BODY()

	FEffectParams() {}

	UPROPERTY(EditAnywhere)
	FGameplayTag EffectType;

	UPROPERTY(EditAnywhere)
	float EffectChance = 0.f;

	UPROPERTY(EditAnywhere)
	float EffectMagnitude = 0.f;

	UPROPERTY(EditAnywhere)
	float EffectFrequency = 0.f;

	UPROPERTY(EditAnywhere)
	float EffectDuration = 0.f;

	float GetEffectDamage() const { return EffectMagnitude; };
	float GetEffectDuration() const { return EffectDuration; };
	float GetEffectFrequency() const { return EffectFrequency; };

	FGameplayTag GetEffectType() const { return EffectType.IsValid() ? EffectType : FGameplayTag(); };

	void SetEffectDamage(float InEffectMagnitude)  { EffectMagnitude = InEffectMagnitude; };
	void SetEffectDuration(float InEffectDuration)  { EffectDuration = InEffectDuration; };
	void SetEffectFrequency(float InEffectFrequency)  { EffectFrequency = InEffectFrequency; };

	void SetEffectType(FGameplayTag InTag)  { EffectType = InTag; };


	void NetSerialize(FArchive& Ar, class UPackageMap* Map, bool& bOutSuccess) {
		Ar << EffectMagnitude;
		Ar << EffectDuration;
		Ar << EffectFrequency;
		if (Ar.IsLoading())
		{
			if (!EffectType.IsValid())
			{
				EffectType = FGameplayTag();
			}
		}
		EffectType.NetSerialize(Ar, Map, bOutSuccess);
	};
	
};


USTRUCT(BlueprintType)
struct FDamageEffectParams
{
	GENERATED_BODY()

	FDamageEffectParams() {}

	UPROPERTY()
	TObjectPtr<UObject> WorldContextObject = nullptr;

	UPROPERTY()
	TSubclassOf<UGameplayEffect> DamageGameplayEffectClass = nullptr;

	UPROPERTY()
	TObjectPtr<UAbilitySystemComponent> SourceAbilitySystemComponent;

	UPROPERTY()
	TObjectPtr<UAbilitySystemComponent> TargetAbilitySystemComponent;

	UPROPERTY()
	float BaseDamage = 0.f;

	UPROPERTY()
	float AbilityLevel = 1.f;

	UPROPERTY()
	FGameplayTag DamageType = FGameplayTag();
};


USTRUCT(BlueprintType)
struct FProjektZGameplayEffectContext : public FGameplayEffectContext
{
	GENERATED_BODY()

public:

	bool IsCriticaHit() const { return bIsCriticalHit; };
	bool IsBlockedHit() const { return bIsBlockedHit; };
	bool IsSuccessfullDebuff() const { return bIsSuccessfulDebuff; };

	bool SetContextEffects(TArray<FEffectParams> InEffects)
	{
		for (auto Effect : InEffects)
		{
			Effects.Add(MakeShared<FEffectParams>(Effect));
		}
	};

	TArray<FEffectParams> GetContextEffects() const
	{
		TArray<FEffectParams> OutEffects;
		for (TSharedPtr<FEffectParams> Effect : Effects)
		{
			OutEffects.Add(*Effect);
		}
		return OutEffects;
	}

	void SetIsCriticalHit(bool bInIsCritcalHit) { bIsCriticalHit = bInIsCritcalHit; };
	void SetIsBlockedHit(bool bInIsBlockedHit) { bIsBlockedHit = bInIsBlockedHit; };
	void SetIsSuccessfullDebuff(bool bInIsSuccessfulDebuff) { bIsSuccessfulDebuff = bInIsSuccessfulDebuff; };

	virtual UScriptStruct* GetScriptStruct() const override
	{
		return StaticStruct();
	}

	virtual FProjektZGameplayEffectContext* Duplicate() const
	{
		FProjektZGameplayEffectContext* NewContext = new FProjektZGameplayEffectContext();
		*NewContext = *this;
		if (GetHitResult())
		{
			// Does a deep copy of the hit result
			NewContext->AddHitResult(*GetHitResult(), true);
		}
		return NewContext;
	}

	/** Custom serialization, subclasses must override this */
	virtual bool NetSerialize(FArchive& Ar, class UPackageMap* Map, bool& bOutSuccess) override;

protected:

	UPROPERTY()
	bool bIsCriticalHit = false;

	UPROPERTY()
	bool bIsBlockedHit = false;

	UPROPERTY()
	bool bIsSuccessfulDebuff = false;

	UPROPERTY()
	uint8 DebuffsAmount = 0;

	TArray<TSharedPtr<FEffectParams>> Effects;
};

template<>
struct TStructOpsTypeTraits<FProjektZGameplayEffectContext> : public TStructOpsTypeTraitsBase2<FProjektZGameplayEffectContext>
{
	enum
	{
		WithNetSerializer = true,
		WithCopy = true
	};
};

