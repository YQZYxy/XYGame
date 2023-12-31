// Copyright Epic Games, Inc. All Rights Reserved.

#include "XYGameAttributeSet.h"

#include "Net/UnrealNetwork.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(XYGameAttributeSet)

class FLifetimeProperty;

UXYGameAttributeSet::UXYGameAttributeSet()
	: BombsRemaining(1.0f)
	, BombCapacity(1.0f)
	, BombRange(2.0f)
	, MovementSpeed(400.0f)
{
}

void UXYGameAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(ThisClass, BombsRemaining, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(ThisClass, BombCapacity, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(ThisClass, BombRange, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(ThisClass, MovementSpeed, COND_None, REPNOTIFY_Always);
}

void UXYGameAttributeSet::OnRep_BombsRemaining(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(ThisClass, BombsRemaining, OldValue);
}

void UXYGameAttributeSet::OnRep_BombCapacity(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(ThisClass, BombCapacity, OldValue);
}

void UXYGameAttributeSet::OnRep_BombRange(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(ThisClass, BombRange, OldValue);
}

void UXYGameAttributeSet::OnRep_MovementSpeed(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(ThisClass, MovementSpeed, OldValue);
}

void UXYGameAttributeSet::PreAttributeBaseChange(const FGameplayAttribute& Attribute, float& NewValue) const
{
	Super::PreAttributeBaseChange(Attribute, NewValue);

	ClampAttribute(Attribute, NewValue);
}

void UXYGameAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);

	ClampAttribute(Attribute, NewValue);
}

void UXYGameAttributeSet::ClampAttribute(const FGameplayAttribute& Attribute, float& NewValue) const
{
	if (Attribute == GetBombsRemainingAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.0f, GetBombCapacity());
	}
	else if (Attribute == GetBombCapacityAttribute())
	{
		NewValue = FMath::Max(NewValue, 1.0f);
	}
	else if (Attribute == GetBombRangeAttribute())
	{
		NewValue = FMath::Max(NewValue, 1.0f);
	}
	else if (Attribute == GetMovementSpeedAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 200.0f, 800.0f);
	}
}

