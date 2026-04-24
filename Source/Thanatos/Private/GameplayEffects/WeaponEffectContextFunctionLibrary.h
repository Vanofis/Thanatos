#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectTypes.h"
#include "Components/GameplayAttributes/DamageModifierComponent.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "WeaponEffectContextFunctionLibrary.generated.h"

USTRUCT()
struct FWeaponGameplayEffectContext : public FGameplayEffectContext
{
	GENERATED_BODY()
	
	FDamageContext DamageContext;
	
	float BaseDamage = 0.0f;
	
	FWeaponGameplayEffectContext();
	FWeaponGameplayEffectContext(
		const FDamageContext& DamageContext,
		const float BaseDamage);
	FWeaponGameplayEffectContext(
		const FDamageContext& DamageContext,
		const float BaseDamage,
		AActor* InInstigator, 
		AActor* InEffectCauser);
	
	virtual UScriptStruct* GetScriptStruct() const override
	{
		return FWeaponGameplayEffectContext::StaticStruct();
	}
	
	virtual FGameplayEffectContext* Duplicate() const override
	{
		FWeaponGameplayEffectContext* NewContext = new FWeaponGameplayEffectContext();
		*NewContext = *this;
		
		return NewContext;
	}
};

UCLASS()
class THANATOS_API UWeaponEffectContextFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, BlueprintPure)
	static FGameplayEffectContextHandle MakeWeaponContext(
		UAbilitySystemComponent* AbilitySystemComponent,
		const FDamageContext& DamageContext,
		const float BaseDamage);
};
