#include "CharacterExperienceManagerBase.h"
#include "Data/CharacterExperience.h"

UCharacterExperienceManagerBase::UCharacterExperienceManagerBase()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UCharacterExperienceManagerBase::BeginPlay()
{
	if (ActiveExperience)
	{
		ApplyExperienceActions();
	}
	
	Super::BeginPlay();
}

void UCharacterExperienceManagerBase::SetCharacterExperience(UCharacterExperience* NewConfiguration)
{
	if (ActiveExperience)
	{
		UndoExperienceActions();
	}
	
	ActiveExperience = NewConfiguration;
	if (ActiveExperience)
	{
		ApplyExperienceActions();
	}
}

AController* UCharacterExperienceManagerBase::GetController()
{
	if (Controller)
	{
		return Controller;
	}
	
	Controller = Cast<AController>(GetOwner());
	return Controller;
}

void UCharacterExperienceManagerBase::ApplyExperienceActions()
{
	for (const auto& Action : ActiveExperience->Actions)
	{
		ActiveActions.Add(DuplicateObject<UCharacterExperienceAction>(Action, this));
		
		const auto Last = ActiveActions.Last();
		Last->Apply(GetController()->GetPawn());
	}
}

void UCharacterExperienceManagerBase::UndoExperienceActions()
{
	while (!ActiveActions.IsEmpty())
	{
		ActiveActions.Pop()->Undo(GetController()->GetPawn());
	}
}

