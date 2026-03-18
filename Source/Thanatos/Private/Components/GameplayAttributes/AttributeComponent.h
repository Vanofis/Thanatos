#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "GameplayEffect.h"
#include "Components/ActorComponent.h"
#include "AttributeComponent.generated.h"

class UAbilitySystemComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FGameplayAttributeChangedEvent, const FGameplayAttribute&, Attribute, float, OldValue, float, NewValue);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGameplayAttributeEvent, const FGameplayAttribute&, Attribute, float, Value);

UCLASS(Blueprintable, ClassGroup=(GameplayAttributes), meta=(BlueprintSpawnableComponent))
class THANATOS_API UAttributeComponent : public UActorComponent
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadOnly, Category="Attribute Component")
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;
	UPROPERTY(BlueprintReadOnly, Category="Attribute Component")
	TObjectPtr<UAttributeSet> AttributeSet;
	
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="Attribute Component", meta=(AllowPrivateAccess=true))
	TSubclassOf<UAttributeSet> AttributeSetClass;
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="Attribute Component", meta=(AllowPrivateAccess=true))
	TSubclassOf<UGameplayEffect> InitializationEffectClass;
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="Attribute Component", 
		meta=(AllowPrivateAccess=true, EditCondition = "InitializationEffectClass != nullptr", EditConditionHides))
	FDataTableRowHandle InitializationRow;

public:
	UAttributeComponent();
	
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	
	virtual const TArray<FGameplayAttribute>& GetAttributeInitializationOrder();
	
protected:
	UFUNCTION(BlueprintNativeEvent, Category="Attribute Component")
	void PreAttributeSetInitialization();
	
private:
	void InitializeAttributeSet();
};
