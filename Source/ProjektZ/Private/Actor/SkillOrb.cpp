// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/SkillOrb.h"
#include <Character/PlayerCharacter.h>

// Sets default values
ASkillOrb::ASkillOrb()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	SetRootComponent(CreateDefaultSubobject<USceneComponent>("SceneRoot"));
}

// Called when the game starts or when spawned
void ASkillOrb::BeginPlay()
{
	Super::BeginPlay();
	
}

void ASkillOrb::GiveAbilityToTarget(AActor* TargetActor)
{
	if (APlayerCharacter* Target = Cast<APlayerCharacter>(TargetActor))
	{
		float Slot = Target->GetFirstFreeSlot();
		if (Slot == -1)
		{
			return;
		}
		Target->AddCharacterAbility(Ability, Level, Slot);
	}
	this->Destroy();
}

// Called every frame
void ASkillOrb::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

