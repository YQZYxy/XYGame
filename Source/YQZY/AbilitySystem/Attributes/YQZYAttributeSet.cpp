// Copyright Epic Games, Inc. All Rights Reserved.

#include "YQZYAttributeSet.h"

#include "AbilitySystem/YQZYAbilitySystemComponent.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(YQZYAttributeSet)

class UWorld;


UYQZYAttributeSet::UYQZYAttributeSet()
{
}

UWorld* UYQZYAttributeSet::GetWorld() const
{
	const UObject* Outer = GetOuter();
	check(Outer);

	return Outer->GetWorld();
}

UYQZYAbilitySystemComponent* UYQZYAttributeSet::GetYQZYAbilitySystemComponent() const
{
	return Cast<UYQZYAbilitySystemComponent>(GetOwningAbilitySystemComponent());
}

