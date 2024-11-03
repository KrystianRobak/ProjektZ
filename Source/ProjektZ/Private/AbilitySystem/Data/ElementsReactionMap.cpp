// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Data/ElementsReactionMap.h"

bool UElementsReactionMap::IsTagReactive(FGameplayTag MainTag, FGameplayTagContainer TagsToCheck)
{
	for (auto elem : ElementsInformation)
	{
		if (elem.ElementTag == MainTag)
		{
			return elem.ReactionElementTags.HasAnyExact(TagsToCheck);
		}
	}
	return false;
}
