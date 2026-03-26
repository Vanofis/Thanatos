#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CharacterExperienceManagerBase.generated.h"

class UCharacterExperience;
class UCharacterExperienceAction;

UCLASS(Blueprintable, Abstract)
class THANATOS_API UCharacterExperienceManagerBase : public UActorComponent
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	TObjectPtr<UCharacterExperience> ActiveExperience;
	
private:
	UPROPERTY()
	TArray<TObjectPtr<UCharacterExperienceAction>> ActiveActions;

	UPROPERTY()
	TObjectPtr<AController> Controller;
	
public:
	UCharacterExperienceManagerBase();
	
	virtual void BeginPlay() override;
	
protected:
	UFUNCTION(BlueprintCallable)
	void SetCharacterExperience(UCharacterExperience* NewConfiguration);
	
	UFUNCTION(BlueprintCallable, BlueprintPure)
	AController* GetController();
	
	void ApplyExperienceActions();
	void UndoExperienceActions();
};
