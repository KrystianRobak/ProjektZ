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

protected:

	UPROPERTY(EditAnywhere, Category = "Input")
	UElementsReactionMap* ElementsReaction;

	//UPROPERTY(BlueprintReadOnly)
	//AItemGenerator ItemGenerator;
	
};
