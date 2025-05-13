// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/CharacterBase.h"
#include "Inventory/DA_BaseItem.h"
#include <Inventory/ItemActor.h>
#include "Interaction/PlayerInterface.h"
#include <Camera/CameraComponent.h>
#include "PlayerCharacter.generated.h"


/**
 * 
 */

class UOverlayWidgetController;

UCLASS()
class PROJEKTZ_API APlayerCharacter : public ACharacterBase, public IPlayerInterface
{
	GENERATED_BODY()
public:
	APlayerCharacter();
	virtual void PossessedBy(AController* NewController) override;
	virtual void OnRep_PlayerState() override;

	virtual void Die() override;

	virtual void StunTagChanged(const FGameplayTag CallbackTag, int32 NewCount) override;

	virtual void MulticastHandleDeath_Implementation() override;

	virtual UCameraComponent* GetCamera_Implementation() override;

	virtual USpringArmComponent* GetBoom_Implementation() override;

	UFUNCTION(BlueprintCallable)
	float GetFirstFreeSlot();

	UFUNCTION(BlueprintCallable)
	bool GetAbilityQueueWindowStatus() { return IsInActiveAbilityWindowQueue; };

	UFUNCTION(BlueprintCallable)
	bool IsInputBlocked() { return bInputBlocked; };

	UFUNCTION(BlueprintCallable)
	void AddCharacterAbility(TSubclassOf<UProjektZGameplayAbility>& Ability, float Level, float Slot);

	UFUNCTION(BlueprintCallable)
	void SwapSlotsAbilities(float Slot1, float Slot2);

	UFUNCTION(BlueprintCallable)
	void RemoveCharacterAbility(float Slot);

	UFUNCTION(BlueprintImplementableEvent, Category = "AI")
	void CheckAndUpdateAbilityQueue(FGameplayTag InAbilityTag);

	// Combat Interface

	virtual int32 GetPlayerLevel() override;

	// End Combat Interface

	void virtual BeginPlay() override;




	UFUNCTION(Server, Reliable)
	void ApplyItemEffect(const FBaseItemInfo& ItemInfo);

	UFUNCTION(Server, Reliable)
	void RemoveItemEffect(const FBaseItemInfo& ItemInfo);

	UFUNCTION(BlueprintCallable, Server, Reliable)
	void SpawnItemActor(const FBaseItemInfo& NewItemInfo);

	UFUNCTION(BlueprintCallable)
	void EquipItem(const FBaseItemInfo ItemInfo);

	UFUNCTION(BlueprintCallable)
	void DeequipItem(const FBaseItemInfo& ItemInfo);

	UFUNCTION(BlueprintCallable)
	void InitOverlayWidgets();

	UFUNCTION(BlueprintImplementableEvent)
	void ChangeItemMesh(const USkeletalMesh* ItemMesh, EItemPlacement ItemPlacement, EItemType ItemType);

	void SlowDownPlayer();


protected:

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Combat")
	TObjectPtr<UCameraComponent> Camera;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Combat")
	TObjectPtr<USpringArmComponent> armComponent;

	UPROPERTY(BlueprintReadOnly, Category = "InventorySystem")
	TArray<bool> IsItemEquipped;

	UPROPERTY(BlueprintReadOnly, Category = "InventorySystem")
	TArray<FBaseItemInfo> ItemInfos;

	UPROPERTY(EditAnywhere, Category = "Abilities")
	float MaxAbilities;

	UPROPERTY(BlueprintReadOnly, Category = "Abilities")
	float CurrentAbilities;

	UPROPERTY(EditAnywhere, Category = "Abilities")
	TArray<FAbilityData> Abilities;

	UPROPERTY(EditAnywhere, Category = "Abilities")
	TArray<FAbilityData> InventoryAbilities;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Abilities")
	TArray<bool> SlotsOccupancy;

	UPROPERTY(BlueprintReadWrite, Category = "AbilityInputQueue", meta = (AllowPrivateAccess = "true"))
	bool IsInActiveAbilityWindowQueue = false;

	UPROPERTY(BlueprintReadWrite, Category = "AbilityInputQueue", meta = (AllowPrivateAccess = "true"))
	bool bInputBlocked = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<AItemActor> ItemActorClass;

private:
	virtual void InitAbilityActorInfo() override;

	void BindDelegatesToAttributes();
	
};
