// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "ItemDescriptor.generated.h"


struct FGameplayAttribute;

USTRUCT(BlueprintType)
struct FItemDescriptorPS
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	FString DescriptorName;

	UPROPERTY(EditAnywhere)
	TArray<FGameplayAttribute> EffectModifiers;
};

/**
 * 
 */
UCLASS()
class PROJEKTZ_API UItemDescriptor : public UDataAsset
{
	GENERATED_BODY()
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "ItemInformation")
	TArray<FItemDescriptorPS> PrefixInfo;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "ItemInformation")
	TArray<FItemDescriptorPS> SuffixInfo;
};
