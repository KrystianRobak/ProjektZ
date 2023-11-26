// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/PC_PlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include <Interaction/EnemyInterface.h>

APC_PlayerController::APC_PlayerController()
{
	bReplicates = true;
}

void APC_PlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	CursorTrace();
}

void APC_PlayerController::BeginPlay()
{
	Super::BeginPlay();
	check(PlayerContext);

	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	check(Subsystem);
	Subsystem->AddMappingContext(PlayerContext, 0);

	bShowMouseCursor = false;

	//FInputModeGameAndUI InputModeData;
	//InputModeData.SetHideCursorDuringCapture(false);
	//SetInputMode(InputModeData);
}

void APC_PlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	UEnhancedInputComponent* EnchancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);

	EnchancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &APC_PlayerController::Move);
	EnchancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &APC_PlayerController::Look);
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
	FHitResult CursorHit;
	GetHitResultUnderCursor(ECC_Visibility, false, CursorHit);
	if (!CursorHit.bBlockingHit) return;
	
	LastActor = ThisActor;
	ThisActor = Cast<IEnemyInterface>(CursorHit.GetActor());

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


