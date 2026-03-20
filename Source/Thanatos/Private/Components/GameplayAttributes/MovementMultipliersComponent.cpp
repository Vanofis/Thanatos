#include "MovementMultipliersComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameplayAttributes/MovementMultipliersAttributeSet.h"

UMovementMultipliersComponent::UMovementMultipliersComponent()
{
	AttributeSetClass = UMovementMultipliersAttributeSet::StaticClass();
}

void UMovementMultipliersComponent::PreAttributeSetInitialization_Implementation()
{
	CharacterMovementComponent = GetOwner()->FindComponentByClass<UCharacterMovementComponent>();
	if (!CharacterMovementComponent)
	{
		return;
	}
	
	InitialMaxAcceleration = CharacterMovementComponent->MaxAcceleration;
	InitialMaxWalkSpeed = CharacterMovementComponent->MaxWalkSpeed;
	InitialBrakingDecelerationWalking = CharacterMovementComponent->BrakingDecelerationWalking;
	InitialMaxFlySpeed = CharacterMovementComponent->MaxFlySpeed;
	InitialBrakingDecelerationFlying = CharacterMovementComponent->BrakingDecelerationFlying;
	
	const UMovementMultipliersAttributeSet* MovementMultipliersAttributeSet = GetMovementMultipliersAttributeSet();
	
	MovementMultipliersAttributeSet->OnMaxAccelerationMultChanged.AddUObject(this, &ThisClass::HandleOnMaxAccelerationChanged);
	MovementMultipliersAttributeSet->OnMaxWalkSpeedMultChanged.AddUObject(this, &ThisClass::HandleOnMaxWalkSpeedChanged);
	MovementMultipliersAttributeSet->OnBrakingDecelerationWalkingMultChanged.AddUObject(this, &ThisClass::HandleOnBrakingDecelerationWalkingChanged);
	MovementMultipliersAttributeSet->OnMaxFlySpeedMultChanged.AddUObject(this, &ThisClass::HandleOnMaxFlySpeedChanged);
	MovementMultipliersAttributeSet->OnBrakingDecelerationFlyingMultChanged.AddUObject(this, &ThisClass::HandleOnBrakingDecelerationFlyingChanged);
}

UMovementMultipliersAttributeSet* UMovementMultipliersComponent::GetMovementMultipliersAttributeSet() const
{
	UMovementMultipliersAttributeSet* MovementMultipliersAttributeSet = Cast<UMovementMultipliersAttributeSet>(AttributeSet);
	check(MovementMultipliersAttributeSet);
	
	return MovementMultipliersAttributeSet;
}

void UMovementMultipliersComponent::HandleOnMaxAccelerationChanged(
	const FGameplayAttribute& Attribute, 
	const float OldValue, 
	const float NewValue) 
const
{
	CharacterMovementComponent->MaxAcceleration = InitialMaxAcceleration * NewValue;
	
	OnMaxAccelerationChanged.Broadcast(Attribute, OldValue, NewValue);
}

void UMovementMultipliersComponent::HandleOnMaxWalkSpeedChanged(
	const FGameplayAttribute& Attribute, 
	const float OldValue, 
	const float NewValue) 
const
{
	CharacterMovementComponent->MaxWalkSpeed = InitialMaxWalkSpeed * NewValue;
	
	OnMaxWalkSpeedChanged.Broadcast(Attribute, OldValue, NewValue);
}

void UMovementMultipliersComponent::HandleOnBrakingDecelerationWalkingChanged(
	const FGameplayAttribute& Attribute, 
	const float OldValue, 
	const float NewValue) 
const
{
	CharacterMovementComponent->BrakingDecelerationWalking = InitialBrakingDecelerationWalking * NewValue;
	
	OnBrakingDecelerationWalkingChanged.Broadcast(Attribute, OldValue, NewValue);
}

void UMovementMultipliersComponent::HandleOnMaxFlySpeedChanged(
	const FGameplayAttribute& Attribute, 
	const float OldValue, 
	const float NewValue) 
const
{
	CharacterMovementComponent->MaxFlySpeed = InitialMaxFlySpeed * NewValue;
	
	OnMaxFlySpeedChanged.Broadcast(Attribute, OldValue, NewValue);
}

void UMovementMultipliersComponent::HandleOnBrakingDecelerationFlyingChanged(
	const FGameplayAttribute& Attribute, 
	const float OldValue, 
	const float NewValue) 
const
{
	CharacterMovementComponent->BrakingDecelerationFlying = InitialBrakingDecelerationFlying * NewValue;
	
	OnBrakingDecelerationFlyingChanged.Broadcast(Attribute, OldValue, NewValue);
}
