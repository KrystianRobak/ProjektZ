// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "AbilitySystem/Data/ElementsReactionMap.h"
#include "Inventory/ItemGenerator.h"
#include "ProjektZGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class PROJEKTZ_API UProjektZGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UElementsReactionMap* GetElementsReaction()
	{
		return this->ElementsReaction;
	}

	TSubclassOf<UGameplayEffect> GetGameplayElementsTagApplier()
	{
		return this->ElementsTagApplier;
	}
protected:

	UPROPERTY(EditAnywhere, Category = "Input")
	UElementsReactionMap* ElementsReaction;

	UPROPERTY(EditAnywhere, Category = "Input")
	TSubclassOf<UGameplayEffect> ElementsTagApplier;

	//UPROPERTY(BlueprintReadOnly)
	//AItemGenerator ItemGenerator;
	
};
