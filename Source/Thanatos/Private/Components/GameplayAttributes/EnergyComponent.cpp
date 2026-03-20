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

TArray<FGameplayAttribute> UEnergyComponent::GetAttributeInitializationOrder()
{
	TArray<FGameplayAttribute> Order;
	Order.Add(UEnergyAttributeSet::GetGatheredDataAttribute());
	Order.Add(UEnergyAttributeSet::GetMaxHeatAttribute());
	Order.Add(UEnergyAttributeSet::GetHeatAttribute());
	Order.Add(UEnergyAttributeSet::GetMaxEnergyAttribute());
	Order.Add(UEnergyAttributeSet::GetEnergyAttribute());
	
	return MoveTemp(Order);
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

void UEnergyComponent::HandleOnGatheredDataChanged(
	const FGameplayAttribute& Attribute, 
	const float OldValue, 
	const float NewValue) 
const
{
	OnGatheredDataChanged.Broadcast(Attribute, OldValue, NewValue);
}

void UEnergyComponent::HandleOnHeatChanged(
	const FGameplayAttribute& Attribute, 
	const float OldValue, 
	const float NewValue) 
const
{
	OnHeatChanged.Broadcast(Attribute, OldValue, NewValue);
}

void UEnergyComponent::HandleOnMaxHeatChanged(
	const FGameplayAttribute& Attribute, 
	const float OldValue, 
	const float NewValue) 
const
{
	OnMaxHeatChanged.Broadcast(Attribute, OldValue, NewValue);
}

void UEnergyComponent::HandleOnEnergyChanged(
	const FGameplayAttribute& Attribute, 
	const float OldValue, 
	const float NewValue) 
const
{
	OnEnergyChanged.Broadcast(Attribute, OldValue, NewValue);
}

void UEnergyComponent::HandleOnMaxEnergyChanged(
	const FGameplayAttribute& Attribute, 
	const float OldValue, 
	const float NewValue) 
const
{
	OnMaxEnergyChanged.Broadcast(Attribute, OldValue, NewValue);
}

void UEnergyComponent::HandleOnOverheat(const FGameplayAttribute& Attribute, float Value) const
{
	OnOverheat.Broadcast(Attribute, Value);
}

