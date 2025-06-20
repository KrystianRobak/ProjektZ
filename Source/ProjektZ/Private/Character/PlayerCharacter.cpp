// Fill out your copyright notice in the Description page of Project Settings.

#include "Character/PlayerCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Player/ProjektZPlayerState.h"
#include "Player/PC_PlayerController.h"
#include <UI/HUD/ProjektZHUD.h>
#include <AbilitySystem/ProjektZAbilitySystemComponent.h>
#include "AbilitySystem/ProjektZAttributeSet.h"
#include "AbilitySystem/ProjektZAbilitySystemLibrary.h"
#include <AbilitySystem/Abilities/ProjektZGameplayAbility.h>
#include <Blueprint/WidgetLayoutLibrary.h>
#include "Components/CapsuleComponent.h"
#include <GameFramework/SpringArmComponent.h>



APlayerCharacter::APlayerCharacter()
{
	GetCharacterMovement()->bUseControllerDesiredRotation = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 400.f, 0.f);

	armComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraSpringArm"));
	armComponent->SetupAttachment(GetCapsuleComponent());
	armComponent->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, 200.0f), FRotator(0.0f, 0.0f, 0.0f));
	armComponent->TargetArmLength = 600.0f;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraMain"));
	Camera->SetupAttachment(armComponent, USpringArmComponent::SocketName);

}

void APlayerCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	//UWidgetLayoutLibrary::RemoveAllWidgets(GetWorld());
	// Init ability actor info for the Server
	InitAbilityActorInfo();
}

void APlayerCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	//UWidgetLayoutLibrary::RemoveAllWidgets(GetWorld());
	// Init ability actor info for the Client
	InitAbilityActorInfo();
}

void APlayerCharacter::Die()
{
	MulticastHandleDeath();
}

void APlayerCharacter::StunTagChanged(const FGameplayTag CallbackTag, int32 NewCount)
{
	if (NewCount > 0)
	{
		if (APC_PlayerController* ProjektZPlayerController = Cast<APC_PlayerController>(GetController()))
		{
			ProjektZPlayerController->DisableInput(ProjektZPlayerController);
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Player stunned!"));
			bInputBlocked = true;
		}

	}
	else
	{
		if (APC_PlayerController* ProjektZPlayerController = Cast<APC_PlayerController>(GetController()))
		{
			ProjektZPlayerController->EnableInput(ProjektZPlayerController);
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Player unstunned!"));
			bInputBlocked = false;
		}

	}
}

void APlayerCharacter::Downed()
{
	if (bDowned || bDead) return;

	// Disable input on controller
	if (AController* PlayerController = GetController())
	{
		PlayerController->SetIgnoreMoveInput(true);
	}

	bDowned = true;
	bDead = false;

	MulticastHandleDown();
}

void APlayerCharacter::MulticastHandleDown_Implementation()
{
	// Disable collision
	/*if (UCapsuleComponent* Capsule = GetCapsuleComponent())
		{
				Capsule->SetCollisionEnabled(ECollisionEnabled::NoCollision);
					}*/

					// Set downed status
	bDowned = true;
	bDead = false;

	// Update tags
	Tags.Remove("Player");
	Tags.Add("Downed");

	// Disable input on controller
	if (AController* PlayerController = GetController())
	{
		PlayerController->SetIgnoreMoveInput(true);
	}

	UE_LOG(LogTemp, Log, TEXT("Player character has been downed. Changes applied on server and all clients."));
}

void APlayerCharacter::MulticastHandleDeath_Implementation()
{
	// Disable collision
	if (UCapsuleComponent* Capsule = GetCapsuleComponent())
	{
		Capsule->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}

	bDowned = true;
	bDead = true;

	// Update tags
	Tags.Remove("Player");
	Tags.Add("Dead");

	// Disable input on controller
	if (AController* PlayerController = GetController())
	{
		PlayerController->SetIgnoreMoveInput(true);
	}

	UE_LOG(LogTemp, Log, TEXT("Player character has died. Changes applied on server and all clients."));
}

UCameraComponent* APlayerCharacter::GetCamera_Implementation()
{
	return Camera;
}

