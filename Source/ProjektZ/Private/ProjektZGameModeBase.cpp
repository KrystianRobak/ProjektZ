// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjektZGameModeBase.h"

float GetProgressCommon(int Progress) {

    if (Progress == 0) return 0.0f;
    return FMath::Clamp(Progress / 20.f, 0.0f, 1.0f);
}

float GetPrefixChance(EItemGrad Quality)
{
    switch (Quality)
    {
    case EItemGrad::Common: return 0.05f;  // 5%
    case EItemGrad::Rare: return 0.25f;    // 25%
    case EItemGrad::Legendary: return 0.60f; // 60%
    case EItemGrad::Mythic: return 1.0f; // 100%
    default: return 0;
    }
}

float GetSuffixChance(EItemGrad Quality)
{
    switch (Quality)
    {
    case EItemGrad::Common: return 0.15f;  // 15%
    case EItemGrad::Rare: return 0.30f;    // 30%
    case EItemGrad::Legendary: return 0.75f; // 75%
    case EItemGrad::Mythic: return 1.0f; // 100%
    default: return 0;
    }
}

int GetAmountOfModifiers(EItemGrad Quality)
{
    switch (Quality)
    {
    case EItemGrad::Common: return FMath::RandRange(1, 2);
    case EItemGrad::Rare: return FMath::RandRange(3, 4);
    case EItemGrad::Legendary: return FMath::RandRange(5, 6);
    case EItemGrad::Mythic: return FMath::RandRange(7, 8);
    default: return 0;
    }
}

int GetBaseValueForQuality(EItemGrad Quality)
{
    switch (Quality)
    {
    case EItemGrad::Common: return FMath::RandRange(10, 40);
    case EItemGrad::Rare: return FMath::RandRange(40, 80);
    case EItemGrad::Legendary: return FMath::RandRange(80, 140);
    case EItemGrad::Mythic: return FMath::RandRange(140, 200);
    default: return 0;
    }
}

EItemGrad DetermineItemQuality(float ProgressCommon)
{
    float Roll = FMath::FRand();

    float CommonChance = FMath::Lerp(0.60f, 0.10f, ProgressCommon);
    float RareChance = FMath::Lerp(0.24f, 0.40f, ProgressCommon);
    float LegendaryChance = FMath::Lerp(0.10f, 0.30f, ProgressCommon);
    float MythicChance = FMath::Lerp(0.01f, 0.20f, ProgressCommon);

    float TotalChance = CommonChance + RareChance + LegendaryChance + MythicChance;
    CommonChance /= TotalChance;
    RareChance /= TotalChance;
    LegendaryChance /= TotalChance;
    MythicChance /= TotalChance;

    if (Roll < CommonChance) return EItemGrad::Common; // 60% -> 10%
    else if (Roll < CommonChance + RareChance) return EItemGrad::Rare; // 24% -> 40%
    else if (Roll < CommonChance + RareChance + LegendaryChance) return EItemGrad::Legendary; // 10% -> 30%
    else return EItemGrad::Mythic; // 1% -> 20%
}

template<typename T>
T GetRandomElementFromTArray(TArray<T> ArrayToCheck)
{
    return ArrayToCheck[FMath::RandRange(0, ArrayToCheck.Num() - 1)];
}

TArray<FBaseItemInfo> AProjektZGameModeBase::GenerateItemsToDrop(int amount)
{
    TArray<FBaseItemInfo> DroppedItems;

    for (int i = 0; i < amount; i++)
    {
        FBaseItemInfo info;

        // Wybierz bazowy typ przedmiotu, np. miecz (Sword)
        FPrimaryItemInfo Primaryinfo = PrimaryIteminfo->GetInfoByType(EItemType::Sword);
        info = Primaryinfo;

        // Losuj jako?? przedmiotu
        EItemGrad Quality = DetermineItemQuality(GetProgressCommon(Progress));
        info.ItemGrade = Quality;

        // Ustaw statystyki dla danej jako?ci w zakresie
        int StatPoints = GetBaseValueForQuality(Quality);

        // Szanse na prefix i sufix w zale?no?ci od jako?ci
        float PrefixChance = GetPrefixChance(Quality); // Funkcja pomocnicza
        float SuffixChance = GetSuffixChance(Quality); // Funkcja pomocnicza

        int AttributePoints = GetAmountOfModifiers(Quality);

        int PrefixPoints = FMath::RandRange(AttributePoints - 1, AttributePoints + 1) / 2;
        int SuffixPoints = FMath::RandRange(AttributePoints - 1, AttributePoints + 1) / 2;

        //Losuj prefix (je?li wypadnie)
        if (FMath::FRand() <= PrefixChance)
        {
            FItemDescriptorPS Prefix = GetRandomElementFromTArray<FItemDescriptorPS>(ItemDescriptorInfo->PrefixInfo);
            info.ItemName = Prefix.DescriptorName + " " + info.ItemName;

            for (int j = 0; j < PrefixPoints; j++)
            {
                FEffectAttributeModifierParams NewAttributeModifier;

                NewAttributeModifier.EffectModifiedAttribute = GetRandomElementFromTArray(Prefix.EffectModifiers);

                NewAttributeModifier.EffectMagnitude = StatPoints;

                info.Modifiers.Modifiers.Add(NewAttributeModifier);
            }

        }

        // Losuj sufix (je?li wypadnie)
        if (FMath::FRand() <= SuffixChance)
        {
            FItemDescriptorPS Suffix = GetRandomElementFromTArray<FItemDescriptorPS>(ItemDescriptorInfo->SuffixInfo);
            info.ItemName = info.ItemName + " " + Suffix.DescriptorName;

            for (int j = 0; j < PrefixPoints; j++)
            {
                FEffectAttributeModifierParams NewAttributeModifier;

                NewAttributeModifier.EffectModifiedAttribute = GetRandomElementFromTArray(Suffix.EffectModifiers);

                NewAttributeModifier.EffectMagnitude = StatPoints;

                info.Modifiers.Modifiers.Add(NewAttributeModifier);
            }
        }

        // Dodaj wygenerowany przedmiot do listy
        DroppedItems.Add(info);
    }

    return DroppedItems;
}