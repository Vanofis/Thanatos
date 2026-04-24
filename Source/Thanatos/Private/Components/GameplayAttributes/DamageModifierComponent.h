#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "GameplayTagContainer.h"
#include "Components/ActorComponent.h"
#include "DamageModifierComponent.generated.h"

USTRUCT(BlueprintType)
struct THANATOS_API FDamageContext
{
	GENERATED_BODY()
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true, Categories="WeaponTypes"))
	FGameplayTagContainer WeaponTypes;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true, Categories="DamageTypes"))
	FGameplayTagContainer DamageType;
};

USTRUCT(BlueprintType)
struct THANATOS_API FDamageRule
{
	GENERATED_BODY()
	
	UPROPERTY(BlueprintReadOnly, EditAnywhere, meta=(AllowPrivateAccess=true))
	FDamageContext Context;
	UPROPERTY(BlueprintReadOnly, EditAnywhere, meta=(AllowPrivateAccess=true))
	TMap<FGameplayAttribute, float> AttributeMultipliers;
	
	bool Matches(const FDamageContext& Other) const;
};

UCLASS(Blueprintable, ClassGroup=(GameplayAttributes), meta=(BlueprintSpawnableComponent))
class THANATOS_API UDamageModifierComponent : public UActorComponent
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess=true))
	TArray<FDamageRule> DamageRules;
	UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess=true, MinValue = 0.0f))
	float DefaultModifier = 1.0f;
	
public:
	UFUNCTION(BlueprintCallable, BlueprintPure)
	TMap<FGameplayAttribute, float> GetAttributesDamage(
		const FDamageContext& Context, 
		const float BaseDamage) 
	const;
};
