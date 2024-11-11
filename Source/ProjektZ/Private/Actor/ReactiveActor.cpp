// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/ReactiveActor.h"

// Sets default values
AReactiveActor::AReactiveActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AReactiveActor::BeginPlay()
{
	Super::BeginPlay();
	
}

void AReactiveActor::SetReacted_Implementation(bool value)
{
	this->bHasReacted = value;
}

bool AReactiveActor::HasReacted_Implementation()
{
	return this->bHasReacted;
}

FGameplayTag AReactiveActor::GetElementTag_Implementation()
{
	return this->Element;
}

// Called every frame
void AReactiveActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

