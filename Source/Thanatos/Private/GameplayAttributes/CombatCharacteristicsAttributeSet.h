#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AttributeSet.h"
#include "CombatCharacteristicsAttributeSet.generated.h"

UCLASS()
class THANATOS_API UCombatCharacteristicsAttributeSet : public UAttributeSet
{
	GENERATED_BODY()
	
public:
	static constexpr float MinMeleeDamage = 1.0f;
	static constexpr float MinRangedDamage = 1.0f;
	static constexpr float MinArmor = 0.0f;
	
private:
	UPROPERTY(BlueprintReadOnly, meta=(AllowPrivateAccess=true))
	FGameplayAttributeData MeleeDamage;
	UPROPERTY(BlueprintReadOnly, meta=(AllowPrivateAccess=true))
	FGameplayAttributeData RangedDamage;
	UPROPERTY(BlueprintReadOnly, meta=(AllowPrivateAccess=true))
	FGameplayAttributeData Armor;
	
public:
	UCombatCharacteristicsAttributeSet();
	
	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	
	ATTRIBUTE_ACCESSORS_BASIC(UCombatCharacteristicsAttributeSet, MeleeDamage);
	ATTRIBUTE_ACCESSORS_BASIC(UCombatCharacteristicsAttributeSet, RangedDamage);
	ATTRIBUTE_ACCESSORS_BASIC(UCombatCharacteristicsAttributeSet, Armor);
};
