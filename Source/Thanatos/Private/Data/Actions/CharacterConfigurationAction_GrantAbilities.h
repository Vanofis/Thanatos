#pragma once

#include "CoreMinimal.h"
#include "GameplayAbilitySpecHandle.h"
#include "Data/CharacterConfiguration.h"
#include "CharacterConfigurationAction_GrantAbilities.generated.h"

class UGameplayAbility;

UCLASS(DisplayName="Grant Abilities")
class THANATOS_API UCharacterConfigurationAction_GrantAbilities : public UCharacterConfigurationAction
{
	GENERATED_BODY()
	
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="Character Configuration Action", meta=(AllowPrivateAccess=true))
	TArray<TSubclassOf<UGameplayAbility>> GameplayAbilities;
	
	TArray<FGameplayAbilitySpecHandle> GrantedAbilities;
	
public:
	virtual void Apply_Implementation(APawn* Pawn) override;
	virtual void Undo_Implementation(APawn* Pawn) override;
};
