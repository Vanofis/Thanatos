#include "CombatCharacteristicsComponent.h"
#include "GameplayAttributes/CombatCharacteristicsAttributeSet.h"

UCombatCharacteristicsComponent::UCombatCharacteristicsComponent()
{
	AttributeSetClass = UCombatCharacteristicsAttributeSet::StaticClass();
}

float UCombatCharacteristicsComponent::GetMinMeleeDamage()
{
	return UCombatCharacteristicsAttributeSet::MinMeleeDamage;
}

float UCombatCharacteristicsComponent::GetMinRangedDamage()
{
	return UCombatCharacteristicsAttributeSet::MinRangedDamage;
}

float UCombatCharacteristicsComponent::GetMinArmor()
{
	return UCombatCharacteristicsAttributeSet::MinArmor;
}

