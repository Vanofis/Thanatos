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
	
	virtual const TArray<FGameplayAttribute>& GetAttributeInitializationOrder() override;
	
protected:
	virtual void PreAttributeSetInitialization_Implementation() override;
	
	UHealthAttributeSet* GetHealthAttributeSet() const;
	
private:
	void HandleOnHealthChanged(const FOnAttributeChangeData& Data) const;
	void HandleOnMaxHealthChanged(const FOnAttributeChangeData& Data) const;
	void HandleOnOutOfHealth(const FGameplayAttribute& Attribute, float Value) const;
};
