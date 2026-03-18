#include "AttributeInitializationExecution.h"

FAttributeInitializationEffectContext::FAttributeInitializationEffectContext()
{}

FAttributeInitializationEffectContext::FAttributeInitializationEffectContext(
	const FDataTableRowHandle& RowHandle,
	const TArray<FGameplayAttribute>& AttributeInitOrder)
	: AttributeInitOrder(AttributeInitOrder)
	, RowHandle(RowHandle)
{}

FAttributeInitializationEffectContext::FAttributeInitializationEffectContext(
	const FDataTableRowHandle& RowHandle, 
	const TArray<FGameplayAttribute>& AttributeInitOrder,
	AActor* InInstigator, 
	AActor* InEffectCauser)
	: Super(InInstigator, InEffectCauser)
	, AttributeInitOrder(AttributeInitOrder)
	, RowHandle(RowHandle)
{}

const FDataTableRowHandle& FAttributeInitializationEffectContext::GetRowHandle() const
{
	return RowHandle;
}

const TArray<FGameplayAttribute>& FAttributeInitializationEffectContext::GetAttributeInitOrder() const
{
	return AttributeInitOrder;
}

void UAttributeInitializationExecution::Execute_Implementation(
	const FGameplayEffectCustomExecutionParameters& ExecutionParams,
	FGameplayEffectCustomExecutionOutput& OutExecutionOutput) 
const
{
	const FGameplayEffectContextHandle& ContextHandle = ExecutionParams.GetOwningSpec().GetEffectContext();
	const FGameplayEffectContext* Context = ContextHandle.Get();
	if (!Context)
	{
		return;
	}
	
	const FAttributeInitializationEffectContext* InitContext = static_cast<const FAttributeInitializationEffectContext*>(Context);
	if (!InitContext)
	{
		return;
	}
		
	const FAttributeInitializationRow* Row = InitContext->GetRowHandle().GetRow<FAttributeInitializationRow>("AttributeInitialization");
	if (!Row)
	{
		return;
	}
	
	for (const auto& Attribute : InitContext->GetAttributeInitOrder())
	{
		const float* InitValuePtr = Row->AttributeInitValues.Find(Attribute);
		if (!InitValuePtr)
		{
			continue;
		}
		
		OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(
			Attribute,
			EGameplayModOp::Override,
			*InitValuePtr
		));
	}
}
