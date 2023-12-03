// Copyright Epic Games, Inc. All Rights Reserved.

#include "YQZYCombatSet.h"

#include "AbilitySystem/Attributes/YQZYAttributeSet.h"
#include "Net/UnrealNetwork.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(YQZYCombatSet)

class FLifetimeProperty;


UYQZYCombatSet::UYQZYCombatSet()
	: BaseDamage(0.0f)
	, BaseHeal(0.0f)
{
}

void UYQZYCombatSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(UYQZYCombatSet, BaseDamage, COND_OwnerOnly, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UYQZYCombatSet, BaseHeal, COND_OwnerOnly, REPNOTIFY_Always);
}

void UYQZYCombatSet::OnRep_BaseDamage(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UYQZYCombatSet, BaseDamage, OldValue);
}

void UYQZYCombatSet::OnRep_BaseHeal(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UYQZYCombatSet, BaseHeal, OldValue);
}

