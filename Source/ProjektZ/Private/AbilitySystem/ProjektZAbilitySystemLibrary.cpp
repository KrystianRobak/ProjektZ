// Fill out your copyright notice in the Description page of Project Settings.

#include "AbilitySystem/ProjektZAbilitySystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Player/ProjektZPlayerState.h"
#include "UI/WidgetController/ProjektZWidgetController.h"
#include <UI/HUD/ProjektZHUD.h>
#include <ProjektZGameModeBase.h>
#include <ProjektZAbilityTypes.h>
#include "ProjektZGameplayTags.h"
#include <AbilitySystemBlueprintLibrary.h>

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

bool UProjektZAbilitySystemLibrary::IsSuccessfulDebuff(const FGameplayEffectContextHandle& EffectContextHandle)
{
	const FGameplayEffectContext* Context = EffectContextHandle.Get();
	if (const FProjektZGameplayEffectContext* CurrentContext = static_cast<const FProjektZGameplayEffectContext*>(Context))
	{
		return CurrentContext->IsSuccessfullDebuff();
	}
	return false;
}

TArray<FEffectParams> UProjektZAbilitySystemLibrary::GetDebuffs(const FGameplayEffectContextHandle& EffectContextHandle)
{
	const FGameplayEffectContext* Context = EffectContextHandle.Get();
	if  (const FProjektZGameplayEffectContext* CurrentContext = static_cast<const FProjektZGameplayEffectContext*>(Context))
	{
		if (CurrentContext->IsSuccessfullDebuff())
		{
			return CurrentContext->GetContextEffects();
		}
	}
	return TArray<FEffectParams>();
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

void UProjektZAbilitySystemLibrary::ApplyEffects(const TArray<FEffectParams>& EffectParams, UAbilitySystemComponent* TargetASC)
{
	
}


FGameplayEffectContextHandle UProjektZAbilitySystemLibrary::ApplyDamageEffect(const FDamageEffectParams& DamageEffectParams)
{
	const FProjektZGameplayTags& GameplayTags = FProjektZGameplayTags::Get();
	const AActor* SourceAvatarActor = DamageEffectParams.SourceAbilitySystemComponent->GetAvatarActor();

	FGameplayEffectContextHandle EffectContextHandle = DamageEffectParams.SourceAbilitySystemComponent->MakeEffectContext();
	EffectContextHandle.AddSourceObject(SourceAvatarActor);

	FGameplayEffectSpecHandle SpecHandle = DamageEffectParams.SourceAbilitySystemComponent->MakeOutgoingSpec(DamageEffectParams.DamageGameplayEffectClass, DamageEffectParams.AbilityLevel, EffectContextHandle);

	UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(SpecHandle, DamageEffectParams.DamageType, DamageEffectParams.BaseDamage);

	DamageEffectParams.TargetAbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data);

	return EffectContextHandle;
}



