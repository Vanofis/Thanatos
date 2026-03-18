#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectExecutionCalculation.h"
#include "AttributeInitializationExecution.generated.h"

USTRUCT(BlueprintType)
struct THANATOS_API FAttributeInitializationRow : public FTableRowBase
{
	GENERATED_BODY()
	
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	TMap<FGameplayAttribute, float> AttributeInitValues;
};

USTRUCT()
struct THANATOS_API FAttributeInitializationEffectContext : public FGameplayEffectContext
{
	GENERATED_BODY()
	
	FAttributeInitializationEffectContext();
	FAttributeInitializationEffectContext(
		const FDataTableRowHandle& RowHandle, 
		const TArray<FGameplayAttribute>& AttributeInitOrder);
	FAttributeInitializationEffectContext(
		const FDataTableRowHandle& RowHandle, 
		const TArray<FGameplayAttribute>& AttributeInitOrder,
		AActor* InInstigator, 
		AActor* InEffectCauser);
	
	const FDataTableRowHandle& GetRowHandle() const;
	
	const TArray<FGameplayAttribute>& GetAttributeInitOrder() const;
	
protected:
	TArray<FGameplayAttribute> AttributeInitOrder;
	
	FDataTableRowHandle RowHandle;
};

UCLASS(Blueprintable)
class THANATOS_API UAttributeInitializationExecution : public UGameplayEffectExecutionCalculation
{
	GENERATED_BODY()
	
public:
	virtual void Execute_Implementation(
		const FGameplayEffectCustomExecutionParameters& ExecutionParams, 
		FGameplayEffectCustomExecutionOutput& OutExecutionOutput) 
	const override;
};
