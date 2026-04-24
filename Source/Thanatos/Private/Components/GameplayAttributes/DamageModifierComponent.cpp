#include "DamageModifierComponent.h"

bool FDamageRule::Matches(const FDamageContext& Other) const
{
	const bool WeaponTypesMatch = Context.WeaponTypes.HasAllExact(Other.WeaponTypes) || Context.WeaponTypes.IsEmpty();
	const bool DamageTypesMatch = Context.DamageType.HasAllExact(Other.DamageType) || Context.DamageType.IsEmpty();
	
	return WeaponTypesMatch && DamageTypesMatch;
}

TMap<FGameplayAttribute, float> UDamageModifierComponent::GetAttributesDamage(
	const FDamageContext& Context, 
	const float BaseDamage)
const
{
	TMap<FGameplayAttribute, float> FinalDamages;
	for (const auto& Rule : DamageRules)
	{
		if (!Rule.Matches(Context))
		{
			continue;
		}
		
		const TMap<FGameplayAttribute, float>& RuleMultipliers = Rule.AttributeMultipliers;
		for (const auto& RuleMultiplierKVP : RuleMultipliers)
		{
			FinalDamages.FindOrAdd(RuleMultiplierKVP.Key, DefaultModifier);
			FinalDamages[RuleMultiplierKVP.Key] *= RuleMultiplierKVP.Value;
		}
	}
	
	for (auto& FinalDamageKVP : FinalDamages)
	{
		FinalDamages[FinalDamageKVP.Key] *= BaseDamage;
	}
	
	return FinalDamages;
}
