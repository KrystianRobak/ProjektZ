// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "NiagaraFunctionLibrary.h"
#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ProjektZGameModeBase.generated.h"

class UCharacterClassInfo;
/**
 * 
 */
UCLASS()
class PROJEKTZ_API AProjektZGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, Category = "Character Class Defaults")
	TObjectPtr<UCharacterClassInfo> CharacterClassInfo;
};
