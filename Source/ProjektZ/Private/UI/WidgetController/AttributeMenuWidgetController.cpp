// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/WidgetController/AttributeMenuWidgetController.h"

#include "AbilitySystem/ProjektZAttributeSet.h"
#include "ProjektZGameplayTags.h"

void UAttributeMenuWidgetController::BindCallbackToDependencies()
{
	UProjektZAttributeSet* AS = CastChecked<UProjektZAttributeSet>(AttributeSet);

	check(AttributeInformation);

	for (auto& Pair : AS->TagsToAttributes)
	{
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(Pair.Value).AddLambda(
			[this, Pair](const FOnAttributeChangeData& Data)
			{
				FProjektZAttributeInfo Info = AttributeInformation->FindAttributeInfoForTag(Pair.Key);
				Info.AttributeValue = Pair.Value.GetNumericValue(AttributeSet);
				UE_LOG(LogTemp, Log, TEXT("Broadcasting Attribute Info"));
				AttributeInfoDelegate.Broadcast(Info);
			}
		);
	}
}

void UAttributeMenuWidgetController::BroadcastInitialValues()
{
	UProjektZAttributeSet* AS = CastChecked<UProjektZAttributeSet>(AttributeSet);

	check(AttributeInformation);

	for (auto& Pair : AS->TagsToAttributes)
	{
		FProjektZAttributeInfo Info = AttributeInformation->FindAttributeInfoForTag(Pair.Key);
		Info.AttributeValue = Pair.Value.GetNumericValue(AttributeSet);
		AttributeInfoDelegate.Broadcast(Info);
	}
}

//void UAttributeMenuWidgetController::BroadcastAttributeInfo(const FGameplayTag& AttributeTag, const FGameplayAttribute& GamAttribute)
//{
//	FProjektZAttributeInfo Info = AttributeInformation->FindAttributeInfoForTag(AttributeTag);
//	Info.AttributeValue = GamAttribute.GetNumericValue(AttributeSet);
//	AttributeInfoDelegate.Broadcast(Info);
//}
