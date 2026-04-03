#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Thanatos_GameplayTagBlueprintFunctionLibrary.generated.h"

UCLASS()
class THANATOS_API UThanatos_GameplayTagBlueprintFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, DisplayName = "Sort Gameplay Tags")
	static TArray<FGameplayTag> SortGameplayTags(TArray<FGameplayTag> Tags);
};
