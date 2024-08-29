// Fill out your copyright notice in the Description page of Project Settings.


#include "AsyncTasks/WaitCooldownChange.h"

UWaitCooldownChange* UWaitCooldownChange::WaitForCooldownChange(UAbilitySystemComponent* InASC, const FGameplayTag& InCooldownTag)
{
	UWaitCooldownChange* WaitCooldownChange = NewObject<UWaitCooldownChange>();
	WaitCooldownChange->ASC = InASC;
	WaitCooldownChange->CooldownTag = InCooldownTag;

	if (!InASC || !InCooldownTag.IsValid())
	{
		WaitCooldownChange->EndTask();
		return nullptr;
	}


	//To know when a cooldown has ended (Removed Cooldown Tag)
	InASC->RegisterGameplayTagEvent(InCooldownTag, EGameplayTagEventType::NewOrRemoved).AddUObject(WaitCooldownChange, &UWaitCooldownChange::CooldownTagChanged);


	//To know when a cooldown  effect had been applied
	InASC->OnActiveGameplayEffectAddedDelegateToSelf.AddUObject(WaitCooldownChange, &UWaitCooldownChange::OnActiveEffectAdded);

	return WaitCooldownChange;
}

void UWaitCooldownChange::EndTask()
{
	if (!ASC) return;
	ASC->RegisterGameplayTagEvent(CooldownTag, EGameplayTagEventType::NewOrRemoved).RemoveAll(this);

	SetReadyToDestroy();
	MarkAsGarbage();
}

void UWaitCooldownChange::CooldownTagChanged(const FGameplayTag InCooldownTag, int32 NewCount)
{
	if (NewCount == 0)
	{
		CooldownEnd.Broadcast(0.f);
	}

}

void UWaitCooldownChange::OnActiveEffectAdded(UAbilitySystemComponent* InASC, const FGameplayEffectSpec& InSpecApplied, FActiveGameplayEffectHandle InActiveEffectHandle)
{
	FGameplayTagContainer AssetTags;
	InSpecApplied.GetAllAssetTags(AssetTags);

	FGameplayTagContainer GrantedTags;
	InSpecApplied.GetAllGrantedTags(GrantedTags);

	if (AssetTags.HasTagExact(CooldownTag) || GrantedTags.HasTagExact(CooldownTag))
	{
		FGameplayEffectQuery GameplayEffectQuery = FGameplayEffectQuery::MakeQuery_MatchAnyOwningTags(CooldownTag.GetSingleTagContainer());
		TArray<float> TimesRemaining = ASC->GetActiveEffectsTimeRemaining(GameplayEffectQuery);

		if (TimesRemaining.Num() > 0)
		{
			float TimeRemaining = TimesRemaining[0];
			for (float Num : TimesRemaining)
			{
				if (Num > TimeRemaining) TimeRemaining = Num;
			}

			CooldownStart.Broadcast(TimeRemaining);
		}
	}
}
