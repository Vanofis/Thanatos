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

const TArray<FGameplayAttribute>& UHealthComponent::GetAttributeInitializationOrder()
{
	static TArray<FGameplayAttribute> Order;
	if (Order.IsEmpty())
	{
		Order.Add(UHealthAttributeSet::GetMaxHealthAttribute());
		Order.Add(UHealthAttributeSet::GetHealthAttribute());
	}
	
	return Order;
}

void UHealthComponent::PreAttributeSetInitialization_Implementation()
{
	const UHealthAttributeSet* HealthAttributeSet = GetHealthAttributeSet();
	
	HealthAttributeSet->OnHealthChanged.AddUObject(this, &ThisClass::HandleOnHealthChanged);
	HealthAttributeSet->OnMaxHealthChanged.AddUObject(this, &ThisClass::HandleOnMaxHealthChanged);
	HealthAttributeSet->OnOutOfHealth.AddUObject(this, &ThisClass::HandleOnOutOfHealth);
}

void UHealthComponent::HandleOnHealthChanged(const FOnAttributeChangeData& Data) const
{
	OnHealthChanged.Broadcast(Data.Attribute, Data.OldValue, Data.NewValue);
}

void UHealthComponent::HandleOnMaxHealthChanged(const FOnAttributeChangeData& Data) const
{
	OnMaxHealthChanged.Broadcast(Data.Attribute, Data.OldValue, Data.NewValue);
}

void UHealthComponent::HandleOnOutOfHealth(const FGameplayAttribute& Attribute, float Value) const
{
	OnOutOfHealth.Broadcast(Attribute, Value);
}

UHealthAttributeSet* UHealthComponent::GetHealthAttributeSet() const
{
	UHealthAttributeSet* HealthAttributeSet = Cast<UHealthAttributeSet>(AttributeSet);
	check(HealthAttributeSet)
	
	return HealthAttributeSet;
}
