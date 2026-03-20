#pragma once

#include "CoreMinimal.h"
#include "AttributeComponent.h"
#include "EnergyComponent.generated.h"

class UEnergyAttributeSet;

UCLASS(ClassGroup=(GameplayAttributes), meta=(BlueprintSpawnableComponent))
class THANATOS_API UEnergyComponent : public UAttributeComponent
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadOnly, BlueprintAssignable, Category="Energy Component")
	mutable FGameplayAttributeChangedEvent OnGatheredDataChanged;
	
	UPROPERTY(BlueprintReadOnly, BlueprintAssignable, Category="Energy Component")
	mutable FGameplayAttributeChangedEvent OnHeatChanged;
	UPROPERTY(BlueprintReadOnly, BlueprintAssignable, Category="Energy Component")
	mutable FGameplayAttributeChangedEvent OnMaxHeatChanged;
	
	UPROPERTY(BlueprintReadOnly, BlueprintAssignable, Category="Energy Component")
	mutable FGameplayAttributeChangedEvent OnEnergyChanged;
	UPROPERTY(BlueprintReadOnly, BlueprintAssignable, Category="Energy Component")
	mutable FGameplayAttributeChangedEvent OnMaxEnergyChanged;
	
	UPROPERTY(BlueprintReadOnly, BlueprintAssignable, Category="Energy Component")
	mutable FGameplayAttributeEvent OnOverheat;
	
	UEnergyComponent();
	
	UFUNCTION(BlueprintCallable, BlueprintPure, Category="Energy Component")
	static float GetMinGatheredData();
	UFUNCTION(BlueprintCallable, BlueprintPure, Category="Energy Component")
	static float GetMinEnergy();
	UFUNCTION(BlueprintCallable, BlueprintPure, Category="Energy Component")
	static float GetMinHeat();

protected:
	virtual void PreAttributeSetInitialization_Implementation() override;
	
	virtual TArray<FGameplayAttribute> GetAttributeInitializationOrder() override;
	
	UEnergyAttributeSet* GetEnergyAttributeSet() const;
	
private:
	void HandleOnGatheredDataChanged(
		const FGameplayAttribute& Attribute, 
		const float OldValue, 
		const float NewValue) 
	const;
	void HandleOnHeatChanged(
		const FGameplayAttribute& Attribute, 
		const float OldValue, 
		const float NewValue) 
	const;
	void HandleOnMaxHeatChanged(		
		const FGameplayAttribute& Attribute, 
		const float OldValue, 
		const float NewValue) 
	const;
	void HandleOnEnergyChanged(		
		const FGameplayAttribute& Attribute, 
		const float OldValue, 
		const float NewValue) 
	const;
	void HandleOnMaxEnergyChanged(		
		const FGameplayAttribute& Attribute, 
		const float OldValue, 
		const float NewValue) 
	const;
	void HandleOnOverheat(const FGameplayAttribute& Attribute, float Value) const;
};
