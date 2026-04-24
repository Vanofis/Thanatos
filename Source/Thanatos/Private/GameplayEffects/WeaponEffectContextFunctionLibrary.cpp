#include "WeaponEffectContextFunctionLibrary.h"
#include "AbilitySystemComponent.h"

FWeaponGameplayEffectContext::FWeaponGameplayEffectContext()
{}

FWeaponGameplayEffectContext::FWeaponGameplayEffectContext(
	const FDamageContext& DamageContext, 
	const float BaseDamage)
	: DamageContext(DamageContext)
	, BaseDamage(BaseDamage)
{}

FWeaponGameplayEffectContext::FWeaponGameplayEffectContext(
	const FDamageContext& DamageContext, 
	const float BaseDamage,
	AActor* InInstigator, 
	AActor* InEffectCauser)
	: Super(InInstigator, InEffectCauser)
	, DamageContext(DamageContext)
	, BaseDamage(BaseDamage)
{}

FGameplayEffectContextHandle UWeaponEffectContextFunctionLibrary::MakeWeaponContext(
	UAbilitySystemComponent* AbilitySystemComponent,
	const FDamageContext& DamageContext,
	const float BaseDamage)
{
	const FGameplayEffectContextHandle ContextHandle = AbilitySystemComponent->MakeEffectContext();
	FWeaponGameplayEffectContext* WeaponContext = new FWeaponGameplayEffectContext(
		DamageContext,
		BaseDamage,
		ContextHandle.Get()->GetInstigator(), 
		ContextHandle.Get()->GetEffectCauser());
	
	return FGameplayEffectContextHandle(WeaponContext);
}
