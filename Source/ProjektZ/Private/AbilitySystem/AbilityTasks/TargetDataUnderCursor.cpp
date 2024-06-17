// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/AbilityTasks/TargetDataUnderCursor.h"
#include "AbilitySystemComponent.h"

UTargetDataUnderCursor* UTargetDataUnderCursor::CreateTargetDataUnderCursor(UGameplayAbility* OwningAbility)
{
	UTargetDataUnderCursor* MyObj = NewAbilityTask<UTargetDataUnderCursor>(OwningAbility);

	return MyObj;
}

void UTargetDataUnderCursor::Activate()
{
	const bool bIsLocalyControllerd = Ability->GetCurrentActorInfo()->IsLocallyControlled();
	if (bIsLocalyControllerd)
	{
		SendCameraCursorData();
	}
	else
	{
		FGameplayAbilitySpecHandle SpecHandle = GetAbilitySpecHandle();
		FPredictionKey ActivationPredictionKey = GetActivationPredictionKey();

		AbilitySystemComponent.Get()->AbilityTargetDataSetDelegate(SpecHandle, ActivationPredictionKey).AddUObject(this, &UTargetDataUnderCursor::OnTargetDataReplicatedCallback);
		const bool bCalledDelegate = AbilitySystemComponent.Get()->CallReplicatedTargetDataDelegatesIfSet(SpecHandle, ActivationPredictionKey);

		if (!bCalledDelegate)
		{
			SetWaitingOnRemotePlayerData();
		}
	}
}

void UTargetDataUnderCursor::SendCameraCursorData()
{
    FScopedPredictionWindow ScopedPrediction(AbilitySystemComponent.Get());
    FGameplayAbilityTargetDataHandle DataHandle;
    FGameplayAbilityTargetData_SingleTargetHit* Data = new FGameplayAbilityTargetData_SingleTargetHit();

    APlayerController* PC = Ability->GetCurrentActorInfo()->PlayerController.Get();
    if (!PC) return;

    FInt32Vector2 ViewportSize;
    PC->GetViewportSize(ViewportSize.X, ViewportSize.Y);

    FVector2D ScreenLocation(ViewportSize.X / 2.0f, ViewportSize.Y / 2.0f);
    FVector WorldPosition, WorldDirection;

    if (PC->DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, WorldPosition, WorldDirection))
    {
        FCollisionQueryParams Params;
        Params.AddIgnoredActor(PC->GetPawn());

        FVector TraceEnd = WorldPosition + (WorldDirection * 10000.0f);
        FHitResult HitResult;

        GetWorld()->LineTraceSingleByChannel(HitResult, WorldPosition, TraceEnd, ECollisionChannel::ECC_Visibility, Params);

        Data->HitResult = HitResult;
        DataHandle.Add(Data);

        AbilitySystemComponent->ServerSetReplicatedTargetData(GetAbilitySpecHandle(), GetActivationPredictionKey(), DataHandle, FGameplayTag(), AbilitySystemComponent->ScopedPredictionKey);

        if (ShouldBroadcastAbilityTaskDelegates())
        {
            ValidData.Broadcast(DataHandle);
        }
    }
}


void UTargetDataUnderCursor::OnTargetDataReplicatedCallback(const FGameplayAbilityTargetDataHandle& DataHandle, FGameplayTag ActivationTag)
{
	AbilitySystemComponent->ConsumeClientReplicatedTargetData(GetAbilitySpecHandle(), GetActivationPredictionKey());
	if (ShouldBroadcastAbilityTaskDelegates())
	{
		ValidData.Broadcast(DataHandle);
	}
}
