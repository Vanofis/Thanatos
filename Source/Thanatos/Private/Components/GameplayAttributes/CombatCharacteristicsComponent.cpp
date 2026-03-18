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

const TArray<FGameplayAttribute>& UCombatCharacteristicsComponent::GetAttributeInitializationOrder()
{
	static TArray<FGameplayAttribute> Order;
	if (Order.IsEmpty())
	{
		Order.Add(UCombatCharacteristicsAttributeSet::GetMeleeDamageAttribute());
		Order.Add(UCombatCharacteristicsAttributeSet::GetRangedDamageAttribute());
		Order.Add(UCombatCharacteristicsAttributeSet::GetArmorAttribute());
	}
	
	return Order;
}

