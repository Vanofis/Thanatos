#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CharacterConfigurationManager.generated.h"

class UCharacterExperience;
class UCharacterExperienceAction;

UCLASS(Blueprintable, Abstract, meta=(BlueprintSpawnableComponent))
class THANATOS_API UCharacterConfigurationManager : public UActorComponent
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	TObjectPtr<UCharacterExperience> ActiveConfiguration;
	
private:
	UPROPERTY()
	TArray<TObjectPtr<UCharacterExperienceAction>> ActiveActions;

	UPROPERTY()
	TObjectPtr<AController> Controller;
	
public:
	UCharacterConfigurationManager();
	
	virtual void BeginPlay() override;
	
protected:
	UFUNCTION(BlueprintCallable)
	void SetCharacterConfiguration(UCharacterExperience* NewConfiguration);
	
	UFUNCTION(BlueprintCallable, BlueprintPure)
	AController* GetController();
	
	void ApplyConfigurationActions();
	void UndoConfigurationActions();
};
