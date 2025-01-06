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

	if (UProjektZAbilitySystemComponent* ASC = Cast<UProjektZAbilitySystemComponent>(AbilitySystemComponent))
	{
		OnAbilityAdded(ASC);
	}
}

void UOverlayWidgetController::BindCallbackToDependencies()
{
	const UProjektZAttributeSet* ProjektZAttributeSet = CastChecked<UProjektZAttributeSet>(AttributeSet);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(ProjektZAttributeSet->GetHealthAttribute()).AddLambda(
		[this](const FOnAttributeChangeData& Data) 
		{
			OnHealthChanged.Broadcast(Data.NewValue);
		}
	);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(ProjektZAttributeSet->GetMaxHealthAttribute()).AddLambda(
		[this](const FOnAttributeChangeData& Data)
		{
			OnMaxHealthChanged.Broadcast(Data.NewValue);
		}
	);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(ProjektZAttributeSet->GetManaAttribute()).AddLambda(
		[this](const FOnAttributeChangeData& Data)
		{
			OnManaChanged.Broadcast(Data.NewValue);
		}
	);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(ProjektZAttributeSet->GetMaxManaAttribute()).AddLambda(
		[this](const FOnAttributeChangeData& Data)
		{
			OnMaxManaChanged.Broadcast(Data.NewValue);
		}
	);

	if (UProjektZAbilitySystemComponent* ProjektZASC = Cast<UProjektZAbilitySystemComponent>(AbilitySystemComponent))
	{
		ProjektZASC->AbilitiesGivenDelegate.AddUObject(this, &UOverlayWidgetController::OnAbilityAdded);

		ProjektZASC->EffectAssetTags.AddLambda(
			[this](const FGameplayTagContainer& AssetsTags)
			{
				for (const FGameplayTag& Tag : AssetsTags)
				{
					FGameplayTag MessageTag = FGameplayTag::RequestGameplayTag("Message");
					if (Tag.MatchesTag(MessageTag))
					{
						const FUIWidgetRow* Row = GetDataTableRowByTag<FUIWidgetRow>(MessageWidgetDataTable, Tag);
						MessageWidgetRowDelegate.Broadcast(*Row);
					}
				}
			}
		);
	}
}

void UOverlayWidgetController::OnAbilityAdded(UProjektZAbilitySystemComponent* ASC)
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
