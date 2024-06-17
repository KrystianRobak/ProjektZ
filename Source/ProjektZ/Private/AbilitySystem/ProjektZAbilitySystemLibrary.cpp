// Fill out your copyright notice in the Description page of Project Settings.

#include "AbilitySystem/ProjektZAbilitySystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Player/ProjektZPlayerState.h"
#include "UI/WidgetController/ProjektZWidgetController.h"
#include <UI/HUD/ProjektZHUD.h>
#include <ProjektZGameModeBase.h>

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

void UProjektZAbilitySystemLibrary::InitializeDefaultAttributes(const UObject* WorldContextObject, ECharacterClass CharacterClass, float Level, UAbilitySystemComponent* ASC)
{
	AProjektZGameModeBase* GameMode = Cast<AProjektZGameModeBase>(UGameplayStatics::GetGameMode(WorldContextObject));
	if (GameMode == nullptr) return;

	FCharacterClassDefaultInfo ClassDefaultInfo = GameMode->CharacterClassInfo->GetClassDefaultInfo(CharacterClass);
	
	ApplyEffectToASC(ASC, ClassDefaultInfo.PrimaryAttributes, Level);
	ApplyEffectToASC(ASC, ClassDefaultInfo.SecondaryAttribute, Level);
	ApplyEffectToASC(ASC, ClassDefaultInfo.VitalAttribute, Level);
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

