#include "MovementMultipliersAttributeSet.h"
#include "GameplayEffectExtension.h"

UMovementMultipliersAttributeSet::UMovementMultipliersAttributeSet()
	: MaxAccelerationMult(1.0f)
	, MaxWalkSpeedMult(1.0f)
	, BrakingDecelerationWalkingMult(1.0f)
	, MaxFlySpeedMult(1.0f)
	, BrakingDecelerationFlyingMult(1.0f)
{}

bool UMovementMultipliersAttributeSet::PreGameplayEffectExecute(FGameplayEffectModCallbackData& Data)
{
	if (Data.EvaluatedData.Magnitude <= 0.0f)
	{
		return false;
	}
	
	return Super::PreGameplayEffectExecute(Data);
}

void UMovementMultipliersAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	NewValue = FMath::Max(0.0f, NewValue);
}

void UMovementMultipliersAttributeSet::PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue)
{
	if (FMath::IsNearlyEqual(OldValue, NewValue))
	{
		return;
	}
	
	if (Attribute == GetMaxAccelerationMultAttribute())
	{
		OnMaxAccelerationMultChanged.Broadcast(Attribute, OldValue, NewValue);
	}
	else if (Attribute == GetMaxWalkSpeedMultAttribute())
	{
		OnMaxWalkSpeedMultChanged.Broadcast(Attribute, OldValue, NewValue);
	}
	else if (Attribute == GetBrakingDecelerationWalkingMultAttribute())
	{
		OnBrakingDecelerationWalkingMultChanged.Broadcast(Attribute, OldValue, NewValue);
	}
	else if (Attribute == GetMaxFlySpeedMultAttribute())
	{
		OnMaxFlySpeedMultChanged.Broadcast(Attribute, OldValue, NewValue);
	}
	else if (Attribute == GetBrakingDecelerationFlyingMultAttribute())
	{
		OnBrakingDecelerationFlyingMultChanged.Broadcast(Attribute, OldValue, NewValue);
	}
}
