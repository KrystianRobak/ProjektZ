// Fill out your copyright notice in the Description page of Project Settings.

#include "AbilitySystem/ProjektZAbilitySystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Player/ProjektZPlayerState.h"
#include "UI/WidgetController/ProjektZWidgetController.h"
#include <UI/HUD/ProjektZHUD.h>
#include "AbilitySystem/ProjektZAttributeSet.h"
#include <ProjektZGameModeBase.h>
#include <ProjektZAbilityTypes.h>
#include "ProjektZGameplayTags.h"
#include <AbilitySystemBlueprintLibrary.h>
#include <GameplayEffectComponents/TargetTagsGameplayEffectComponent.h>
#include <Interaction/CombatInterface.h>
#include <AbilitySystem/ProjektZAbilitySystemComponent.h>
#include "Engine/OverlapResult.h"

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

USpellMenuWidgetController* UProjektZAbilitySystemLibrary::GetSpellMenuWidgetController(const UObject* WorldContextObject)
{
	if (APlayerController* PC = UGameplayStatics::GetPlayerController(WorldContextObject, 0))
	{
		if (AProjektZHUD* ProjektZHUD = Cast<AProjektZHUD>(PC->GetHUD()))
		{
			AProjektZPlayerState* PS = PC->GetPlayerState<AProjektZPlayerState>();
			UAbilitySystemComponent* ASC = PS->GetAbilitySystemComponent();
			UAttributeSet* AS = PS->GetAttributeSet();

			const FWidgetControllerParams WidgetControllerParams(PC, PS, ASC, AS);

			return ProjektZHUD->GetSpellMenuWidgetController(WidgetControllerParams);
		}
	}

	return nullptr;
}

//UPartyStatsWidgetController* UProjektZAbilitySystemLibrary::GetPartyStatsMenuWidgetController(const UObject* WorldContextObject)
//{
//	if (APlayerController* PC = UGameplayStatics::GetPlayerController(WorldContextObject, 0))
//	{
//		if (AProjektZHUD* ProjektZHUD = Cast<AProjektZHUD>(PC->GetHUD()))
//		{
//			AProjektZPlayerState* PS = PC->GetPlayerState<AProjektZPlayerState>();
//			UAbilitySystemComponent* ASC = PS->GetAbilitySystemComponent();
//			UAttributeSet* AS = PS->GetAttributeSet();
//
//			const FWidgetControllerParams WidgetControllerParams(PC, PS, ASC, AS);
//
//			return ProjektZHUD->GetPartyMembersWidgetController(WidgetControllerParams);
//		}
//	}
//
//	return nullptr;
//}

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
	
	ApplyEffectToASC(ASC, ClassDefaultInfo.OffensiveAttributes, Level);
	ApplyEffectToASC(ASC, ClassDefaultInfo.DefensiveAttributes, Level);
	ApplyEffectToASC(ASC, ClassDefaultInfo.VitalAttributes, Level);
	ApplyEffectToASC(ASC, ClassDefaultInfo.ResistanceAttributes, Level);
	ApplyEffectToASC(ASC, ClassDefaultInfo.AmplifierAttributes, Level);
}

