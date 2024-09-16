// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include <GameplayTagContainer.h>

#include "AbilityInfo.generated.h"


class UGameplayAbility;

USTRUCT(BlueprintType)
struct FProjektZAbilityInfo
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FGameplayTag AbilityTag = FGameplayTag();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UGameplayAbility> Ability;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FGameplayTag InputTag = FGameplayTag();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FGameplayTag CooldownTag = FGameplayTag();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UTexture2D> Icon = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UMaterialInterface> BackgroundMaterial = nullptr;
};


/**
 * 
 */
UCLASS()
class PROJEKTZ_API UAbilityInfo : public UDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="AbilityInformation")
	TArray<FProjektZAbilityInfo> AbilityInformation;


public:

	FProjektZAbilityInfo FindAbilityInfoByTag(const FGameplayTag& AbilityTag, bool bLogNotFound = false) const;
};
