// Copyright Epic Games, Inc. All Rights Reserved.

#include "YQZYAbilityCost_PlayerTagStack.h"

#include "GameFramework/Controller.h"
#include "YQZYGameplayAbility.h"
#include "Player/YQZYPlayerState.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(YQZYAbilityCost_PlayerTagStack)

UYQZYAbilityCost_PlayerTagStack::UYQZYAbilityCost_PlayerTagStack()
{
	Quantity.SetValue(1.0f);
}

bool UYQZYAbilityCost_PlayerTagStack::CheckCost(const UYQZYGameplayAbility* Ability, const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, FGameplayTagContainer* OptionalRelevantTags) const
{
	if (AController* PC = Ability->GetControllerFromActorInfo())
	{
		if (AYQZYPlayerState* PS = Cast<AYQZYPlayerState>(PC->PlayerState))
		{
			const int32 AbilityLevel = Ability->GetAbilityLevel(Handle, ActorInfo);

			const float NumStacksReal = Quantity.GetValueAtLevel(AbilityLevel);
			const int32 NumStacks = FMath::TruncToInt(NumStacksReal);

			return PS->GetStatTagStackCount(Tag) >= NumStacks;
		}
	}
	return false;
}

void UYQZYAbilityCost_PlayerTagStack::ApplyCost(const UYQZYGameplayAbility* Ability, const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo)
{
	if (ActorInfo->IsNetAuthority())
	{
		if (AController* PC = Ability->GetControllerFromActorInfo())
		{
			if (AYQZYPlayerState* PS = Cast<AYQZYPlayerState>(PC->PlayerState))
			{
				const int32 AbilityLevel = Ability->GetAbilityLevel(Handle, ActorInfo);

				const float NumStacksReal = Quantity.GetValueAtLevel(AbilityLevel);
				const int32 NumStacks = FMath::TruncToInt(NumStacksReal);

				PS->RemoveStatTagStack(Tag, NumStacks);
			}
		}
	}
}

