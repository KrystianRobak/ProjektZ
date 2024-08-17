// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectTypes.h"
#include "ProjektZAbilityTypes.generated.h"

USTRUCT(BlueprintType)
struct FProjektZGameplayEffectContext : public FGameplayEffectContext
{
	GENERATED_BODY()

public:

	bool IsCriticaHit() const { return bIsCriticalHit; };
	bool IsBlockedHit() const { return bIsBlockedHit; };

	void SetIsCriticalHit(bool bInIsCritcalHit) { bIsCriticalHit = bInIsCritcalHit; };
	void SetIsBlockedHit(bool bInIsBlockedHit) { bIsBlockedHit = bInIsBlockedHit; };

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

