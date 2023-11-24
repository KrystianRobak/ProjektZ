// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/PC_PlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"

APC_PlayerController::APC_PlayerController()
{
	bReplicates = true;
}

void APC_PlayerController::BeginPlay()
{
	Super::BeginPlay();
	check(PlayerContext);

	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	check(Subsystem);
	Subsystem->AddMappingContext(PlayerContext, 0);

	bShowMouseCursor = false;

	FInputModeGameAndUI InputModeData;
	InputModeData.SetHideCursorDuringCapture(false);
	SetInputMode(InputModeData);
}

void APC_PlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	UEnhancedInputComponent* EnchancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);

	EnchancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &APC_PlayerController::Move);
}

void APC_PlayerController::Move(const FInputActionValue& InputActionValue)
{
	const FVector2D InputAxisVector = InputActionValue.Get<FVector2D>();
	const FRotator Rotation = GetControlRotation();
	const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);

	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	if (APawn* ControlledPawn = GetPawn<APawn>()) {
		ControlledPawn->AddMovementInput(ForwardDirection, InputAxisVector.Y);
		ControlledPawn->AddMovementInput(RightDirection, InputAxisVector.X);
	}
}


