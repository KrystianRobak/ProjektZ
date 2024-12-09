// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Character/PlayerCharacter.h"
#include "GameplayTagContainer.h"
#include "../AbilitySystem/ProjektZAbilitySystemComponent.h"
#include "PC_PlayerController.generated.h"

class UInputMappingContext;
class UInputAction;
struct FInputActionValue;
class IEnemyInterface;
class UProjektZInputConfig;
class UDamageTextComponent;

/**
 * 
 */

UCLASS()
class PROJEKTZ_API APC_PlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	APC_PlayerController();
	virtual void PlayerTick(float DeltaTime) override;

	UFUNCTION(Client, Reliable)
	void ShowDamageNumber(float DamageAmount, ACharacter* TargetCharacter);

	void SetUpASCDependentInput(UAbilitySystemComponent* ASC);

	UProjektZAbilitySystemComponent* GetASC();


protected:

	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;
	virtual void OnPossess(APawn* aPawn) override;


private:
	void Move(const FInputActionValue& InputActionValue);

	void Look(const FInputActionValue& InputActionValue);

	void CursorTrace();

	UFUNCTION(BlueprintCallable)
	void AbilityInputTagPressed(FGameplayTag InputTag);

	UFUNCTION(BlueprintCallable)
	void AbilityInputTagReleased(FGameplayTag InputTag);

	UFUNCTION(BlueprintCallable)
	void AbilityInputTagHeld(FGameplayTag InputTag);

	UFUNCTION(BlueprintCallable, Category = "Tags")
	void BP_GetOwnedGameplayTags(FGameplayTagContainer& TagContainer) const;

private:

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputMappingContext> PlayerContext;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> MoveAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> LookAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> CancelTargeting;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> ConfirmTargeting;

	UPROPERTY(EditAnywhere, Category = "Controller")
	float SensitivityScale = 1;

	IEnemyInterface* LastActor;
	IEnemyInterface* ThisActor;

	UPROPERTY(EditDefaultsOnly, Category="Input")
	TObjectPtr<UProjektZInputConfig> InputConfig;

	//UPROPERTY(EditDefaultsOnly, Category = "BasicInput")
	//TObjectPtr<UProjektZInputConfig> BasicInputConfig;

	UPROPERTY()
	TObjectPtr<UProjektZAbilitySystemComponent> ProjektZAbilitySystemComponent;

	UPROPERTY()
	FGameplayTagContainer CharacterTags;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UDamageTextComponent> DamageTextComponentClass;

	UPROPERTY()
	TObjectPtr<APlayerCharacter> PlayerCharacter;

	UPROPERTY(EditDefaultsOnly)
	bool IsInAbilityInputQueueWindow = false;

	FTimerHandle TimeHandle;
}; 
