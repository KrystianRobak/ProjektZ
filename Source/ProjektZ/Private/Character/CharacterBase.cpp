#include "Character/CharacterBase.h"


ACharacterBase::ACharacterBase()
{
	PrimaryActorTick.bCanEverTick = true;

	Weapon = CreateDefaultSubobject<USkeletalMeshComponent>("Weapon");
	Weapon->SetupAttachment(GetMesh(), FName("WeaponHandSocket"));
	Weapon->SetCollisionEnabled(ECollisionEnabled::NoCollision);

}

void ACharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}