USpringArmComponent* APlayerCharacter::GetBoom_Implementation()
{
	return armComponent;
}

float APlayerCharacter::GetFirstFreeSlot()
{
	for (int i = 0; i < MaxAbilities; i++)
	{
		if (!SlotsOccupancy[i])
			return i;
	}
	return -1;
}

void APlayerCharacter::RemoveCharacterAbility(float Slot)
{
	if (AbilitySystemComponent && HasAuthority())
	{
		UProjektZAbilitySystemComponent* ASC = CastChecked<UProjektZAbilitySystemComponent>(AbilitySystemComponent);
		ASC->ClearAbility(Abilities[Slot].AbilitySpecHandle);
		SlotsOccupancy[Slot] = false;
	}
}

void APlayerCharacter::AddCharacterAbility(TSubclassOf<UProjektZGameplayAbility>& Ability, float Level, float Slot)
{
	if (AbilitySystemComponent && HasAuthority())
	{
		if (SlotsOccupancy[Slot])
		{
			RemoveCharacterAbility(Slot);
		}
		UProjektZAbilitySystemComponent* ASC = CastChecked<UProjektZAbilitySystemComponent>(AbilitySystemComponent);

		FAbilityData& Data = Abilities[Slot];
		ASC->AddAbility(Ability, Level, Data);
		SlotsOccupancy[Slot] = true;
	}
}

void APlayerCharacter::SwapSlotsAbilities(float Slot1, float Slot2)
{
	FAbilityData TempData = Abilities[Slot1];
	bool TempOccupancy = SlotsOccupancy[Slot1];

	Abilities[Slot1] = Abilities[Slot2];
	SlotsOccupancy[Slot1] = SlotsOccupancy[Slot2];

	Abilities[Slot2] = TempData;
	SlotsOccupancy[Slot2] = TempOccupancy;
}

int32 APlayerCharacter::GetPlayerLevel()
{
	AProjektZPlayerState* ProjektZPlayerState = GetPlayerState<AProjektZPlayerState>();
	check(ProjektZPlayerState);
	return ProjektZPlayerState->GetPlayerLevel();
}

void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	for (int i = 0; i < MaxAbilities; i++)
	{
		SlotsOccupancy.Add(false);
		Abilities.Add(FAbilityData());	
	}

	for (int i = 0; i < 10; i++)
	{
		IsItemEquipped.Add(false);
		ItemInfos.Add(FBaseItemInfo());
	}
}

void APlayerCharacter::ApplyItemEffect_Implementation(const FBaseItemInfo& ItemInfo)
{
	if (ItemInfo.ItemTypePlacement == EItemPlacement::Noone) return;

	IsItemEquipped[ItemInfo.ItemTypePlacement] = true;
	ItemInfos[ItemInfo.ItemTypePlacement] = ItemInfo;

	UProjektZAbilitySystemComponent* ASC = CastChecked<UProjektZAbilitySystemComponent>(AbilitySystemComponent);

	for (auto ability : ItemInfo.Abilities)
	{
		InventoryAbilities.Add(FAbilityData());
		FAbilityData& Data = InventoryAbilities.Last();
		ASC->AddAbility(ability, 1, Data);
	}

	UProjektZAbilitySystemLibrary::ApplyEffectFromEquippedItem(ItemInfo, AbilitySystemComponent, false);
}

void APlayerCharacter::RemoveItemEffect_Implementation(const FBaseItemInfo& ItemInfo)
{
	if (ItemInfo.ItemTypePlacement == EItemPlacement::Noone) return;

	IsItemEquipped[ItemInfo.ItemTypePlacement] = false;
	ItemInfos[ItemInfo.ItemTypePlacement] = ItemInfo;

	UProjektZAbilitySystemComponent* ASC = CastChecked<UProjektZAbilitySystemComponent>(AbilitySystemComponent);

	for (auto& ability : InventoryAbilities)
	{
		ASC->ClearAbility(ability.AbilitySpecHandle);
	}

	InventoryAbilities.Empty();

	UProjektZAbilitySystemLibrary::ApplyEffectFromEquippedItem(ItemInfo, AbilitySystemComponent, true);
}

