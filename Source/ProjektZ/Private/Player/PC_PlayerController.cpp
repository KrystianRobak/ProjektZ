// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/PC_PlayerController.h"
#include "EnhancedInputSubsystems.h"
#include <Interaction/EnemyInterface.h>
#include "AbilitySystemBlueprintLibrary.h"
#include <Input/ProjektZInputComponent.h>
#include "GameFramework/Character.h"
#include "UI/Widget/DamageTextComponent.h"
#include "TimerManager.h"
#include "GameFramework/CharacterMovementComponent.h"

APC_PlayerController::APC_PlayerController()
{
	bReplicates = true;
}

void APC_PlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	CursorTrace();
}

void APC_PlayerController::ShowDamageNumber_Implementation(float DamageAmount, ACharacter* TargetCharacter)
{
	if (IsValid(TargetCharacter) && DamageTextComponentClass)
	{
		UDamageTextComponent* DamageText = NewObject<UDamageTextComponent>(TargetCharacter, DamageTextComponentClass);
		DamageText->RegisterComponent();
		DamageText->AttachToComponent(TargetCharacter->GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);
		DamageText->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);
		DamageText->SetDamageText(DamageAmount);
	}
}



void APC_PlayerController::SetUpASCDependentInput(UAbilitySystemComponent* ASC)
{
	
}

void APC_PlayerController::BeginPlay()
{
	Super::BeginPlay();

	check(PlayerContext);

	PlayerCharacter = Cast<APlayerCharacter>(GetPawn());

	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());

	if (Subsystem) 
	{
		Subsystem->AddMappingContext(PlayerContext, 0);
	}
	
	bShowMouseCursor = false;

	UProjektZInputComponent* ProjektZInputComponent = Cast<UProjektZInputComponent>(InputComponent);
	if (UAbilitySystemComponent* Asc = GetASC())
	{
		ProjektZInputComponent->BindAction(ConfirmTargeting, ETriggerEvent::Triggered, Asc, &UAbilitySystemComponent::LocalInputConfirm);
		ProjektZInputComponent->BindAction(CancelTargeting, ETriggerEvent::Triggered, Asc, &UAbilitySystemComponent::LocalInputCancel);
	}
}

//void APC_PlayerController::SetupInputComponent()
//{
//	Super::SetupInputComponent();
//	UProjektZInputComponent* ProjektZInputComponent = CastChecked<UProjektZInputComponent>(InputComponent);
//
//
//	ProjektZInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &APC_PlayerController::Move);
//	ProjektZInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &APC_PlayerController::Look);
//	
//	ProjektZInputComponent->BindAbilityActions(InputConfig, this, &ThisClass::AbilityInputTagPressed, &ThisClass::AbilityInputTagReleased, &ThisClass::AbilityInputTagHeld);
//}

void APC_PlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	// The CRITICAL FIX: Ensure InputComponent is UProjektZInputComponent
	UProjektZInputComponent* ProjektZInputComponent = Cast<UProjektZInputComponent>(InputComponent);

	if (!ProjektZInputComponent)
	{
		// If InputComponent is NOT already a UProjektZInputComponent (which is the default for APlayerController)
		// We create a new one and assign it.
		ProjektZInputComponent = NewObject<UProjektZInputComponent>(this, UProjektZInputComponent::StaticClass(), TEXT("PlayerControllerCustomInputComponent"));
		if (ProjektZInputComponent)
		{
			InputComponent = ProjektZInputComponent; // Assign the newly created custom input component
			ProjektZInputComponent->RegisterComponent(); // Important: Register the component to make it active
			UE_LOG(LogTemp, Log, TEXT("APC_PlayerController: Successfully created and set UProjektZInputComponent."));
		}
		else
		{
			// This indicates a severe issue, the game might not be playable without proper input
			UE_LOG(LogTemp, Error, TEXT("APC_PlayerController: FAILED to create UProjektZInputComponent!"));
			return; // Exit if we can't set up the input component
		}
	}
	else
	{
		// This log is for debugging purposes, in case it was already the correct type (e.g. from an existing blueprint)
		UE_LOG(LogTemp, Log, TEXT("APC_PlayerController: InputComponent was already UProjektZInputComponent."));
	}

	// Now that we are sure ProjektZInputComponent is valid and of the correct type, bind actions
	// These are general movement and look inputs
	ProjektZInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &APC_PlayerController::Move);
	ProjektZInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &APC_PlayerController::Look);

	// These bindings use your custom BindAbilityActions for Gameplay Abilities
	ProjektZInputComponent->BindAbilityActions(InputConfig, this, &ThisClass::AbilityInputTagPressed, &ThisClass::AbilityInputTagReleased, &ThisClass::AbilityInputTagHeld);
}

