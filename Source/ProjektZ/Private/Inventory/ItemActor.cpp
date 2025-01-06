// Fill out your copyright notice in the Description page of Project Settings.


#include "Inventory/ItemActor.h"

// Sets default values
AItemActor::AItemActor()
{
	bReplicates = true;

	ItemMesh = CreateDefaultSubobject<USkeletalMeshComponent>("ItemMesh");
	ItemMesh->SetupAttachment(RootComponent);
	ItemMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

// Called when the game starts or when spawned
void AItemActor::BeginPlay()
{
	Super::BeginPlay();
	
}
