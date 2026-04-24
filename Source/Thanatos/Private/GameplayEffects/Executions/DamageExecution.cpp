#include "DamageExecution.h"
#include "AbilitySystemComponent.h"
#include "GameplayEffects/WeaponEffectContextFunctionLibrary.h"

void UDamageExecution::Execute_Implementation(
	const FGameplayEffectCustomExecutionParameters& ExecutionParams,
	FGameplayEffectCustomExecutionOutput& OutExecutionOutput) 
const
{
	const FWeaponGameplayEffectContext* Context = static_cast<const FWeaponGameplayEffectContext*>(
		ExecutionParams.GetOwningSpec().GetEffectContext().Get());
	if (!Context)
	{
		return;
	}
	
	const AActor* Owner = ExecutionParams.GetTargetAbilitySystemComponent()->GetOwner();
	const UDamageModifierComponent* DamageModifierComponent = Owner->FindComponentByClass<UDamageModifierComponent>();
	
	check(DamageModifierComponent);
	
	TMap<FGameplayAttribute, float> AttributesDamage = DamageModifierComponent->GetAttributesDamage(
		Context->DamageContext, Context->BaseDamage);
	for (const auto& AttributesDamageKVP : AttributesDamage)
	{
		OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(
			AttributesDamageKVP.Key,
			EGameplayModOp::AddFinal,
			AttributesDamageKVP.Value
		));
	}
}
