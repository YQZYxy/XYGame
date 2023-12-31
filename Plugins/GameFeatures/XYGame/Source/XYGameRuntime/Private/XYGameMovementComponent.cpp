// Copyright Epic Games, Inc. All Rights Reserved.

#include "XYGameMovementComponent.h"

#include "AbilitySystemGlobals.h"
#include "XYGameAttributeSet.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(XYGameMovementComponent)

UXYGameMovementComponent::UXYGameMovementComponent(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

float UXYGameMovementComponent::GetMaxSpeed() const
{
	if (UAbilitySystemComponent* ASC = UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(GetOwner()))
	{
		if (MovementMode == MOVE_Walking)
		{
			if (ASC->HasMatchingGameplayTag(TAG_Gameplay_MovementStopped))
			{
				return 0;
			}

			const float MaxSpeedFromAttribute = ASC->GetNumericAttribute(UXYGameAttributeSet::GetMovementSpeedAttribute());
			if (MaxSpeedFromAttribute > 0.0f)
			{
				return MaxSpeedFromAttribute;
			}
		}
	}

	return Super::GetMaxSpeed();
}