void APC_PlayerController::OnPossess(APawn* aPawn)
{
	Super::OnPossess(aPawn);
}

void APC_PlayerController::Move(const FInputActionValue& InputActionValue)
{
	const FVector2D MoveVectorValue = InputActionValue.Get<FVector2D>();

	APawn* ControlledPawn = GetPawn<APawn>();

	const FRotator Rotation = ControlledPawn->GetControlRotation();
	const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);

	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	ControlledPawn->AddMovementInput(ForwardDirection, MoveVectorValue.Y);
	ControlledPawn->AddMovementInput(RightDirection, MoveVectorValue.X);

}

void APC_PlayerController::Look(const FInputActionValue& Value)
{
	const FVector2D LookAxisValue = Value.Get<FVector2D>();

	if (APawn* ControlledPawn = GetPawn<APawn>()) {
		ControlledPawn->AddControllerYawInput(-LookAxisValue.X);
		ControlledPawn->AddControllerPitchInput(LookAxisValue.Y);
	}
}

void APC_PlayerController::CursorTrace()
{
	FHitResult CameraHit;

	FInt32Vector2 ViewPoint;
	//FRotator ViewRotation;
	GetViewportSize(ViewPoint.X, ViewPoint.Y);

	ViewPoint.X = ViewPoint.X / 2;
	ViewPoint.Y = ViewPoint.Y / 2;

	FVector WorldPosition, WorldDirection;
	DeprojectScreenPositionToWorld(ViewPoint.X, ViewPoint.Y, WorldPosition, WorldDirection);



	GetWorld()->LineTraceSingleByChannel(CameraHit, WorldPosition, WorldPosition + WorldDirection * 500000.f, ECC_Visibility);

	if (!CameraHit.bBlockingHit) return;
	
	LastActor = ThisActor;
	ThisActor = Cast<IEnemyInterface>(CameraHit.GetActor());

	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, CameraHit.GetActor()->GetName());

	if (LastActor == nullptr)
	{
		if (ThisActor != nullptr)
		{
			ThisActor->HighlightActor();
		}
	}
	else
	{
		if (ThisActor == nullptr) 
		{
			LastActor->UnHightlightActior();
		}
		else
		{
			if (LastActor != ThisActor)
			{
				LastActor->UnHightlightActior();
				ThisActor->HighlightActor();
			}
		}
	}
}

void APC_PlayerController::AbilityInputTagPressed(FGameplayTag InputTag)
{
	if (GetASC() == nullptr) return;

	if (PlayerCharacter->GetAbilityQueueWindowStatus())
	{
		PlayerCharacter->CheckAndUpdateAbilityQueue(GetASC()->GetAbilityTagByInputTag(InputTag));
	}
	else
	{
		if (PlayerCharacter->IsInputBlocked()) return;
		GetASC()->AbilityInputTagPressed(InputTag);
	}
}

void APC_PlayerController::AbilityInputTagReleased(FGameplayTag InputTag)
{
	if (GetASC() == nullptr) return;

	if (PlayerCharacter->GetAbilityQueueWindowStatus())
	{
		PlayerCharacter->CheckAndUpdateAbilityQueue(GetASC()->GetAbilityTagByInputTag(InputTag));
	}
	else
	{ 
		if (PlayerCharacter->IsInputBlocked()) return;
		GetASC()->AbilityInputTagReleased(InputTag);
	}
}

void APC_PlayerController::AbilityInputTagHeld(FGameplayTag InputTag)
{
	if (GetASC() == nullptr) return;
	
	if (PlayerCharacter->GetAbilityQueueWindowStatus())
	{
		PlayerCharacter->CheckAndUpdateAbilityQueue(GetASC()->GetAbilityTagByInputTag(InputTag));
	}
	else
	{
		if (PlayerCharacter->IsInputBlocked()) return;
		GetASC()->AbilityInputTagHeld(InputTag);
	}
}

UProjektZAbilitySystemComponent* APC_PlayerController::GetASC()
{
	if (ProjektZAbilitySystemComponent == nullptr)
	{
		ProjektZAbilitySystemComponent = Cast<UProjektZAbilitySystemComponent>(UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetPawn<APawn>()));
	}
	return ProjektZAbilitySystemComponent;
}

void APC_PlayerController::BP_GetOwnedGameplayTags(FGameplayTagContainer& TagContainer) const
{
	TagContainer.Reset();
	TagContainer = ProjektZAbilitySystemComponent->GetOwnedGameplayTags();
}
