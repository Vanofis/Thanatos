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
{}

bool UEnergyAttributeSet::PreGameplayEffectExecute(FGameplayEffectModCallbackData& Data)
{
	if (Data.EvaluatedData.Magnitude <= 0.0f)
	{
		return false;
	}
	
	GatheredDataPreChanged = GetGatheredData();
	HeatPreChanged = GetHeat();
	MaxHeatPreChanged = GetMaxHeat();
	EnergyPreChanged = GetEnergy();
	MaxEnergyPreChanged = GetMaxEnergy();
	
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
	
	FOnAttributeChangeData ChangeData;
	ChangeData.GEModData = &Data;
	
	if (!FMath::IsNearlyEqual(GatheredDataPreChanged, GetGatheredData()))
	{
		ChangeData.Attribute = GetGatheredDataAttribute();
		ChangeData.OldValue = GatheredDataPreChanged;
		ChangeData.NewValue = GetGatheredData();
		
		OnGatheredDataChanged.Broadcast(ChangeData);
	}
	
	if (!FMath::IsNearlyEqual(HeatPreChanged, GetHeat()))
	{
		ChangeData.Attribute = GetHeatAttribute();
		ChangeData.OldValue = HeatPreChanged;
		ChangeData.NewValue = GetHeat();
		
		OnGatheredDataChanged.Broadcast(ChangeData);
	}
	
	if (!FMath::IsNearlyEqual(MaxHeatPreChanged, GetMaxHeat()))
	{
		ChangeData.Attribute = GetMaxHeatAttribute();
		ChangeData.OldValue = MaxHeatPreChanged;
		ChangeData.NewValue = GetMaxHeat();
		
		OnGatheredDataChanged.Broadcast(ChangeData);
	}
	
	if (!FMath::IsNearlyEqual(EnergyPreChanged, GetEnergy()))
	{
		ChangeData.Attribute = GetEnergyAttribute();
		ChangeData.OldValue = EnergyPreChanged;
		ChangeData.NewValue = GetEnergy();
		
		OnGatheredDataChanged.Broadcast(ChangeData);
	}
	
	if (!FMath::IsNearlyEqual(MaxEnergyPreChanged, GetMaxEnergy()))
	{
		ChangeData.Attribute = GetMaxEnergyAttribute();
		ChangeData.OldValue = MaxEnergyPreChanged;
		ChangeData.NewValue = GetMaxEnergy();
		
		OnGatheredDataChanged.Broadcast(ChangeData);
	}
	
	if (GetHeat() >= GetMaxHeat() && !bIsHeatMax)
	{
		bIsHeatMax = true;
		
		OnOverheat.Broadcast(GetHeatAttribute(), GetHeat());
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
