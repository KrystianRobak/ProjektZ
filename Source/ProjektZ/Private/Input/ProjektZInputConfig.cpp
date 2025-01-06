// Fill out your copyright notice in the Description page of Project Settings.


#include "Input/ProjektZInputConfig.h"

const UInputAction* UProjektZInputConfig::FindAbilityInputActionForTag(const FGameplayTag& InputTag, bool bLogNotFound) const
{
	for (auto& Action : AbilityInputActions) {
		if (Action.InputTag.MatchesTag(InputTag))
			return Action.InputAction;
	}
	if (bLogNotFound)
	{
		UE_LOG(LogTemp, Error, TEXT("Can't find AbilityInputAction for InputTag [%s], on InptConfig [%s]"), *InputTag.ToString(), *GetNameSafe(this));
	}
	return nullptr;
}
