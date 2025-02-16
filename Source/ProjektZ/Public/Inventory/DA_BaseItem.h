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

	// Custom for every item

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TEnumAsByte<EItemGrad> ItemGrade = EItemGrad::Common;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FEffectParams Modifiers;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString ItemName;

	// Passed from PRIMARY ITEM DATABASE

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TEnumAsByte<EItemType> ItemType = EItemType::Sword;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TEnumAsByte<EItemPlacement> ItemTypePlacement = EItemPlacement::Noone;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UTexture2D> Icon = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UMaterialInterface> BackgroundMaterial = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<USkeletalMesh> WeaponMesh = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<TSubclassOf<UGameplayAbility>> Abilities;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FVector2D Dimensions;


	FBaseItemInfo operator =(FPrimaryItemInfo newItemInfo)
	{
		this->BackgroundMaterial = newItemInfo.BackgroundMaterial;
		this->Dimensions = newItemInfo.Dimensions;
		this->Icon = newItemInfo.Icon;
		this->Abilities = newItemInfo.Abilities;
		this->WeaponMesh = newItemInfo.WeaponMesh;
		this->ItemTypePlacement = newItemInfo.ItemTypePlacement;
		this->ItemType = newItemInfo.ItemType;

		return *this;
	}
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
