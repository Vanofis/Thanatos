#include "EnergyAttributeSet.h"

UEnergyAttributeSet::UEnergyAttributeSet()
	: GatheredData(0.0f)
	, Heat(0.0f)
	, MaxHeat(1.0f)
	, Energy(0.0f)
	, MaxEnergy(0.0f)
	, bIsHeatMax(false)
{}

void UEnergyAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	if (Attribute == GetGatheredDataAttribute())
	{
		NewValue = FMath::Max(NewValue, 0.0f);
	}
	else if (Attribute == GetHeatAttribute())
	{
		NewValue = FMath::Max(NewValue, MinHeat);
	}
	else if (Attribute == GetEnergyAttribute())
	{
		NewValue = FMath::Clamp(NewValue, MinEnergy, GetMaxEnergy());
	}
}

void UEnergyAttributeSet::PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue)
{
	if (FMath::IsNearlyEqual(OldValue, NewValue))
	{
		return;
	}
	
	if (Attribute == GetGatheredDataAttribute())
	{
		OnGatheredDataChanged.Broadcast(Attribute, OldValue, NewValue);
	}
	else if (Attribute == GetHeatAttribute())
	{
		OnHeatChanged.Broadcast(Attribute, OldValue, NewValue);
	}
	else if (Attribute == GetMaxHeatAttribute())
	{
		OnMaxHeatChanged.Broadcast(Attribute, OldValue, NewValue);
	}
	else if (Attribute == GetEnergyAttribute())
	{
		OnEnergyChanged.Broadcast(Attribute, OldValue, NewValue);
	}
	else if (Attribute == GetMaxEnergyAttribute())
	{
		OnMaxEnergyChanged.Broadcast(Attribute, OldValue, NewValue);
		
		if (GetEnergy() > GetMaxEnergy())
		{
			GetOwningAbilitySystemComponentChecked()->ApplyModToAttribute(
				GetEnergyAttribute(), 
				EGameplayModOp::Override,
				GetMaxEnergy()
				);
		}
	}
	
	if (!bIsHeatMax && NewValue >= GetMaxHeat())
	{
		bIsHeatMax = true;
		
		OnOverheat.Broadcast(Attribute, NewValue);
	}
}
