// Copyright Epic Games, Inc. All Rights Reserved.

#include "YQZYAbilitySystemGlobals.h"

#include "YQZYGameplayEffectContext.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(YQZYAbilitySystemGlobals)

struct FGameplayEffectContext;

UYQZYAbilitySystemGlobals::UYQZYAbilitySystemGlobals(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

FGameplayEffectContext* UYQZYAbilitySystemGlobals::AllocGameplayEffectContext() const
{
	return new FYQZYGameplayEffectContext();
}

