#pragma once

#include "CoreMinimal.h"

struct FGameplayAttribute;

DECLARE_MULTICAST_DELEGATE_TwoParams(FGameplayAttributeEventNative, const FGameplayAttribute&, float);
DECLARE_MULTICAST_DELEGATE_ThreeParams(FGameplayAttributeChangeEventNative, const FGameplayAttribute&, float, float);
