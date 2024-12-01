// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include <GameplayTagContainer.h>
#include "ProjektZAbilityTypes.h"
#include "DA_PrimaryItemInfo.h"
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

USTRUCT(BlueprintType)
struct FBaseItemInfo
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TEnumAsByte<EItemGrad> ItemGrade = EItemGrad::Common;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TEnumAsByte<EItemType> ItemType = EItemType::Sword;

	FPrimaryItemInfo* ItemInfo = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FEffectParams Modifiers;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName ItemName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TEnumAsByte<EItemPlacement> ItemTypePlacement = EItemPlacement::Noone;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UTexture2D> Icon = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UMaterialInterface> BackgroundMaterial = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<USkeletalMesh> WeaponMesh = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UGameplayAbility> LMBAbility;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UGameplayAbility> RMBAbility;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FVector2D Dimensions;
};
/**
 * 
 */
UCLASS()
class PROJEKTZ_API UDA_BaseItem : public UDataAsset
{
	GENERATED_BODY()
public:
	//FBaseItemInfo GetItemInfo(FName ItemName);

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "ItemInformation")
	TObjectPtr<UDA_PrimaryItemInfo> Data;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "ItemInformation")
	TArray<FBaseItemInfo> ItemInformation;
};
