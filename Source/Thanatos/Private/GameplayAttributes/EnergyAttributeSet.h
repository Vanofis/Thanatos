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
	mutable FGameplayAttributeChangeEventNative OnGatheredDataChanged;
	
	mutable FGameplayAttributeChangeEventNative OnHeatChanged;
	mutable FGameplayAttributeChangeEventNative OnMaxHeatChanged;
	
	mutable FGameplayAttributeChangeEventNative OnEnergyChanged;
	mutable FGameplayAttributeChangeEventNative OnMaxEnergyChanged;
	
	mutable FGameplayAttributeEventNative OnEnergyNoLongerMax;
	mutable FGameplayAttributeEventNative OnEnergyMax;
	
	mutable FGameplayAttributeEventNative OnHeatMin;
	mutable FGameplayAttributeEventNative OnHeatNoLongerMin;
	
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
	FGameplayAttributeData HeatDecayRate;
	
	UPROPERTY(BlueprintReadOnly, meta=(AllowPrivateAccess=true))
	FGameplayAttributeData Energy;
	UPROPERTY(BlueprintReadOnly, meta=(AllowPrivateAccess=true))
	FGameplayAttributeData MaxEnergy;
	UPROPERTY(BlueprintReadOnly, meta=(AllowPrivateAccess=true))
	FGameplayAttributeData EnergyRegenerationRate;
	
	bool bIsHeatMin;
	bool bIsHeatMax;
	
	bool bEnergyMax;
	
public:
	UEnergyAttributeSet();
	
	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	virtual void PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue) override;
	
	ATTRIBUTE_ACCESSORS_BASIC(UEnergyAttributeSet, GatheredData)
	
	ATTRIBUTE_ACCESSORS_BASIC(UEnergyAttributeSet, Heat)
	ATTRIBUTE_ACCESSORS_BASIC(UEnergyAttributeSet, MaxHeat)
	ATTRIBUTE_ACCESSORS_BASIC(UEnergyAttributeSet, HeatDecayRate)
	
	ATTRIBUTE_ACCESSORS_BASIC(UEnergyAttributeSet, Energy)
	ATTRIBUTE_ACCESSORS_BASIC(UEnergyAttributeSet, MaxEnergy)
	ATTRIBUTE_ACCESSORS_BASIC(UEnergyAttributeSet, EnergyRegenerationRate)
};
