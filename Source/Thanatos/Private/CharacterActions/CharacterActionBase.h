#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "CharacterActionBase.generated.h"

UCLASS(Blueprintable, Abstract, DefaultToInstanced, EditInlineNew)
class THANATOS_API UCharacterActionBase : public UObject
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void Apply(APawn* Pawn);
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void Undo(APawn* Pawn);
};
