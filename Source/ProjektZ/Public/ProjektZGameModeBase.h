// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "NiagaraFunctionLibrary.h"
#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Inventory/DA_BaseItem.h"
#include "Inventory/ItemDescriptor.h"
#include "ProjektZGameModeBase.generated.h"

class UCharacterClassInfo;
/**
 * 
 */
UCLASS()
class PROJEKTZ_API AProjektZGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

	AActor GenerateRandomLoot();

	UFUNCTION(BlueprintCallable)
	TArray<FBaseItemInfo> GenerateItemsToDrop(int amount);


public:
	UPROPERTY(EditDefaultsOnly, Category = "Character Class Defaults")
	TObjectPtr<UCharacterClassInfo> CharacterClassInfo;

	UPROPERTY(EditDefaultsOnly, Category = "Item Defaults")
	TObjectPtr<UDA_PrimaryItemInfo> PrimaryIteminfo;

	UPROPERTY(EditDefaultsOnly, Category = "Item Defaults")
	TObjectPtr<UItemDescriptor> ItemDescriptorInfo;

	/* RANDOM ITEM GENERATOR VARIABLE SECTION */

	int StageBonus;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Levels")
	int32 Progress = 0;


	TArray<int> GradeBonuses;

	TArray<int> GradeCapsForModifiers;
};
