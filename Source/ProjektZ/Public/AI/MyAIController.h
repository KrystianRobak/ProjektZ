// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "MyAIController.generated.h"

class UBlackboardComponent;
class UBehaviorTreeComponent;



/**
 * 
 */
UCLASS()
class PROJEKTZ_API AMyAIController : public AAIController
{
	GENERATED_BODY()

public:
	AMyAIController();

protected:

	UPROPERTY()
	TObjectPtr<UBehaviorTreeComponent> BehaviorTreeComponent;
};
