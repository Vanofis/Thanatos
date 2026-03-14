#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "CharacterConfiguration.generated.h"

UCLASS(Blueprintable, Abstract, EditInlineNew, DefaultToInstanced)
class UMovementProcessor : public UObject
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void Move(APawn* Pawn, FVector Direction);
};

UCLASS(Blueprintable, Abstract, EditInlineNew, DefaultToInstanced)
class UCharacterConfigurationAction : public UObject
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void Apply(APawn* Pawn);
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void Undo(APawn* Pawn);
};

UCLASS(Blueprintable)
class UCharacterConfiguration : public UPrimaryDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Instanced)
	TArray<TObjectPtr<UCharacterConfigurationAction>> Actions;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Instanced)
	TObjectPtr<UMovementProcessor> MovementProcessor;
};
