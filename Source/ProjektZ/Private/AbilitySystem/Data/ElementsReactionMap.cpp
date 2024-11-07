// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Data/ElementsReactionMap.h"

bool UElementsReactionMap::IsTagReactive(FGameplayTag MainTag, FGameplayTagContainer TagsToCheck)
{
	for (auto elem : ElementsInformation)
	{
		if (elem.ElementTag == MainTag)
		{
			if (TagsToCheck.HasAnyExact(elem.ReactionElementTags))
			{
				return true;
			}
		}
	}

	return false;
}

FGameplayTag UElementsReactionMap::GetReactiveTag(FGameplayTag MainTag, FGameplayTag TagToCheck)
{
	for (auto elem : ElementsInformation)
	{
		if (elem.ElementTag == MainTag)
		{
			for (FGameplayTag tag : elem.ReactionElementTags)
			{
				if (tag.MatchesTagExact(TagToCheck))
				{
					return tag;
				}
			}
		}
	}
	return FGameplayTag();
}
