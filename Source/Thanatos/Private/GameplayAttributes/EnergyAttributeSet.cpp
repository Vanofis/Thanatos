#include "EnergyAttributeSet.h"
#include "GameplayEffectExtension.h"

UEnergyAttributeSet::UEnergyAttributeSet()
	: GatheredData(MinGatheredData)
	, Heat(MinHeat)
	, MaxHeat(100.0f)
	, HeatDecrease(0.0f)
	, HeatIncrease(0.0f)
	, Energy(MinEnergy)
	, MaxEnergy(100.0f)
	, EnergyDamage(0.0f)
	, EnergyRestoration(0.0f)
	, bIsHeatMax(false)
{}

bool UEnergyAttributeSet::PreGameplayEffectExecute(FGameplayEffectModCallbackData& Data)
{
	if (Data.EvaluatedData.Magnitude <= 0.0f)
	{
		return false;
	}
	
	return Super::PreGameplayEffectExecute(Data);
}

void UEnergyAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);
	
	const FGameplayAttribute& Attribute = Data.EvaluatedData.Attribute;
	if (Attribute == GetGatheredDataAttribute())
	{
		SetGatheredData(FMath::Max(MinGatheredData, GetGatheredData()));
	}
	else if (Attribute == GetHeatAttribute())
	{
		SetHeat(FMath::Max(0.0f, GetHeat()));
	}
	else if (Attribute == GetMaxHeatAttribute())
	{
		SetMaxHeat(FMath::Max(MinHeat, GetMaxHeat()));
		SetHeat(MinHeat);
	}
	else if (Attribute == GetHeatDecreaseAttribute())
	{
		SetHeat(FMath::Max(GetHeat() - GetHeatDecrease(), MinHeat));
		SetHeatDecrease(0.0f);
	}
	else if (Attribute == GetHeatIncreaseAttribute())
	{
		SetHeat(GetHeat() + GetHeatIncrease());
		SetHeatIncrease(0.0f);
	}
	else if (Attribute == GetEnergyAttribute())
	{
		SetEnergy(FMath::Clamp(GetEnergy(), MinEnergy, GetMaxEnergy()));
	}
	else if (Attribute == GetMaxEnergyAttribute())
	{
		SetEnergy(GetMaxEnergy());
	}
	else if (Attribute == GetEnergyDamageAttribute())
	{
		SetEnergy(FMath::Clamp(GetEnergy() - GetEnergyDamage(), MinEnergy, GetMaxEnergy()));
		SetEnergyDamage(0.0f);
	}
	else if (Attribute == GetEnergyRestorationAttribute())
	{
		SetEnergy(FMath::Clamp(GetEnergy() + GetEnergyRestoration(), MinEnergy, GetMaxEnergy()));
		SetEnergyRestoration(0.0f);
	}
}

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
		
		if (!bIsHeatMax && NewValue >= GetMaxHeat())
		{
			bIsHeatMax = true;
			
			OnOverheat.Broadcast(Attribute, NewValue);
		}
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
	}
}
