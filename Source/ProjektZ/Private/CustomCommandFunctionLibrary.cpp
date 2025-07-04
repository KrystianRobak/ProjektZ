// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomCommandFunctionLibrary.h"

TMap<FString, FCustomCommandBinding> UCustomCommandFunctionLibrary::CommandMap;

void UCustomCommandFunctionLibrary::RegisterCommand(const FCustomCommandBinding& Binding)
{
	if (!Binding.Command.Command.IsEmpty())
	{
		const FString LowerCommand = Binding.Command.Command.ToLower();
		CommandMap.Add(Binding.Command.Command.ToLower(), Binding);
		
		UE_LOG(LogTemp, Warning, TEXT("Command Registered: %s"), *LowerCommand);
	}
}

bool UCustomCommandFunctionLibrary::ExecuteCommandFromInputString(const FString& InputString)
{
	// Split the input by whitespace
	TArray<FString> Tokens;
	InputString.ParseIntoArrayWS(Tokens); // WS = Whitespace

	if (Tokens.Num() == 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("ExecuteCommandFromInputString: Input string is empty."));
		return false;
	}

	// Extract command key (case-insensitive match)
	const FString CommandKey = Tokens[0].ToLower();
	if (!CommandMap.Contains(CommandKey))
	{
		UE_LOG(LogTemp, Warning, TEXT("Command '%s' not found."), *CommandKey);
		return false;
	}

	// Get remaining parameters
	TArray<FString> Parameters = Tokens;
	Parameters.RemoveAt(0);

	// Execute command
	const FCustomCommandBinding& Binding = CommandMap[CommandKey];
	Binding.Execute(Parameters);

	return true;
}

TArray<FCustomCommand> UCustomCommandFunctionLibrary::FindCommandsMatchingRegex(const FString& RegexPattern)
{
	TArray<FCustomCommand> MatchingCommands;

	const FString LowerPattern = RegexPattern.ToLower();
	FRegexPattern CompiledPattern(LowerPattern);

	for (const auto& Elem : CommandMap)
	{
		const FString LowerCommandKey = Elem.Key.ToLower();

		FRegexMatcher Matcher(CompiledPattern, LowerCommandKey);
		if (Matcher.FindNext())
		{
			MatchingCommands.Add(Elem.Value.Command);
		}
	}

	return MatchingCommands;
}
