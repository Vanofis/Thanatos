#include "CharacterConfigurationAction_GrantAbilities.h"
#include "AbilitySystemComponent.h"

void UCharacterConfigurationAction_GrantAbilities::Apply_Implementation(APawn* Pawn)
{
	UAbilitySystemComponent* AbilitySystemComponent = Pawn->FindComponentByClass<UAbilitySystemComponent>();
	for (const auto& AbilityClass : GameplayAbilities)
	{
		GrantedAbilities.Add(AbilitySystemComponent->GiveAbility(AbilityClass));
	}
}

void UCharacterConfigurationAction_GrantAbilities::Undo_Implementation(APawn* Pawn)
{
	UAbilitySystemComponent* AbilitySystemComponent = Pawn->FindComponentByClass<UAbilitySystemComponent>();
	while (!GrantedAbilities.IsEmpty())
	{
		AbilitySystemComponent->ClearAbility(GrantedAbilities.Pop());
	}
}
