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
	void OnMaxAccelerationChanged(const FOnAttributeChangeData& Data) const;
	
	void OnMaxWalkSpeedChanged(const FOnAttributeChangeData& Data) const;
	void OnBrakingDecelerationWalkingChanged(const FOnAttributeChangeData& Data) const;
	
	void OnMaxFlySpeedChanged(const FOnAttributeChangeData& Data) const;
	void OnBrakingDecelerationFlyingChanged(const FOnAttributeChangeData& Data) const;
};
