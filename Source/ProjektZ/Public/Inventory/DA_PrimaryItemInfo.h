// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "DA_PrimaryItemInfo.generated.h"

class UGameplayAbility;

UENUM(BlueprintType)
enum EItemType
{
	Sword,
	Axe,
	Hammer,
	Mace,
	ShortSword,
	Shield,
	MagicBook,
	Wand
};

UENUM(BlueprintType)
enum EItemPlacement
{
	Head,
	Necless,
	Armor,
	Bracelet,
	FirstHand,
	SecondHand,
	LeftRing,
	Boots,
	RightRing,
	Noone
};

USTRUCT(BlueprintType)
struct FPrimaryItemInfo
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TEnumAsByte<EItemPlacement> ItemTypePlacement = EItemPlacement::Noone;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TEnumAsByte<EItemType> ItemType = EItemType::Sword;

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
class PROJEKTZ_API UDA_PrimaryItemInfo : public UDataAsset
{
	GENERATED_BODY()
public:
	FPrimaryItemInfo GetInfoByType(EItemType ItemType);


	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "ItemInformation")
	TArray<FPrimaryItemInfo> ItemInformation;
};
