// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjektZGameModeBase.h"

float GetProgressCommon(int Progress){

    if (Progress == 0) return 0.0f;
    return FMath::Clamp(Progress / 10.f, 0.0f, 1.0f);
}

float GetPrefixChance(EItemGrad Quality)
{
    switch (Quality)
    {
    case EItemGrad::Common: return 0.10f;  // 10%
    case EItemGrad::Rare: return 0.25f;    // 25%
    case EItemGrad::Legendary: return 0.50f; // 50%
    case EItemGrad::Mythic: return 0.05;
    default: return 0;
    }
}

int GetAmountOfModifiers(EItemGrad Quality)
{
    switch (Quality)
    {
    case EItemGrad::Common: return 2;  // 10%
    case EItemGrad::Rare: return 3;    // 25%
    case EItemGrad::Legendary: return 4; // 50%
    case EItemGrad::Mythic: return 5;
    default: return 0;
    }
}

int GetBaseValueForQuality(EItemGrad Quality)
{
    switch (Quality)
    {
    case EItemGrad::Common: return 50;
    case EItemGrad::Rare: return 100;
    case EItemGrad::Legendary: return 150;
    case EItemGrad::Mythic: return 200;
    default: return 0;
    }
}

EItemGrad DetermineItemQuality(float ProgressCommon)
{
    float Roll = FMath::FRand();

    float CommonChance = FMath::Lerp(0.50f, 0.15f, ProgressCommon);
    float RareChance = FMath::Lerp(0.30f, 0.45f, ProgressCommon);
    float LegendaryChance = FMath::Lerp(0.15f, 0.25f, ProgressCommon);
    float MythicChance = FMath::Lerp(0.05f, 0.15f, ProgressCommon);

    float TotalChance = CommonChance + RareChance + LegendaryChance + MythicChance;
    CommonChance /= TotalChance;
    RareChance /= TotalChance;
    LegendaryChance /= TotalChance;
    MythicChance /= TotalChance;

    if (Roll < CommonChance) return EItemGrad::Common; // 50% -> 15%
    else if (Roll < CommonChance + RareChance) return EItemGrad::Rare; // 30% -> 45%
    else if (Roll < CommonChance + RareChance + LegendaryChance) return EItemGrad::Legendary; // 15% -> 25%
    else return EItemGrad::Mythic; //5% -> 15%
}

template<typename T>
T GetRandomElementFromTArray(TArray<T> ArrayToCheck)
{
    return ArrayToCheck[FMath::RandRange(0, ArrayToCheck.Num()-1)];
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

        // Losuj jakoœæ przedmiotu
        EItemGrad Quality = DetermineItemQuality(GetProgressCommon(Progress));
        info.ItemGrade = Quality;

        // Ustaw bazowe statystyki dla danej jakoœci
        int BaseValue = GetBaseValueForQuality(Quality); // Funkcja pomocnicza
        int StatPoints = FMath::RandRange(BaseValue - 30, BaseValue + 30);

        // Szanse na prefix i sufix w zale¿noœci od jakoœci
        float PrefixChance = GetPrefixChance(Quality); // Funkcja pomocnicza
        float SuffixChance = GetPrefixChance(Quality); // Funkcja pomocnicza

        int AttributePoints = GetAmountOfModifiers(Quality);

        int PrefixPoints = AttributePoints / 2;
        int SuffixPoints = AttributePoints - PrefixPoints;

        //Losuj prefix (jeœli wypadnie)
        if (FMath::FRand() < PrefixChance)
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

        // Losuj sufix (jeœli wypadnie)
        if (FMath::FRand() < SuffixChance)
        {
            FItemDescriptorPS Suffix = GetRandomElementFromTArray<FItemDescriptorPS>(ItemDescriptorInfo->SuffixInfo);
            info.ItemName =   info.ItemName + " " + Suffix.DescriptorName;

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


