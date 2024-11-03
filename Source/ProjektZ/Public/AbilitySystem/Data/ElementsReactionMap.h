// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "ProjektZGameplayTags.h"
#include "ElementsReactionMap.generated.h"


USTRUCT(BlueprintType)
struct FElementInfo
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FGameplayTag ElementTag = FGameplayTag();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FGameplayTagContainer ReactionElementTags;

};


UCLASS()
class PROJEKTZ_API UElementsReactionMap : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AbilityInformation")
	TArray<FElementInfo> ElementsInformation;

	bool IsTagReactive(FGameplayTag MainTag, FGameplayTagContainer TagsToCheck);

};
