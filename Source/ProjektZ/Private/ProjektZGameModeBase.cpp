// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjektZGameModeBase.h"

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

EItemGrad DetermineItemQuality()
{
    float Roll = FMath::FRand();

    if (Roll < 0.5f) return EItemGrad::Common;        // 50% szans
    else if (Roll < 0.8f) return EItemGrad::Rare;     // 30% szans
    else if (Roll < 0.95f) return EItemGrad::Legendary; // 15% szans
    else return EItemGrad::Mythic;                 // 5% szans
}

//template<typename T>
//T GetRandomElementFromTArray(TArray<T> ArrayToCheck)
//{
//    return ArrayToCheck.begin();
//}

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
        EItemGrad Quality = DetermineItemQuality();
        info.ItemGrade = Quality;

        // Ustaw bazowe statystyki dla danej jakoœci
        int BaseValue = GetBaseValueForQuality(Quality); // Funkcja pomocnicza
        int StatPoints = FMath::RandRange(BaseValue - 30, BaseValue + 30);

        // Szanse na prefix i sufix w zale¿noœci od jakoœci
        float PrefixChance = GetPrefixChance(Quality); // Funkcja pomocnicza
        float SuffixChance = GetPrefixChance(Quality); // Funkcja pomocnicza

        // Losuj prefix (jeœli wypadnie)
        //if (FMath::FRand() < PrefixChance)
        //{
        //    FItemDescriptorPS Prefix = GetRandomElementFromTArray<FItemDescriptorPS>(ItemDescriptorInfo->PrefixInfo);
        //    info.ItemName = Prefix.DescriptorName + " " + info.ItemName;


        //   // info.Attributes.Append(Prefix.Attributes); // Dodaj atrybuty z prefixu
        //    
        //}

        //// Losuj sufix (jeœli wypadnie)
        //if (FMath::FRand() < SuffixChance)
        //{
        //    FItemDescriptorPS Sufix = GetRandomElementFromTArray<FItemDescriptorPS>(ItemDescriptorInfo->SufixInfo);
        //    //info.Attributes.Append(Sufix.Attributes); // Dodaj atrybuty z sufixu
        //    //info.Suffix = Sufix;
        //}

        // Dodaj wygenerowany przedmiot do listy
        DroppedItems.Add(info);
    }

    return DroppedItems;
}
