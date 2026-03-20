#include "AttributeComponent.h"
#include "AbilitySystemComponent.h"
#include "GameplayEffects/AttributeInitializationExecution.h"

UAttributeComponent::UAttributeComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UAttributeComponent::BeginPlay()
{
	AbilitySystemComponent = GetOwner()->FindComponentByClass<UAbilitySystemComponent>();
	check(AbilitySystemComponent);
	
	InitializeAttributeSet();
	
	Super::BeginPlay();
}

void UAttributeComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	
	AbilitySystemComponent->RemoveSpawnedAttribute(AttributeSet.Get());
}

TArray<FGameplayAttribute> UAttributeComponent::GetAttributeInitializationOrder()
{
	TArray<FGameplayAttribute> Order;
	
	UAttributeSet::GetAttributesFromSetClass(AttributeSetClass, Order);
	
	return MoveTemp(Order);
}

void UAttributeComponent::PreAttributeSetInitialization_Implementation()
{}

void UAttributeComponent::InitializeAttributeSet()
{
	AttributeSet = NewObject<UAttributeSet>(GetOwner(), AttributeSetClass);
	check(AttributeSet);
	
	AbilitySystemComponent->AddAttributeSetSubobject(AttributeSet.Get());
	PreAttributeSetInitialization();

	if (InitializationEffectClass)
	{
		FAttributeInitializationEffectContext* Context = new FAttributeInitializationEffectContext(
			InitializationRow, 
			GetAttributeInitializationOrder(),
			GetOwner(), 
			GetOwner());
		const FGameplayEffectSpecHandle SpecHandle = AbilitySystemComponent->MakeOutgoingSpec(
			InitializationEffectClass, 
			1.0f, 
			FGameplayEffectContextHandle(Context));
		
		AbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data);
	}
}
