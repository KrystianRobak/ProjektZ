// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomCommandInstanceSubsystem.h"
#include <CustomCommandFunctionLibrary.h>

void UCustomCommandInstanceSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	// Custom initialization logic can be added here
	UE_LOG(LogTemp, Warning, TEXT("CustomCommandInstanceSubsystem Initialized"));

	// Example: Registering a command
	UCustomCommandFunctionLibrary::RegisterCommand(FCustomCommandBinding{
		FCustomCommand{
			TEXT("exampleCommand"),
			TEXT("This is an example command."),
			{TEXT("param1"), TEXT("param2")}
		},
		FCppCommandDelegate::CreateLambda([](const TArray<FString>& Params)
			{
				UE_LOG(LogTemp, Warning, TEXT("Example command executed with params: %s"), *FString::Join(Params, TEXT(", ")));
			})
		});
}
