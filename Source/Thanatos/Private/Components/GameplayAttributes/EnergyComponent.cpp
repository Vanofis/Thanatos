#include "EnergyComponent.h"
#include "GameplayAttributes/EnergyAttributeSet.h"

UEnergyComponent::UEnergyComponent()
{
	AttributeSetClass = UEnergyAttributeSet::StaticClass();
}

float UEnergyComponent::GetMinGatheredData()
{
	return UEnergyAttributeSet::MinGatheredData;
}

float UEnergyComponent::GetMinEnergy()
{
	return UEnergyAttributeSet::MinEnergy;	
}

float UEnergyComponent::GetMinHeat()
{
	return UEnergyAttributeSet::MinHeat;
}

const TArray<FGameplayAttribute>& UEnergyComponent::GetAttributeInitializationOrder()
{
	static TArray<FGameplayAttribute> Order;
	if (Order.IsEmpty())
	{
		Order.Add(UEnergyAttributeSet::GetGatheredDataAttribute());
		Order.Add(UEnergyAttributeSet::GetMaxHeatAttribute());
		Order.Add(UEnergyAttributeSet::GetHeatAttribute());
		Order.Add(UEnergyAttributeSet::GetMaxEnergyAttribute());
		Order.Add(UEnergyAttributeSet::GetEnergyAttribute());
	}
	
	return Order;
}

void UEnergyComponent::PreAttributeSetInitialization_Implementation()
{
	const UEnergyAttributeSet* EnergyAttributeSet = GetEnergyAttributeSet();
	
	EnergyAttributeSet->OnGatheredDataChanged.AddUObject(this, &ThisClass::HandleOnGatheredDataChanged);
	EnergyAttributeSet->OnMaxHeatChanged.AddUObject(this, &ThisClass::HandleOnMaxHeatChanged);
	EnergyAttributeSet->OnHeatChanged.AddUObject(this, &ThisClass::HandleOnHeatChanged);
	EnergyAttributeSet->OnMaxEnergyChanged.AddUObject(this, &ThisClass::HandleOnMaxEnergyChanged);
	EnergyAttributeSet->OnEnergyChanged.AddUObject(this, &ThisClass::HandleOnEnergyChanged);
	EnergyAttributeSet->OnOverheat.AddUObject(this, &ThisClass::HandleOnOverheat);
}

UEnergyAttributeSet* UEnergyComponent::GetEnergyAttributeSet() const
{
	UEnergyAttributeSet* EnergyAttributeSet = Cast<UEnergyAttributeSet>(AttributeSet);
	check(EnergyAttributeSet);
	
	return EnergyAttributeSet;
}

void UEnergyComponent::HandleOnGatheredDataChanged(const FOnAttributeChangeData& Data) const
{
	OnGatheredDataChanged.Broadcast(Data.Attribute, Data.OldValue, Data.NewValue);
}

void UEnergyComponent::HandleOnHeatChanged(const FOnAttributeChangeData& Data) const
{
	OnHeatChanged.Broadcast(Data.Attribute, Data.OldValue, Data.NewValue);
}

void UEnergyComponent::HandleOnMaxHeatChanged(const FOnAttributeChangeData& Data) const
{
	OnMaxHeatChanged.Broadcast(Data.Attribute, Data.OldValue, Data.NewValue);
}

void UEnergyComponent::HandleOnEnergyChanged(const FOnAttributeChangeData& Data) const
{
	OnEnergyChanged.Broadcast(Data.Attribute, Data.OldValue, Data.NewValue);
}

void UEnergyComponent::HandleOnMaxEnergyChanged(const FOnAttributeChangeData& Data) const
{
	OnMaxEnergyChanged.Broadcast(Data.Attribute, Data.OldValue, Data.NewValue);
}

void UEnergyComponent::HandleOnOverheat(const FGameplayAttribute& Attribute, float Value) const
{
	OnOverheat.Broadcast(Attribute, Value);
}

