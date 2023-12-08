// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/WidgetController/OverlayWidgetController.h"
#include "AbilitySystem/ProjektZAttributeSet.h"

void UOverlayWidgetController::BroadcastInitialValues()
{
	const UProjektZAttributeSet* ProjektZAttributeSet = CastChecked<UProjektZAttributeSet>(AttributeSet);

	OnHealthChanged.Broadcast(ProjektZAttributeSet->GetHealth());
	OnMaxHealthChanged.Broadcast(ProjektZAttributeSet->GetMaxHealth());

	OnManaChanged.Broadcast(ProjektZAttributeSet->GetMana());
	OnMaxManaChanged.Broadcast(ProjektZAttributeSet->GetMaxMana());

}

void UOverlayWidgetController::BindCallbackToDependencies()
{
	const UProjektZAttributeSet* ProjektZAttributeSet = CastChecked<UProjektZAttributeSet>(AttributeSet);
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(ProjektZAttributeSet->GetHealthAttribute()).AddUObject(this, &UOverlayWidgetController::HealthChanged);
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(ProjektZAttributeSet->GetMaxHealthAttribute()).AddUObject(this, &UOverlayWidgetController::MaxHealthChanged);
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(ProjektZAttributeSet->GetManaAttribute()).AddUObject(this, &UOverlayWidgetController::ManaChanged);
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(ProjektZAttributeSet->GetMaxManaAttribute()).AddUObject(this, &UOverlayWidgetController::MaxManaChanged);
}

void UOverlayWidgetController::HealthChanged(const FOnAttributeChangeData& Data) const
{
	OnHealthChanged.Broadcast(Data.NewValue);
}

void UOverlayWidgetController::MaxHealthChanged(const FOnAttributeChangeData& Data) const
{
	OnMaxHealthChanged.Broadcast(Data.NewValue);
}

void UOverlayWidgetController::ManaChanged(const FOnAttributeChangeData& Data) const
{
	OnManaChanged.Broadcast(Data.NewValue);
}

void UOverlayWidgetController::MaxManaChanged(const FOnAttributeChangeData& Data) const
{
	OnMaxManaChanged.Broadcast(Data.NewValue);
}
