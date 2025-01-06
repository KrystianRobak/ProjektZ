// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "../Interaction/ReactiveInterface.h"
#include "ReactiveActor.generated.h"

UCLASS()
class PROJEKTZ_API AReactiveActor : public AActor, public IReactiveInterface 
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AReactiveActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Element")
	FGameplayTag Element;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Element")
	bool bHasReacted;

public:

	void SetReacted_Implementation(bool value);

	bool HasReacted_Implementation();

	FGameplayTag GetElementTag_Implementation();
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:


};
