#include "MovementMultipliersAttributeSet.h"

UMovementMultipliersAttributeSet::UMovementMultipliersAttributeSet()
	: MaxAccelerationMult(1.0f)
	, MaxWalkSpeedMult(1.0f)
	, BrakingDecelerationWalkingMult(1.0f)
	, MaxFlySpeedMult(1.0f)
	, BrakingDecelerationFlyingMult(1.0f)
{}

bool UMovementMultipliersAttributeSet::PreGameplayEffectExecute(FGameplayEffectModCallbackData& Data)
{
	MaxAccelerationMultPreChanged = GetMaxAccelerationMult();
	
	MaxWalkSpeedMultPreChanged = GetMaxWalkSpeedMult();
	BrakingDecelerationWalkingMultPreChanged = GetBrakingDecelerationWalkingMult();
	
	MaxFlySpeedMultPreChanged = GetMaxFlySpeedMult();
	BrakingDecelerationFlyingMultPreChanged = GetBrakingDecelerationFlyingMult();
	
	return Super::PreGameplayEffectExecute(Data);
}

void UMovementMultipliersAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	FOnAttributeChangeData ChangeData;
	ChangeData.GEModData = &Data;
	
	if (!FMath::IsNearlyEqual(MaxAccelerationMultPreChanged, GetMaxAccelerationMult()))
	{
		ChangeData.Attribute = GetMaxAccelerationMultAttribute();
		ChangeData.OldValue = MaxAccelerationMultPreChanged;
		ChangeData.NewValue = GetMaxAccelerationMult();
		
		OnMaxAccelerationMultChanged.Broadcast(ChangeData);
	}
	
	if (!FMath::IsNearlyEqual(MaxWalkSpeedMultPreChanged, GetMaxWalkSpeedMult()))
	{
		ChangeData.Attribute = GetMaxWalkSpeedMultAttribute();
		ChangeData.OldValue = MaxWalkSpeedMultPreChanged;
		ChangeData.NewValue = GetMaxWalkSpeedMult();
		
		OnMaxWalkSpeedMultChanged.Broadcast(ChangeData);
	}
	
	if (!FMath::IsNearlyEqual(BrakingDecelerationWalkingMultPreChanged, GetBrakingDecelerationWalkingMult()))
	{
		ChangeData.Attribute = GetBrakingDecelerationWalkingMultAttribute();
		ChangeData.OldValue = BrakingDecelerationWalkingMultPreChanged;
		ChangeData.NewValue = GetBrakingDecelerationWalkingMult();
		
		OnBrakingDecelerationWalkingMultChanged.Broadcast(ChangeData);
	}
	
	if (!FMath::IsNearlyEqual(MaxFlySpeedMultPreChanged, GetMaxFlySpeedMult()))
	{
		ChangeData.Attribute = GetMaxFlySpeedMultAttribute();
		ChangeData.OldValue = MaxFlySpeedMultPreChanged;
		ChangeData.NewValue = GetMaxFlySpeedMult();
		
		OnMaxFlySpeedMultChanged.Broadcast(ChangeData);
	}
	
	if (!FMath::IsNearlyEqual(BrakingDecelerationFlyingMultPreChanged, GetBrakingDecelerationFlyingMult()))
	{
		ChangeData.Attribute = GetBrakingDecelerationFlyingMultAttribute();
		ChangeData.OldValue = BrakingDecelerationFlyingMultPreChanged;
		ChangeData.NewValue = GetBrakingDecelerationFlyingMult();
		
		OnBrakingDecelerationFlyingMultChanged.Broadcast(ChangeData);
	}
}

void UMovementMultipliersAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	NewValue = FMath::Max(0.0f, NewValue);
}
