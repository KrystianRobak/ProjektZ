// Fill out your copyright notice in the Description page of Project Settings.

#include "AbilitySystem/ProjektZAbilitySystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Player/ProjektZPlayerState.h"
#include "UI/WidgetController/ProjektZWidgetController.h"
#include <UI/HUD/ProjektZHUD.h>
#include <ProjektZGameModeBase.h>
#include <ProjektZAbilityTypes.h>
#include <Interaction/CombatInterface.h>

UOverlayWidgetController* UProjektZAbilitySystemLibrary::GetOverlayWidgetController(const UObject* WorldContextObject)
{
	if (APlayerController* PC = UGameplayStatics::GetPlayerController(WorldContextObject, 0))
	{
		if (AProjektZHUD* ProjektZHUD = Cast<AProjektZHUD>(PC->GetHUD()))
		{
			AProjektZPlayerState* PS = PC->GetPlayerState<AProjektZPlayerState>();
			UAbilitySystemComponent* ASC = PS->GetAbilitySystemComponent();
			UAttributeSet* AS = PS->GetAttributeSet();

			const FWidgetControllerParams WidgetControllerParams(PC, PS, ASC, AS);

			return ProjektZHUD->GetOverlayWidgetController(WidgetControllerParams);
		}
	}

	return nullptr;
}

UAttributeMenuWidgetController* UProjektZAbilitySystemLibrary::GetAttributeMenuWidgetController(const UObject* WorldContextObject)
{
	if (APlayerController* PC = UGameplayStatics::GetPlayerController(WorldContextObject, 0))
	{
		if (AProjektZHUD* ProjektZHUD = Cast<AProjektZHUD>(PC->GetHUD()))
		{
			AProjektZPlayerState* PS = PC->GetPlayerState<AProjektZPlayerState>();
			UAbilitySystemComponent* ASC = PS->GetAbilitySystemComponent();
			UAttributeSet* AS = PS->GetAttributeSet();

			const FWidgetControllerParams WidgetControllerParams(PC, PS, ASC, AS);

			return ProjektZHUD->GetAttributeMenuWidgetController(WidgetControllerParams);
		}
	}

	return nullptr;
}

void UProjektZAbilitySystemLibrary::InitializeDefaultAbilities(const UObject* WorldContextObject, ECharacterClass CharacterClass, float Level, UAbilitySystemComponent* ASC)
{
	FCharacterClassDefaultInfo ClassDefaultInfo = GetCharacterClassInfo(WorldContextObject)->GetClassDefaultInfo(CharacterClass);

	ClassDefaultInfo.StartupAbilities;
	for (TSubclassOf<UGameplayAbility> Ability : ClassDefaultInfo.StartupAbilities)
	{
		FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(Ability, 1);
		ASC->GiveAbility(AbilitySpec);
	}

}


void UProjektZAbilitySystemLibrary::InitializeDefaultAttributes(const UObject* WorldContextObject, ECharacterClass CharacterClass, float Level, UAbilitySystemComponent* ASC)
{
	FCharacterClassDefaultInfo ClassDefaultInfo = GetCharacterClassInfo(WorldContextObject)->GetClassDefaultInfo(CharacterClass);
	
	ApplyEffectToASC(ASC, ClassDefaultInfo.PrimaryAttributes, Level);
	ApplyEffectToASC(ASC, ClassDefaultInfo.SecondaryAttribute, Level);
	ApplyEffectToASC(ASC, ClassDefaultInfo.VitalAttribute, Level);
	ApplyEffectToASC(ASC, ClassDefaultInfo.ResistanceAttribute, Level);
}

void UProjektZAbilitySystemLibrary::GiveCommonAbilitites(const UObject* WorldContextObject, UAbilitySystemComponent* ASC)
{
	if (ASC)
	{
		UCharacterClassInfo* ClassDefaultInfo = GetCharacterClassInfo(WorldContextObject);
		for (TSubclassOf<UGameplayAbility> AbilityClass : ClassDefaultInfo->CommonAbilities)
		{
			FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(AbilityClass, 1);
			ASC->GiveAbility(AbilitySpec);
		}
	}
}


