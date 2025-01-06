// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/AssetManager.h"
#include "ProjektZAssetManager.generated.h"

/**
 * 
 */
UCLASS()
class PROJEKTZ_API UProjektZAssetManager : public UAssetManager
{
	GENERATED_BODY()
public:
	static UProjektZAssetManager& Get();
protected:
	virtual void StartInitialLoading();
};
