#include "HealthComponent.h"
#include "GameplayAttributes/HealthAttributeSet.h"

UHealthComponent::UHealthComponent()
{
	AttributeSetClass = UHealthAttributeSet::StaticClass();
}

float UHealthComponent::GetMinHealth()
{
	return UHealthAttributeSet::MinHealth;
}

float UHealthComponent::GetDamageMultiplier(const FGameplayTag MultiplierTag) const
{
	const float* DamageMultiplierPtr = DamageModifiers.Find(MultiplierTag);
	if (!DamageMultiplierPtr)
	{
		return 0.0f;
	}
	
	return *DamageMultiplierPtr;
}

TArray<FGameplayAttribute> UHealthComponent::GetAttributeInitializationOrder()
{
	TArray<FGameplayAttribute> Order;
	Order.Add(UHealthAttributeSet::GetMaxHealthAttribute());
	Order.Add(UHealthAttributeSet::GetHealthAttribute());
	
	return MoveTemp(Order);
}

void UHealthComponent::PreAttributeSetInitialization_Implementation()
{
	const UHealthAttributeSet* HealthAttributeSet = GetHealthAttributeSet();
	
	HealthAttributeSet->OnHealthChanged.AddUObject(this, &ThisClass::HandleOnHealthChanged);
	HealthAttributeSet->OnMaxHealthChanged.AddUObject(this, &ThisClass::HandleOnMaxHealthChanged);
	HealthAttributeSet->OnOutOfHealth.AddUObject(this, &ThisClass::HandleOnOutOfHealth);
}

UHealthAttributeSet* UHealthComponent::GetHealthAttributeSet() const
{
	UHealthAttributeSet* HealthAttributeSet = Cast<UHealthAttributeSet>(AttributeSet);
	check(HealthAttributeSet)
	
	return HealthAttributeSet;
}

void UHealthComponent::HandleOnHealthChanged(
	const FGameplayAttribute& Attribute, 
	const float OldValue, 
	const float NewValue) 
const
{
	OnHealthChanged.Broadcast(Attribute, OldValue, NewValue);
}

void UHealthComponent::HandleOnMaxHealthChanged(
	const FGameplayAttribute& Attribute, 
	const float OldValue,
	const float NewValue) 
const
{
	OnMaxHealthChanged.Broadcast(Attribute, OldValue, NewValue);
}

void UHealthComponent::HandleOnOutOfHealth(const FGameplayAttribute& Attribute, float Value) const
{
	OnOutOfHealth.Broadcast(Attribute, Value);
}