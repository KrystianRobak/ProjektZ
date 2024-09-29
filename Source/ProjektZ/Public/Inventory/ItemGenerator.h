// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DA_BaseItem.h"

#include "ItemGenerator.generated.h"

UCLASS()
class PROJEKTZ_API AItemGenerator : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AItemGenerator();

	void GenerateItems(uint8 amount, TArray<FBaseItemInfo>& ItemContainer);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

protected:




};
