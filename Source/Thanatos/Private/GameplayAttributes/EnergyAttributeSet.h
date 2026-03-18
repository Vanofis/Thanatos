#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AttributeSet.h"
#include "Thanatos_GameplayAttributesTypes.h"
#include "EnergyAttributeSet.generated.h"

UCLASS()
class THANATOS_API UEnergyAttributeSet : public UAttributeSet
{
	GENERATED_BODY()
	
public:
	mutable FOnGameplayAttributeValueChange OnGatheredDataChanged;
	
	mutable FOnGameplayAttributeValueChange OnHeatChanged;
	mutable FOnGameplayAttributeValueChange OnMaxHeatChanged;
	
	mutable FOnGameplayAttributeValueChange OnEnergyChanged;
	mutable FOnGameplayAttributeValueChange OnMaxEnergyChanged;
	
	mutable FGameplayAttributeEventNative OnOverheat;
	
	static constexpr float MinGatheredData = 200.0f;
	static constexpr float MinEnergy = 0.0f;
	static constexpr float MinHeat = 75.0f;
	
private:
	UPROPERTY(BlueprintReadOnly, meta=(AllowPrivateAccess=true))
	FGameplayAttributeData GatheredData;
	
	UPROPERTY(BlueprintReadOnly, meta=(AllowPrivateAccess=true))
	FGameplayAttributeData Heat;
	UPROPERTY(BlueprintReadOnly, meta=(AllowPrivateAccess=true))
	FGameplayAttributeData MaxHeat;
	UPROPERTY(BlueprintReadOnly, meta=(AllowPrivateAccess=true))
	FGameplayAttributeData HeatDecrease;
	UPROPERTY(BlueprintReadOnly, meta=(AllowPrivateAccess=true))
	FGameplayAttributeData HeatIncrease;
	
	UPROPERTY(BlueprintReadOnly, meta=(AllowPrivateAccess=true))
	FGameplayAttributeData Energy;
	UPROPERTY(BlueprintReadOnly, meta=(AllowPrivateAccess=true))
	FGameplayAttributeData MaxEnergy;
	UPROPERTY(BlueprintReadOnly, meta=(AllowPrivateAccess=true))
	FGameplayAttributeData EnergyDamage;
	UPROPERTY(BlueprintReadOnly, meta=(AllowPrivateAccess=true))
	FGameplayAttributeData EnergyRestoration;
	
	float GatheredDataPreChanged;
	
	float HeatPreChanged;
	float MaxHeatPreChanged;
	
	float EnergyPreChanged;
	float MaxEnergyPreChanged;
	
	bool bIsHeatMax;
	
public:
	UEnergyAttributeSet();
	
	virtual bool PreGameplayEffectExecute(FGameplayEffectModCallbackData& Data) override;
	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;
	
	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	
	ATTRIBUTE_ACCESSORS_BASIC(UEnergyAttributeSet, GatheredData)
	
	ATTRIBUTE_ACCESSORS_BASIC(UEnergyAttributeSet, Heat)
	ATTRIBUTE_ACCESSORS_BASIC(UEnergyAttributeSet, MaxHeat)
	ATTRIBUTE_ACCESSORS_BASIC(UEnergyAttributeSet, HeatDecrease)
	ATTRIBUTE_ACCESSORS_BASIC(UEnergyAttributeSet, HeatIncrease)
	
	ATTRIBUTE_ACCESSORS_BASIC(UEnergyAttributeSet, Energy)
	ATTRIBUTE_ACCESSORS_BASIC(UEnergyAttributeSet, MaxEnergy)
	ATTRIBUTE_ACCESSORS_BASIC(UEnergyAttributeSet, EnergyDamage)
	ATTRIBUTE_ACCESSORS_BASIC(UEnergyAttributeSet, EnergyRestoration)
};
