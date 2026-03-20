#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AttributeSet.h"
#include "GameplayEffectTypes.h"
#include "Thanatos_GameplayAttributesTypes.h"
#include "MovementMultipliersAttributeSet.generated.h"

UCLASS()
class THANATOS_API UMovementMultipliersAttributeSet : public UAttributeSet
{
	GENERATED_BODY()
	
public:
	mutable FGameplayAttributeChangeEventNative OnMaxAccelerationMultChanged;
	
	mutable FGameplayAttributeChangeEventNative OnMaxWalkSpeedMultChanged;
	mutable FGameplayAttributeChangeEventNative OnBrakingDecelerationWalkingMultChanged;
	
	mutable FGameplayAttributeChangeEventNative OnMaxFlySpeedMultChanged;
	mutable FGameplayAttributeChangeEventNative OnBrakingDecelerationFlyingMultChanged;
	
private:
	UPROPERTY(BlueprintReadOnly, meta=(AllowPrivateAccess=true))
	FGameplayAttributeData MaxAccelerationMult;
	
	UPROPERTY(BlueprintReadOnly, meta=(AllowPrivateAccess=true))
	FGameplayAttributeData MaxWalkSpeedMult;
	UPROPERTY(BlueprintReadOnly, meta=(AllowPrivateAccess=true))
	FGameplayAttributeData BrakingDecelerationWalkingMult;
	
	UPROPERTY(BlueprintReadOnly, meta=(AllowPrivateAccess=true))
	FGameplayAttributeData MaxFlySpeedMult;
	UPROPERTY(BlueprintReadOnly, meta=(AllowPrivateAccess=true))
	FGameplayAttributeData BrakingDecelerationFlyingMult;
	
public:
	UMovementMultipliersAttributeSet();
	
	virtual bool PreGameplayEffectExecute(FGameplayEffectModCallbackData& Data) override;
	
	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	virtual void PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue) override;
	
	ATTRIBUTE_ACCESSORS_BASIC(UMovementMultipliersAttributeSet, MaxAccelerationMult)
	
	ATTRIBUTE_ACCESSORS_BASIC(UMovementMultipliersAttributeSet, MaxWalkSpeedMult)
	ATTRIBUTE_ACCESSORS_BASIC(UMovementMultipliersAttributeSet, BrakingDecelerationWalkingMult)
	
	ATTRIBUTE_ACCESSORS_BASIC(UMovementMultipliersAttributeSet, MaxFlySpeedMult)
	ATTRIBUTE_ACCESSORS_BASIC(UMovementMultipliersAttributeSet, BrakingDecelerationFlyingMult)
};