void UProjektZAbilitySystemLibrary::GiveCommonAbilitites(const UObject* WorldContextObject, UAbilitySystemComponent* ASC)
{
	if (UProjektZAbilitySystemComponent* ProjektZASC = Cast<UProjektZAbilitySystemComponent>(ASC))
	{
		UCharacterClassInfo* ClassDefaultInfo = GetCharacterClassInfo(WorldContextObject);
		for (TSubclassOf<UGameplayAbility> AbilityClass : ClassDefaultInfo->CommonAbilities)
		{
			FAbilityData Data;
			ProjektZASC->AddAbility(AbilityClass, 1, Data);
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

//bool UProjektZAbilitySystemLibrary::IsSuccessfulDebuff(const FGameplayEffectContextHandle& EffectContextHandle)
//{
//	const FGameplayEffectContext* Context = EffectContextHandle.Get();
//	if (const FProjektZGameplayEffectContext* CurrentContext = static_cast<const FProjektZGameplayEffectContext*>(Context))
//	{
//		return CurrentContext->IsSuccessfullDebuff();
//	}
//	return false;
//}
//
//TArray<FEffectParams> UProjektZAbilitySystemLibrary::GetDebuffs(const FGameplayEffectContextHandle& EffectContextHandle)
//{
//	const FGameplayEffectContext* Context = EffectContextHandle.Get();
//	if  (const FProjektZGameplayEffectContext* CurrentContext = static_cast<const FProjektZGameplayEffectContext*>(Context))
//	{
//		if (CurrentContext->IsSuccessfullDebuff())
//		{
//			return CurrentContext->GetContextEffects();
//		}
//	}
//	return TArray<FEffectParams>();
//}

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

FActiveGameplayEffectHandle UProjektZAbilitySystemLibrary::ApplyEffect(const FEffectParams& EffectParams, UAbilitySystemComponent* TargetASC, AActor* Instigator, bool bIsInfinite, bool IsSubtraction)
{
	FGameplayTag BaseTag = EffectParams.EffectType;

	//FGameplayTag MagnitudeTag = FGameplayTag::RequestGameplayTag(FName(BaseTag.ToString() + ".Magnitude"));

	FGameplayEffectContextHandle EffectContext = TargetASC->MakeEffectContext();
	EffectContext.AddInstigator(Instigator, Instigator);

	UGameplayEffect* Effect = NewObject<UGameplayEffect>(GetTransientPackage(), FName(BaseTag.ToString()));

	if (bIsInfinite) 
	{
		Effect->DurationPolicy = EGameplayEffectDurationType::Instant;
		Effect->DurationMagnitude = FScalableFloat(0.f);
	}
	else
	{
		Effect->DurationPolicy = EGameplayEffectDurationType::HasDuration;
		Effect->DurationMagnitude = FScalableFloat(EffectParams.EffectDuration);
		Effect->Period = EffectParams.EffectFrequency;
	}

	Effect->InheritableOwnedTagsContainer.AddTag(EffectParams.EffectType);

	FInheritedTagContainer TagContainer = FInheritedTagContainer();
	UTargetTagsGameplayEffectComponent& Component = Effect->FindOrAddComponent<UTargetTagsGameplayEffectComponent>();
	TagContainer.Added.AddTag(EffectParams.EffectType);
	Component.SetAndApplyTargetTagChanges(TagContainer);


	Effect->StackingType = EGameplayEffectStackingType::AggregateBySource;
	Effect->StackLimitCount = 1;

	for (auto Modifier : EffectParams.Modifiers)
	{
		int32 Index = Effect->Modifiers.Num();
		Effect->Modifiers.Add(FGameplayModifierInfo());
		FGameplayModifierInfo& ModifierInfo = Effect->Modifiers[Index];

		if(IsSubtraction)
		{
			ModifierInfo.ModifierMagnitude = FScalableFloat(-(Modifier.EffectMagnitude));
		}
		else
		{
			ModifierInfo.ModifierMagnitude = FScalableFloat(Modifier.EffectMagnitude);
		}
		
		ModifierInfo.ModifierOp = EGameplayModOp::Additive;
		ModifierInfo.Attribute = Modifier.EffectModifiedAttribute;
	}
	
	FGameplayEffectSpec MutableSpec = FGameplayEffectSpec(Effect, EffectContext, 1.f);

	return TargetASC->ApplyGameplayEffectSpecToSelf(MutableSpec);
}


FGameplayEffectContextHandle UProjektZAbilitySystemLibrary::ApplyDamageEffect(const FDamageEffectParams& DamageEffectParams)
{
	const FProjektZGameplayTags& GameplayTags = FProjektZGameplayTags::Get();
	const AActor* SourceAvatarActor = DamageEffectParams.SourceAbilitySystemComponent->GetAvatarActor();

	/* EFFECT TAG APPLYING */

	FGameplayEffectContextHandle EffectContextHandle = DamageEffectParams.SourceAbilitySystemComponent->MakeEffectContext();
	EffectContextHandle.AddSourceObject(SourceAvatarActor);

	FGameplayEffectSpecHandle TempTagSpecHandle = DamageEffectParams.SourceAbilitySystemComponent->MakeOutgoingSpec(DamageEffectParams.ElementApplierEffectClass, DamageEffectParams.AbilityLevel, EffectContextHandle);

	if (TempTagSpecHandle.Data.IsValid())
	{
		TempTagSpecHandle.Data->DynamicGrantedTags.AddTag(DamageEffectParams.ConditionType);
		DamageEffectParams.TargetAbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*TempTagSpecHandle.Data);
	}

	/* DAMAGE APPLYING */

	EffectContextHandle = DamageEffectParams.SourceAbilitySystemComponent->MakeEffectContext();
	EffectContextHandle.AddSourceObject(SourceAvatarActor);

	FGameplayEffectSpecHandle SpecHandle = DamageEffectParams.SourceAbilitySystemComponent->MakeOutgoingSpec(DamageEffectParams.DamageGameplayEffectClass, DamageEffectParams.AbilityLevel, EffectContextHandle);

	UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(SpecHandle, DamageEffectParams.DamageType, DamageEffectParams.BaseDamage);

	DamageEffectParams.TargetAbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data);

	return EffectContextHandle;
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

FActiveGameplayEffectHandle UProjektZAbilitySystemLibrary::ApplyEffectFromEquippedItem(const FBaseItemInfo& ItemInfo, UAbilitySystemComponent* TargetASC, bool IsSubtraction)
{
	return ApplyEffect(ItemInfo.Modifiers, TargetASC, TargetASC->GetOwner(), true, IsSubtraction);
}

bool UProjektZAbilitySystemLibrary::IsNotFriend(AActor* FirstActor, AActor* SecondActor)
{
	const bool FirstIsPLayer = FirstActor->ActorHasTag(FName("Player"));
	const bool SecondIsPLayer = SecondActor->ActorHasTag(FName("Player"));
	const bool FirstIsEnemy = FirstActor->ActorHasTag(FName("Enemy"));
	const bool SecondIsEnemy = SecondActor->ActorHasTag(FName("Enemy"));

	const bool BothArePlayers = FirstIsPLayer && SecondIsPLayer;
	const bool BothAreEnemies = FirstIsEnemy && SecondIsEnemy;
	const bool Friends = BothArePlayers || BothAreEnemies;
	return !Friends;
}





