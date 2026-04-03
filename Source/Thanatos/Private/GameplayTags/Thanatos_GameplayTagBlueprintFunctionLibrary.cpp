#include "Thanatos_GameplayTagBlueprintFunctionLibrary.h"

TArray<FGameplayTag> UThanatos_GameplayTagBlueprintFunctionLibrary::SortGameplayTags(TArray<FGameplayTag> Tags)
{
	Tags.Sort([](const FGameplayTag A, const FGameplayTag B)
	{
		return A.ToString() < B.ToString();
	});
	
	return Tags;
}
