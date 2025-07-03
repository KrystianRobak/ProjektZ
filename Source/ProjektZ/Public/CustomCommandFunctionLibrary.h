// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "CustomCommandFunctionLibrary.generated.h"

DECLARE_DELEGATE_OneParam(FCppCommandDelegate, const TArray<FString>&)

DECLARE_DYNAMIC_DELEGATE_OneParam(FBlueprintCommandDelegate, const TArray<FString>&, Parameters);


USTRUCT(BlueprintType)
struct FCustomCommand
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Custom Command")
	FString Command;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Custom Command")
	FString CommandDescription;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Custom Command")
	TArray<FString> CommandParameters;
};


USTRUCT(BlueprintType)
struct FCustomCommandBinding
{
	GENERATED_BODY()

	// Associated command
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Custom Command")
	FCustomCommand Command;

	// Blueprint delegate (bindable in Blueprints)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Custom Command")
	FBlueprintCommandDelegate BlueprintCallback;

	// C++ delegate (not exposed to Blueprints)
	FCppCommandDelegate CppCallback;

	// Utility to call the correct bound function
	void Execute(const TArray<FString>& Params) const
	{
		if (CppCallback.IsBound())
		{
			CppCallback.Execute(Params);
		}
		else if (BlueprintCallback.IsBound())
		{
			BlueprintCallback.Execute(Params);
		}
	}
};


/**
 * 
 */
UCLASS()
class PROJEKTZ_API UCustomCommandFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:

	/** Adds a command binding to the map */
	UFUNCTION(BlueprintCallable, Category = "Custom Command")
	static void RegisterCommand(const FCustomCommandBinding& Binding);

	/** Call command by input array (first = command, rest = parameters) */
	UFUNCTION(BlueprintCallable, Category = "Custom Command")
	static bool ExecuteCommandFromInputString(const FString& InputString);

	/** Find all commands matching a regex pattern (case-insensitive) */
	UFUNCTION(BlueprintCallable, Category = "Custom Command")
	static TArray<FCustomCommand> FindCommandsMatchingRegex(const FString& RegexPattern);
private:

	/** Static map of command string -> command binding */
	static TMap<FString, FCustomCommandBinding> CommandMap;
};
