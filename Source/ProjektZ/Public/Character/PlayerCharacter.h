// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/CharacterBase.h"
#include "PlayerCharacter.generated.h"

/**
 * 
 */
UCLASS()
class PROJEKTZ_API APlayerCharacter : public ACharacterBase
{
	GENERATED_BODY()
public:
	APlayerCharacter();
	virtual void PossessedBy(AController* NewController) override;
	virtual void OnRep_PlayerState() override;

	UFUNCTION(BlueprintCallable)
	float GetFirstFreeSlot();

	UFUNCTION(BlueprintCallable)
	void AddCharacterAbility(TSubclassOf<UGameplayAbility>& Ability, float Level, float Slot);

	UFUNCTION(BlueprintCallable)
	void SwapSlotsAbilities(float Slot1, float Slot2);

	UFUNCTION(BlueprintCallable)
	void RemoveCharacterAbility(float Slot);

	// Combat Interface

	virtual int32 GetPlayerLevel() override;

	// End Combat Interface

	void virtual BeginPlay() override;

protected:

	UPROPERTY(EditAnywhere, Category = "Abilities")
	float MaxAbilities;

	UPROPERTY(BlueprintReadOnly, Category = "Abilities")
	float CurrentAbilities;

	UPROPERTY(EditAnywhere, Category = "Abilities")
	TArray<FAbilityData> Abilities;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Abilities")
	TArray<bool> SlotsOccupancy;

private:
	virtual void InitAbilityActorInfo() override;
	
};
