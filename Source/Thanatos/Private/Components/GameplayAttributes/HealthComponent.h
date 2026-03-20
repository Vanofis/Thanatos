# pragma once

#include "CoreMinimal.h"
#include "AttributeComponent.h"
#include "HealthComponent.generated.h"

class UHealthAttributeSet;

UCLASS(ClassGroup=(GameplayAttributes), meta=(BlueprintSpawnableComponent))
class THANATOS_API UHealthComponent : public UAttributeComponent
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly, BlueprintAssignable, Category="Health Component")
	mutable FGameplayAttributeChangedEvent OnHealthChanged;
	UPROPERTY(BlueprintReadOnly, BlueprintAssignable, Category="Health Component")
	mutable FGameplayAttributeChangedEvent OnMaxHealthChanged;
	UPROPERTY(BlueprintReadOnly, BlueprintAssignable, Category="Health Component")
	mutable FGameplayAttributeEvent OnOutOfHealth;
	
	UHealthComponent();
	
	UFUNCTION(BlueprintCallable, BlueprintPure, Category="Health Component")
	static float GetMinHealth();

protected:
	virtual void PreAttributeSetInitialization_Implementation() override;
	
	virtual TArray<FGameplayAttribute> GetAttributeInitializationOrder() override;
	
	UHealthAttributeSet* GetHealthAttributeSet() const;

private:
	void HandleOnHealthChanged(
		const FGameplayAttribute& Attribute, 
		const float OldValue, 
		const float NewValue) 
	const;
	void HandleOnMaxHealthChanged(
		const FGameplayAttribute& Attribute, 
		const float OldValue, 
		const float NewValue) 
	const;
	void HandleOnOutOfHealth(const FGameplayAttribute& Attribute, const float Value) const;
};
