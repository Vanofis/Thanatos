#include "CharacterConfigurationManager.h"
#include "Data/CharacterExperience.h"

UCharacterConfigurationManager::UCharacterConfigurationManager()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UCharacterConfigurationManager::BeginPlay()
{
	if (ActiveConfiguration)
	{
		ApplyConfigurationActions();
	}
	
	Super::BeginPlay();
}

void UCharacterConfigurationManager::SetCharacterConfiguration(UCharacterExperience* NewConfiguration)
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
		ActiveActions.Add(DuplicateObject<UCharacterExperienceAction>(Action, this));
		
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

