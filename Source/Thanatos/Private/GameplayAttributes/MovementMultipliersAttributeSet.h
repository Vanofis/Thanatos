#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AttributeSet.h"
#include "GameplayEffectTypes.h"
#include "MovementMultipliersAttributeSet.generated.h"

UCLASS()
class THANATOS_API UMovementMultipliersAttributeSet : public UAttributeSet
{
	GENERATED_BODY()
	
public:
	mutable FOnGameplayAttributeValueChange OnMaxAccelerationMultChanged;
	
	mutable FOnGameplayAttributeValueChange OnMaxWalkSpeedMultChanged;
	mutable FOnGameplayAttributeValueChange OnBrakingDecelerationWalkingMultChanged;
	
	mutable FOnGameplayAttributeValueChange OnMaxFlySpeedMultChanged;
	mutable FOnGameplayAttributeValueChange OnBrakingDecelerationFlyingMultChanged;
	
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
	
	float MaxAccelerationMultPreChanged;
	
	float MaxWalkSpeedMultPreChanged;
	float BrakingDecelerationWalkingMultPreChanged;
	
	float MaxFlySpeedMultPreChanged;
	float BrakingDecelerationFlyingMultPreChanged;
	
public:
	UMovementMultipliersAttributeSet();
	
	virtual bool PreGameplayEffectExecute(FGameplayEffectModCallbackData& Data) override;
	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;
	
	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	
	ATTRIBUTE_ACCESSORS_BASIC(UMovementMultipliersAttributeSet, MaxAccelerationMult)
	
	ATTRIBUTE_ACCESSORS_BASIC(UMovementMultipliersAttributeSet, MaxWalkSpeedMult)
	ATTRIBUTE_ACCESSORS_BASIC(UMovementMultipliersAttributeSet, BrakingDecelerationWalkingMult)
	
	ATTRIBUTE_ACCESSORS_BASIC(UMovementMultipliersAttributeSet, MaxFlySpeedMult)
	ATTRIBUTE_ACCESSORS_BASIC(UMovementMultipliersAttributeSet, BrakingDecelerationFlyingMult)
};
