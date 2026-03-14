#include "CharacterConfigurationManager.h"
#include "Data/CharacterConfiguration.h"

UCharacterConfigurationManager::UCharacterConfigurationManager()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UCharacterConfigurationManager::SetCharacterConfiguration(UCharacterConfiguration* NewConfiguration)
{
	if (ActiveConfiguration)
	{
		UndoConfigurationActions();
	}
	
	ActiveConfiguration = NewConfiguration;
	if (ActiveConfiguration)
	{
		ApplyConfigurationActions();
	}
}

AController* UCharacterConfigurationManager::GetController()
{
	if (Controller)
	{
		return Controller;
	}
	
	Controller = Cast<AController>(GetOwner());
	return Controller;
}

void UCharacterConfigurationManager::ApplyConfigurationActions()
{
	for (const auto& Action : ActiveConfiguration->Actions)
	{
		ActiveActions.Add(DuplicateObject<UCharacterConfigurationAction>(Action, this));
		
		const auto Last = ActiveActions.Last();
		Last->Apply(GetController()->GetPawn());
	}
}

void UCharacterConfigurationManager::UndoConfigurationActions()
{
	while (!ActiveActions.IsEmpty())
	{
		ActiveActions.Pop()->Undo(GetController()->GetPawn());
	}
}