void APlayerCharacter::SpawnItemActor_Implementation(const FBaseItemInfo& NewItemInfo)
{
	FTransform SpawnTransform;
	SpawnTransform.SetLocation(GetActorLocation());
	AItemActor* Item = GetWorld()->SpawnActorDeferred<AItemActor>(ItemActorClass, SpawnTransform, nullptr, this, ESpawnActorCollisionHandlingMethod::AlwaysSpawn);

	Item->ItemInfo = NewItemInfo;

	Item->FinishSpawning(SpawnTransform);
}

void APlayerCharacter::EquipItem(const FBaseItemInfo ItemInfo)
{
	if (!IsItemEquipped[ItemInfo.ItemTypePlacement])
	{
		IsItemEquipped[ItemInfo.ItemTypePlacement] = true;
		ItemInfos[ItemInfo.ItemTypePlacement] = ItemInfo;
		ApplyItemEffect(ItemInfo);
	}
	else
	{
		SpawnItemActor(ItemInfos[ItemInfo.ItemTypePlacement]);

		DeequipItem(ItemInfos[ItemInfo.ItemTypePlacement]);

		IsItemEquipped[ItemInfo.ItemTypePlacement] = true;
		ItemInfos[ItemInfo.ItemTypePlacement] = ItemInfo;
		ApplyItemEffect(ItemInfo);
	}

	ChangeItemMesh(ItemInfo.WeaponMesh, ItemInfo.ItemTypePlacement, ItemInfo.ItemType);
}

void APlayerCharacter::DeequipItem(const FBaseItemInfo& ItemInfo)
{
	if (ItemInfo.ItemTypePlacement == EItemPlacement::Noone) return;

	ChangeItemMesh(nullptr, ItemInfo.ItemTypePlacement, ItemInfo.ItemType);

	IsItemEquipped[ItemInfo.ItemTypePlacement] = false;
	ItemInfos[ItemInfo.ItemTypePlacement] = FBaseItemInfo();

	RemoveItemEffect(ItemInfo);
}

void APlayerCharacter::InitOverlayWidgets()
{
	AProjektZPlayerState* ProjektZPlayerState = GetPlayerState<AProjektZPlayerState>();

	if (APC_PlayerController* ProjektZPlayerController = Cast<APC_PlayerController>(GetController()))
	{
		if (AProjektZHUD* ProjektZHUD = Cast<AProjektZHUD>(ProjektZPlayerController->GetHUD()))
		{
			ProjektZHUD->InitOverlay(ProjektZPlayerController, ProjektZPlayerState, AbilitySystemComponent, AttributeSet);
		}
	}
}

void APlayerCharacter::SlowDownPlayer()
{
	GetCharacterMovement()->BrakingDecelerationWalking = 50;
}

void APlayerCharacter::InitAbilityActorInfo()
{
	AProjektZPlayerState* ProjektZPlayerState = GetPlayerState<AProjektZPlayerState>();
	check(ProjektZPlayerState);

	ProjektZPlayerState->GetAbilitySystemComponent()->InitAbilityActorInfo(ProjektZPlayerState, this);

	Cast<UProjektZAbilitySystemComponent>(ProjektZPlayerState->GetAbilitySystemComponent())->AbilityActorInfoSet();

	AbilitySystemComponent = ProjektZPlayerState->GetAbilitySystemComponent();
	AttributeSet = ProjektZPlayerState->GetAttributeSet();

	BindDelegatesToAttributes();
	if (HasAuthority())
	{
		UProjektZAbilitySystemLibrary::GiveCommonAbilitites(this, AbilitySystemComponent);
	}
	InitializeDefaultAttributes();
}


void APlayerCharacter::BindDelegatesToAttributes()
{
	UProjektZAttributeSet* PlayerAttributesSet = Cast<UProjektZAttributeSet>(AttributeSet);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(PlayerAttributesSet->GetMovementSpeedAttribute()).AddLambda(
		[this](const FOnAttributeChangeData& Data)
		{
			GetCharacterMovement()->MaxWalkSpeed = Data.NewValue;
		}
	);
}


