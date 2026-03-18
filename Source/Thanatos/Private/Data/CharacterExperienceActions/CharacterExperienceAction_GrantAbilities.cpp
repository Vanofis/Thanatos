#include "CharacterExperienceAction_GrantAbilities.h"
#include "AbilitySystemComponent.h"

void UCharacterExperienceAction_GrantAbilities::Apply_Implementation(APawn* Pawn)
{
	UAbilitySystemComponent* AbilitySystemComponent = Pawn->FindComponentByClass<UAbilitySystemComponent>();
	for (const auto& AbilityClass : GameplayAbilities)
	{
		GrantedAbilities.Add(AbilitySystemComponent->GiveAbility(AbilityClass));
	}
}

void UCharacterExperienceAction_GrantAbilities::Undo_Implementation(APawn* Pawn)
{
	UAbilitySystemComponent* AbilitySystemComponent = Pawn->FindComponentByClass<UAbilitySystemComponent>();
	while (!GrantedAbilities.IsEmpty())
	{
		AbilitySystemComponent->ClearAbility(GrantedAbilities.Pop());
	}
}
