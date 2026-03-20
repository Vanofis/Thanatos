#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AttributeSet.h"
#include "Thanatos_GameplayAttributesTypes.h"
#include "HealthAttributeSet.generated.h"

UCLASS()
class THANATOS_API UHealthAttributeSet : public UAttributeSet
{
	GENERATED_BODY()
	
public:
	mutable FGameplayAttributeChangeEventNative OnHealthChanged;
	mutable FGameplayAttributeChangeEventNative OnMaxHealthChanged;
	
	mutable FGameplayAttributeEventNative OnOutOfHealth;
	
	static constexpr float MinHealth = 0.0f;
	
private:
	UPROPERTY(BlueprintReadOnly, meta=(AllowPrivateAccess=true))
	FGameplayAttributeData Health;
	UPROPERTY(BlueprintReadOnly, meta=(AllowPrivateAccess=true))
	FGameplayAttributeData MaxHealth;
	UPROPERTY(BlueprintReadOnly, meta=(AllowPrivateAccess=true))
	FGameplayAttributeData HealthDamage;
	UPROPERTY(BlueprintReadOnly, meta=(AllowPrivateAccess=true))
	FGameplayAttributeData HealthRestoration;
	
	bool bIsOutOfHealth;
	
public:
	UHealthAttributeSet();
	
	virtual bool PreGameplayEffectExecute(FGameplayEffectModCallbackData& Data) override;
	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;
	
	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	virtual void PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue) override;
	
	ATTRIBUTE_ACCESSORS_BASIC(UHealthAttributeSet, Health)
	ATTRIBUTE_ACCESSORS_BASIC(UHealthAttributeSet, MaxHealth)
	ATTRIBUTE_ACCESSORS_BASIC(UHealthAttributeSet, HealthDamage)
	ATTRIBUTE_ACCESSORS_BASIC(UHealthAttributeSet, HealthRestoration)
};
