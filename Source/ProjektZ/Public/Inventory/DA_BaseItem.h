// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include <GameplayTagContainer.h>
#include "ProjektZAbilityTypes.h"
#include "DA_BaseItem.generated.h"

UENUM(BlueprintType)
enum EItemGrad
{
	Common,
	Uncommon,
	Rare,
	Unique,
	Legendary,
	Mythic,
	Divine
};

UENUM(BlueprintType)
enum EItemPlacement
{
	Head,
	Armor,
	FirstHand,
	SecondHand,
	LeftRing,
	RightRing,
	Necless,
	Noone
};

USTRUCT(BlueprintType)
struct FBaseItemInfo
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TEnumAsByte<EItemGrad> ItemGrade = EItemGrad::Common;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TEnumAsByte<EItemPlacement> ItemTypePlacement = EItemPlacement::Noone;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UTexture2D> Icon = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UMaterialInterface> BackgroundMaterial = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<USkeletalMesh> WeaponMesh = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FEffectParams Modifiers;
};
/**
 * 
 */
UCLASS()
class PROJEKTZ_API UDA_BaseItem : public UDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "ItemInformation")
	TArray<FBaseItemInfo> ItemInformation;
};
