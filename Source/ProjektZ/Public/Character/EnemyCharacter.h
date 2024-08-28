// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/CharacterBase.h"
#include "Interaction/EnemyInterface.h"

#include "../UI/WidgetController/OverlayWidgetController.h"
#include <AbilitySystem/Data/CharacterClassInfo.h>

#include "BehaviorTree/BehaviorTreeComponent.h"
#include "EnemyCharacter.generated.h"


class UWidgetComponent;
class AMyAIController;
/**
 * 
 */
UCLASS()
class PROJEKTZ_API AEnemyCharacter : public ACharacterBase, public IEnemyInterface
{
	GENERATED_BODY()

public:

	AEnemyCharacter();
	virtual void PossessedBy(AController* NewController) override;

	// Enemy InterFace

	virtual void HighlightActor() override;
	virtual void UnHightlightActior() override;

	// End Enemy Interface

	// Combat Interface

	virtual int32 GetPlayerLevel() override;

	virtual void Die() override;

	virtual void SetCombatTarget_Implementation(AActor* InCombatTarget) override;
	virtual AActor* GetCombatTarget_Implementation() const override;

	

	// End Combat Interface

	UPROPERTY(BlueprintAssignable)
	FOnAttributeChangedSignature OnHealthChanged;

	UPROPERTY(BlueprintAssignable)
	FOnAttributeChangedSignature OnMaxHealthChanged;

	UPROPERTY(BlueprintReadWrite, Category = "Combat")
	TObjectPtr<AActor> CombatTarget;

protected:
	virtual void BeginPlay() override;

	void HitReactTagChanged(const FGameplayTag CallbackTag, int32 NewCount);

	virtual void InitAbilityActorInfo() override;
	virtual void InitializeDefaultAttributes() const override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character Class Defaults")
	int32 Level = 1;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character Class Defaults")
	ECharacterClass CharacterClass = ECharacterClass::Warrior;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UWidgetComponent> HealthBarWidget;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Combat")
	float LifeSpan = 5.f;

	UPROPERTY(EditAnywhere, Category = "AI")
	TObjectPtr<UBehaviorTree> BehaviorTree;

	UPROPERTY()
	TObjectPtr<AMyAIController> MyAIController;

};
