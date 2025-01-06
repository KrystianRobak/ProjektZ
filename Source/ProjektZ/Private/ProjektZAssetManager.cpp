// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjektZAssetManager.h"
#include "ProjektZGameplayTags.h"
#include "AbilitySystemGlobals.h"

UProjektZAssetManager& UProjektZAssetManager::Get()
{
	check(GEngine);

	UProjektZAssetManager* ProjektZAssetManager = Cast<UProjektZAssetManager>(GEngine->AssetManager);
	return *ProjektZAssetManager;
}

void UProjektZAssetManager::StartInitialLoading()
{
	Super::StartInitialLoading();

	FProjektZGameplayTags::InitializeNativeGameplayTags();

	UAbilitySystemGlobals::Get().InitGlobalData();
}
