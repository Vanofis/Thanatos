#pragma once

#include "CoreMinimal.h"
#include "AttributeComponent.h"
#include "MovementMultipliersComponent.generated.h"

class UCharacterMovementComponent;
class UMovementMultipliersAttributeSet;

UCLASS(ClassGroup=(GameplayAttributes), meta=(BlueprintSpawnableComponent))
class THANATOS_API UMovementMultipliersComponent : public UAttributeComponent
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly, BlueprintAssignable, Category="Movement Multipliers Component")
	mutable FGameplayAttributeChangedEvent OnMaxAccelerationChanged;
	
	UPROPERTY(BlueprintReadOnly, BlueprintAssignable, Category="Movement Multipliers Component")
	mutable FGameplayAttributeChangedEvent OnMaxWalkSpeedChanged;
	UPROPERTY(BlueprintReadOnly, BlueprintAssignable, Category="Movement Multipliers Component")
	mutable FGameplayAttributeChangedEvent OnBrakingDecelerationWalkingChanged;
	
	UPROPERTY(BlueprintReadOnly, BlueprintAssignable, Category="Movement Multipliers Component")
	mutable FGameplayAttributeChangedEvent OnMaxFlySpeedChanged;
	UPROPERTY(BlueprintReadOnly, BlueprintAssignable, Category="Movement Multipliers Component")
	mutable FGameplayAttributeChangedEvent OnBrakingDecelerationFlyingChanged;
	
protected:
	UPROPERTY()
	TObjectPtr<UCharacterMovementComponent> CharacterMovementComponent;
	
private:
	float InitialMaxAcceleration;
	
	float InitialMaxWalkSpeed;
	float InitialBrakingDecelerationWalking;
	
	float InitialMaxFlySpeed;
	float InitialBrakingDecelerationFlying;
	
public:
	UMovementMultipliersComponent();
	
	virtual void PreAttributeSetInitialization_Implementation() override;

protected:
	UMovementMultipliersAttributeSet* GetMovementMultipliersAttributeSet() const;
	
private:
	void HandleOnMaxAccelerationChanged(
		const FGameplayAttribute& Attribute, 
		const float OldValue, 
		const float NewValue) 
	const;
	
	void HandleOnMaxWalkSpeedChanged(
		const FGameplayAttribute& Attribute, 
		const float OldValue, 
		const float NewValue) 
	const;
	void HandleOnBrakingDecelerationWalkingChanged(
		const FGameplayAttribute& Attribute, 
		const float OldValue, 
		const float NewValue) 
	const;
	
	void HandleOnMaxFlySpeedChanged(
		const FGameplayAttribute& Attribute, 
		const float OldValue, 
		const float NewValue) 
	const;
	void HandleOnBrakingDecelerationFlyingChanged(
		const FGameplayAttribute& Attribute, 
		const float OldValue, 
		const float NewValue) 
	const;
};
