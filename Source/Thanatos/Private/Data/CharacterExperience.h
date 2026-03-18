#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "CharacterExperience.generated.h"

UCLASS(Blueprintable, Abstract, EditInlineNew, DefaultToInstanced)
class THANATOS_API UMovementProcessor : public UObject
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void Move(APawn* Pawn, FVector Direction);
};

UCLASS(Blueprintable, Abstract, EditInlineNew, DefaultToInstanced)
class THANATOS_API UCharacterExperienceAction : public UObject
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void Apply(APawn* Pawn);
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void Undo(APawn* Pawn);
};

UCLASS(Blueprintable)
class THANATOS_API UCharacterExperience : public UPrimaryDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Instanced)
	TArray<TObjectPtr<UCharacterExperienceAction>> Actions;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Instanced)
	TObjectPtr<UMovementProcessor> MovementProcessor;
};
