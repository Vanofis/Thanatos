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
	
private:
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="Health Component", meta=(AllowPrivateAccess=true))
	TMap<FGameplayTag, float> DamageModifiers;
	
public:
	UHealthComponent();
	
	UFUNCTION(BlueprintCallable, BlueprintPure, Category="Health Component")
	static float GetMinHealth();

	UFUNCTION(BlueprintCallable, BlueprintPure, Category="Health Component")
	float GetDamageMultiplier(const FGameplayTag MultiplierTag) const;
	
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
