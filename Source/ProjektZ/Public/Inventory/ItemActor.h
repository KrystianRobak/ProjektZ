// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DA_BaseItem.h"
#include "Components/SphereComponent.h"
#include "ItemActor.generated.h"

UCLASS()
class PROJEKTZ_API AItemActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AItemActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FBaseItemInfo ItemInfo;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TObjectPtr<USkeletalMeshComponent> ItemMesh;
};
