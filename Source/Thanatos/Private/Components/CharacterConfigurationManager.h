#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CharacterConfigurationManager.generated.h"

class UCharacterConfiguration;
class UCharacterConfigurationAction;

UCLASS(Blueprintable, Abstract, meta=(BlueprintSpawnableComponent))
class THANATOS_API UCharacterConfigurationManager : public UActorComponent
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	TObjectPtr<UCharacterConfiguration> ActiveConfiguration;
	
private:
	UPROPERTY()
	TArray<TObjectPtr<UCharacterConfigurationAction>> ActiveActions;

	UPROPERTY()
	TObjectPtr<AController> Controller;
	
public:
	UCharacterConfigurationManager();
	
protected:
	UFUNCTION(BlueprintCallable)
	void SetCharacterConfiguration(UCharacterConfiguration* NewConfiguration);
	
	UFUNCTION(BlueprintCallable, BlueprintPure)
	AController* GetController();
	
	void ApplyConfigurationActions();
	void UndoConfigurationActions();
};
