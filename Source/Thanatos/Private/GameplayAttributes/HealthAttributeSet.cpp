#include "HealthAttributeSet.h"
#include "GameplayEffectExtension.h"

UHealthAttributeSet::UHealthAttributeSet()
	: Health(100.0f)
	, MaxHealth(100.0f)
	, HealthDamage(0.0f)
	, HealthRestoration(0.0f)
{}

bool UHealthAttributeSet::PreGameplayEffectExecute(FGameplayEffectModCallbackData& Data)
{
	if (Data.EvaluatedData.Magnitude <= 0.0f)
	{
		return false;
	}
	
	HealthPreChanged = GetHealth();
	MaxHealthPreChanged = GetMaxHealth();
	
	return Super::PreGameplayEffectExecute(Data);
}

void UHealthAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);
	
	const FGameplayAttribute& Attribute = Data.EvaluatedData.Attribute;
	if (Attribute == GetHealthAttribute())
	{
		SetHealth(FMath::Clamp(GetHealth(), MinHealth, GetMaxHealth()));
	}
	else if (Attribute == GetMaxHealthAttribute())
	{
		SetMaxHealth(FMath::Max(1.0f, GetMaxHealth()));
		SetHealth(FMath::Clamp(GetHealth(), MinHealth, GetMaxHealth()));
	}
	else if (Attribute == GetHealthDamageAttribute())
	{
		SetHealth(FMath::Clamp(GetHealth() - GetHealthDamage(), MinHealth, GetMaxHealth()));
		SetHealthDamage(0.0f);
	}
	else if (Attribute == GetHealthRestorationAttribute())
	{
		SetHealth(FMath::Clamp(GetHealth() + GetHealthRestoration(), MinHealth, GetMaxHealth()));
		SetHealthDamage(0.0f);
	}
	
	FOnAttributeChangeData ChangeData;
	ChangeData.GEModData = &Data;
	
	if (!FMath::IsNearlyEqual(GetHealth(), HealthPreChanged))
	{
		ChangeData.Attribute = GetHealthAttribute();
		ChangeData.NewValue = GetHealth();
		ChangeData.OldValue = HealthPreChanged;
		
		OnHealthChanged.Broadcast(ChangeData);
	}
	
	if (!FMath::IsNearlyEqual(GetMaxHealth(), MaxHealthPreChanged))
	{
		ChangeData.Attribute = GetMaxHealthAttribute();
		ChangeData.NewValue = GetMaxHealth();
		ChangeData.OldValue = MaxHealthPreChanged;
		
		OnMaxHealthChanged.Broadcast(ChangeData);
	}
	
	if (FMath::IsNearlyEqual(GetHealth(), MinHealth))
	{
		OnOutOfHealth.Broadcast(GetHealthAttribute(), MinHealth);
	}
}

void UHealthAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	if (Attribute == GetHealthAttribute())
	{
		NewValue = FMath::Clamp(NewValue, MinHealth, GetMaxHealth());
	}
}
