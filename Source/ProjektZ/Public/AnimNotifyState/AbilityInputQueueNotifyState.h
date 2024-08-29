// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "AbilitySystem/ProjektZAbilitySystemComponent.h"
#include "AbilityInputQueueNotifyState.generated.h"

/**
 * 
 */
UCLASS()
class PROJEKTZ_API UAbilityInputQueueNotifyState : public UAnimNotifyState
{
	GENERATED_BODY()
public:
	
	UPROPERTY(EditAnywhere)
	TArray<TSubclassOf<UGameplayAbility>> AllowedAbilities;
	
};
