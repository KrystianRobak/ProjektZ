// Fill out your copyright notice in the Description page of Project Settings.


#include "Inventory/ItemGenerator.h"

// Sets default values
AItemGenerator::AItemGenerator()
{

}

//bool AItemGenerator::SelectGradeForItem();

void AItemGenerator::GenerateItems(uint8 amount, TArray<FBaseItemInfo>& ItemContainer)
{
	ItemContainer.Reserve(amount);

	uint8 MinAboveLegendaryItemGradeCount = 0.5;
	uint8 MinAboveRareItemGradeCount = 0.15;

	uint8 BaseItemAttributePointsValue = 100;

	bool RNGJesusManifestation = false;



	for (int i = 0; i < amount; i++)
	{
		FBaseItemInfo ItemInfo;

		//SelectGradeForItem(ItemInfo);

		//RNGJesusManifestation = FMath::RandRange()
	}
}

// Called when the game starts or when spawned
void AItemGenerator::BeginPlay()
{
	Super::BeginPlay();
	
}