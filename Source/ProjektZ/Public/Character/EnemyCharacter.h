// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/CharacterBase.h"
#include "Interaction/EnemyInterface.h"
#include "EnemyCharacter.generated.h"

/**
 * 
 */
UCLASS()
class PROJEKTZ_API AEnemyCharacter : public ACharacterBase, public IEnemyInterface
{
	GENERATED_BODY()

public:

	AEnemyCharacter();

	// Enemy InterFace

	virtual void HighlightActor() override;
	virtual void UnHightlightActior() override;

	// End Enemy Interface

	// Combat Interface

	virtual int32 GetPlayerLevel() override;

	// End Combat Interface


protected:
	virtual void BeginPlay() override;

	virtual void InitAbilityActorInfo() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character Class Defaults")
	int32 Level = 1;
};
