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
	
	MovementMultipliersAttributeSet->OnMaxAccelerationMultChanged.AddUObject(this, &ThisClass::OnMaxAccelerationChanged);
	MovementMultipliersAttributeSet->OnMaxWalkSpeedMultChanged.AddUObject(this, &ThisClass::OnMaxWalkSpeedChanged);
	MovementMultipliersAttributeSet->OnBrakingDecelerationWalkingMultChanged.AddUObject(this, &ThisClass::OnBrakingDecelerationWalkingChanged);
	MovementMultipliersAttributeSet->OnMaxFlySpeedMultChanged.AddUObject(this, &ThisClass::OnMaxFlySpeedChanged);
	MovementMultipliersAttributeSet->OnBrakingDecelerationFlyingMultChanged.AddUObject(this, &ThisClass::OnBrakingDecelerationFlyingChanged);
}

UMovementMultipliersAttributeSet* UMovementMultipliersComponent::GetMovementMultipliersAttributeSet() const
{
	UMovementMultipliersAttributeSet* MovementMultipliersAttributeSet = Cast<UMovementMultipliersAttributeSet>(AttributeSet);
	check(MovementMultipliersAttributeSet);
	
	return MovementMultipliersAttributeSet;
}

void UMovementMultipliersComponent::OnMaxAccelerationChanged(const FOnAttributeChangeData& Data) const
{
	CharacterMovementComponent->MaxAcceleration = InitialMaxAcceleration * Data.NewValue;
}

void UMovementMultipliersComponent::OnMaxWalkSpeedChanged(const FOnAttributeChangeData& Data) const
{
	CharacterMovementComponent->MaxWalkSpeed = InitialMaxWalkSpeed * Data.NewValue;
}

void UMovementMultipliersComponent::OnBrakingDecelerationWalkingChanged(const FOnAttributeChangeData& Data) const
{
	CharacterMovementComponent->BrakingDecelerationWalking = InitialBrakingDecelerationWalking * Data.NewValue;
}

void UMovementMultipliersComponent::OnMaxFlySpeedChanged(const FOnAttributeChangeData& Data) const
{
	CharacterMovementComponent->MaxFlySpeed = InitialMaxFlySpeed * Data.NewValue;
}

void UMovementMultipliersComponent::OnBrakingDecelerationFlyingChanged(const FOnAttributeChangeData& Data) const
{
	CharacterMovementComponent->BrakingDecelerationFlying = InitialBrakingDecelerationFlying * Data.NewValue;
}
