// Copyright Epic Games, Inc. All Rights Reserved.

#include "YQZYGameplayAbility_Jump.h"

#include "AbilitySystem/Abilities/YQZYGameplayAbility.h"
#include "Character/YQZYCharacter.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(YQZYGameplayAbility_Jump)

struct FGameplayTagContainer;


UYQZYGameplayAbility_Jump::UYQZYGameplayAbility_Jump(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
	NetExecutionPolicy = EGameplayAbilityNetExecutionPolicy::LocalPredicted;
}

bool UYQZYGameplayAbility_Jump::CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags, const FGameplayTagContainer* TargetTags, FGameplayTagContainer* OptionalRelevantTags) const
{
	if (!ActorInfo || !ActorInfo->AvatarActor.IsValid())
	{
		return false;
	}

	const AYQZYCharacter* YQZYCharacter = Cast<AYQZYCharacter>(ActorInfo->AvatarActor.Get());
	if (!YQZYCharacter || !YQZYCharacter->CanJump())
	{
		return false;
	}

	if (!Super::CanActivateAbility(Handle, ActorInfo, SourceTags, TargetTags, OptionalRelevantTags))
	{
		return false;
	}

	return true;
}

void UYQZYGameplayAbility_Jump::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	// Stop jumping in case the ability blueprint doesn't call it.
	CharacterJumpStop();

	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}

void UYQZYGameplayAbility_Jump::CharacterJumpStart()
{
	if (AYQZYCharacter* YQZYCharacter = GetYQZYCharacterFromActorInfo())
	{
		if (YQZYCharacter->IsLocallyControlled() && !YQZYCharacter->bPressedJump)
		{
			YQZYCharacter->UnCrouch();
			YQZYCharacter->Jump();
		}
	}
}

void UYQZYGameplayAbility_Jump::CharacterJumpStop()
{
	if (AYQZYCharacter* YQZYCharacter = GetYQZYCharacterFromActorInfo())
	{
		if (YQZYCharacter->IsLocallyControlled() && YQZYCharacter->bPressedJump)
		{
			YQZYCharacter->StopJumping();
		}
	}
}

