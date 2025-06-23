// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Data/ElementsReactionMap.h"

bool UElementsReactionMap::IsTagReactive(FGameplayTag MainTag, FGameplayTagContainer TagsToCheck)
{
	for (auto elem : ElementsInformation)
	{
		UE_LOG(LogTemp, Warning, TEXT("Checking MainTag: %s"), *MainTag.ToString());
		UE_LOG(LogTemp, Warning, TEXT("Against ElementTag: %s"), *elem.ElementTag.ToString());

		if (elem.ElementTag == MainTag)
		{
			UE_LOG(LogTemp, Warning, TEXT("Matching ElementTag Found"));

			if (TagsToCheck.HasAnyExact(elem.ReactionElementTags))
			{
				UE_LOG(LogTemp, Warning, TEXT("Reaction Tag Found: %s"), *elem.ReactionElementTags.ToString());
				return true;
			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("Reaction Tags didn't match. Checking: %s"), *TagsToCheck.ToString());
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
