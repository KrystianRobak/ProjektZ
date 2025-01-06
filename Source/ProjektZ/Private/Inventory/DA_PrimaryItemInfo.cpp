// Fill out your copyright notice in the Description page of Project Settings.


#include "Inventory/DA_PrimaryItemInfo.h"

FPrimaryItemInfo UDA_PrimaryItemInfo::GetInfoByType(EItemType ItemType)
{
    for (FPrimaryItemInfo& ItemData : ItemInformation)
    {
        if (ItemData.ItemType == ItemType)
        {
            return ItemData;
        }
    }
    return FPrimaryItemInfo();
}