void UProjektZAbilitySystemLibrary::ApplyEffectToASC(UAbilitySystemComponent* ASC, const TSubclassOf<UGameplayEffect>& GameplayEffectClass, const float Level)
{
	
	check(IsValid(ASC));
	check(GameplayEffectClass);

	FGameplayEffectContextHandle EffectContextHandle = ASC->MakeEffectContext();

	EffectContextHandle.AddSourceObject(ASC->GetAvatarActor());

	const FGameplayEffectSpecHandle EffectSpecHandle = ASC->MakeOutgoingSpec(GameplayEffectClass, Level, EffectContextHandle);

	ASC->ApplyGameplayEffectSpecToSelf(*EffectSpecHandle.Data.Get());
}

UCharacterClassInfo* UProjektZAbilitySystemLibrary::GetCharacterClassInfo(const UObject* WorldContextObject)
{
	AProjektZGameModeBase* GameMode = Cast<AProjektZGameModeBase>(UGameplayStatics::GetGameMode(WorldContextObject));
	if (GameMode == nullptr) return nullptr;

	return GameMode->CharacterClassInfo;
}

bool UProjektZAbilitySystemLibrary::IsBlockedHit(const FGameplayEffectContextHandle& EffectContextHandle)
{
	const FGameplayEffectContext* Context = EffectContextHandle.Get();
	if (const FProjektZGameplayEffectContext* CurrentContext = static_cast<const FProjektZGameplayEffectContext*>(Context))
	{
		return CurrentContext->IsBlockedHit();
	}
	return false;
}

bool UProjektZAbilitySystemLibrary::IsCriticalHit(const FGameplayEffectContextHandle& EffectContextHandle)
{
	const FGameplayEffectContext* Context = EffectContextHandle.Get();
	if (const FProjektZGameplayEffectContext* CurrentContext = static_cast<const FProjektZGameplayEffectContext*>(Context))
	{
		return CurrentContext->IsCriticaHit();
	}
	return false;
}

void UProjektZAbilitySystemLibrary::SetIsBlockedHit(UPARAM(ref)FGameplayEffectContextHandle& EffectContextHandle, bool bInIsBlockedHit)
{
	FGameplayEffectContext* Context = EffectContextHandle.Get();
	if (FProjektZGameplayEffectContext* CurrentContext = static_cast<FProjektZGameplayEffectContext*>(Context))
	{
		CurrentContext->SetIsBlockedHit(bInIsBlockedHit);
	}
}

void UProjektZAbilitySystemLibrary::SetIsCriticalHit(UPARAM(ref)FGameplayEffectContextHandle& EffectContextHandle, bool bInIsCriticalHit)
{
	FGameplayEffectContext* Context = EffectContextHandle.Get();
	if (FProjektZGameplayEffectContext* CurrentContext = static_cast<FProjektZGameplayEffectContext*>(Context))
	{
		CurrentContext->SetIsCriticalHit(bInIsCriticalHit);
	}
}

void UProjektZAbilitySystemLibrary::GetLivePlayerWithinRadius(const UObject* WorldContextObject, TArray<AActor*>& OutOverLappingActors, const TArray<AActor*>& ActorsToIgnore, float Radius, const FVector& SphereOrigin)
{
	FCollisionQueryParams SphereParams;
	SphereParams.AddIgnoredActors(ActorsToIgnore);

	if (const UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull))
	{
		TArray<FOverlapResult> Overlaps;
		World->OverlapMultiByObjectType(Overlaps, SphereOrigin, FQuat::Identity, FCollisionObjectQueryParams(FCollisionObjectQueryParams::InitType::AllDynamicObjects), FCollisionShape::MakeSphere(Radius), SphereParams);
		for (FOverlapResult& Overlap : Overlaps)
		{
			if (Overlap.GetActor()->Implements<UCombatInterface>() && !ICombatInterface::Execute_IsDead(Overlap.GetActor()))
			{
				OutOverLappingActors.AddUnique(ICombatInterface::Execute_GetAvatar(Overlap.GetActor()));
			}
		}
	}

}



