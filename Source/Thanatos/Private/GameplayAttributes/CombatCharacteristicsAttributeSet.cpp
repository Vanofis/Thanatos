#include "CombatCharacteristicsAttributeSet.h"

UCombatCharacteristicsAttributeSet::UCombatCharacteristicsAttributeSet()
	: MeleeDamage(MinMeleeDamage)
	, RangedDamage(MinRangedDamage)
	, Armor(MinArmor)
{}

void UCombatCharacteristicsAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	if (Attribute == GetMeleeDamageAttribute())
	{
		NewValue = FMath::Max(NewValue, MinMeleeDamage);
	}
	else if (Attribute == GetRangedDamageAttribute())
	{
		NewValue = FMath::Max(NewValue, MinRangedDamage);
	}
	else if (Attribute == GetArmorAttribute())
	{
		NewValue = FMath::Max(NewValue, MinArmor);
	}
}
