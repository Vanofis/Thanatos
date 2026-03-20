#pragma once

#include "CoreMinimal.h"
#include "AttributeComponent.h"
#include "CombatCharacteristicsComponent.generated.h"

UCLASS(ClassGroup=(GameplayAttributes), meta=(BlueprintSpawnableComponent))
class THANATOS_API UCombatCharacteristicsComponent : public UAttributeComponent
{
	GENERATED_BODY()

public:
	UCombatCharacteristicsComponent();
	
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Combat Characteristics Component")
	static float GetMinMeleeDamage();
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Combat Characteristics Component")
	static float GetMinRangedDamage();
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Combat Characteristics Component")
	static float GetMinArmor();
};
