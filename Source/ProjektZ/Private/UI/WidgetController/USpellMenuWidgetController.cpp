// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/WidgetController/USpellMenuWidgetController.h"

void USpellMenuWidgetController::BroadcastInitialValues()
{
	if (UProjektZAbilitySystemComponent* ASC = Cast<UProjektZAbilitySystemComponent>(AbilitySystemComponent))
	{
		OnAbilityChanged(ASC);
	}
}

void USpellMenuWidgetController::BindCallbackToDependencies()
{
	/*if (UProjektZAbilitySystemComponent* ProjektZASC = Cast<UProjektZAbilitySystemComponent>(AbilitySystemComponent))
	{
		ProjektZASC->AbilitiesGivenDelegate.AddUObject(this, &USpellMenuWidgetController::OnAbilityChanged);
	}*/
}


void USpellMenuWidgetController::OnAbilityChanged(UProjektZAbilitySystemComponent* ASC)
{
	FForEachAbility BroadcastDelegate;
	BroadcastDelegate.BindLambda([this, ASC](const FGameplayAbilitySpec& AbilitySpec)
		{
			FProjektZAbilityInfo Info = AbilityInfo->FindAbilityInfoByTag(ASC->GetAbilityTagFromSpec(AbilitySpec));
			Info.InputTag = ASC->GetInputTagFromSpec(AbilitySpec);
			AbilityInfoDelegate.Broadcast(Info);
		});

	ASC->ForEachAbility(BroadcastDelegate);
}