// Copyright Epic Games, Inc. All Rights Reserved.

#include "YQZYGameplayAbility_Death.h"

#include "AbilitySystem/Abilities/YQZYGameplayAbility.h"
#include "AbilitySystem/YQZYAbilitySystemComponent.h"
#include "Character/YQZYHealthComponent.h"
#include "YQZYGameplayTags.h"
#include "YQZYLog.h"
#include "Trace/Trace.inl"

#include UE_INLINE_GENERATED_CPP_BY_NAME(YQZYGameplayAbility_Death)

UYQZYGameplayAbility_Death::UYQZYGameplayAbility_Death(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
	NetExecutionPolicy = EGameplayAbilityNetExecutionPolicy::ServerInitiated;

	bAutoStartDeath = true;

	if (HasAnyFlags(RF_ClassDefaultObject))
	{
		// Add the ability trigger tag as default to the CDO.
		FAbilityTriggerData TriggerData;
		TriggerData.TriggerTag = YQZYGameplayTags::GameplayEvent_Death;
		TriggerData.TriggerSource = EGameplayAbilityTriggerSource::GameplayEvent;
		AbilityTriggers.Add(TriggerData);
	}
}

void UYQZYGameplayAbility_Death::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	check(ActorInfo);

	UYQZYAbilitySystemComponent* YQZYASC = CastChecked<UYQZYAbilitySystemComponent>(ActorInfo->AbilitySystemComponent.Get());

	FGameplayTagContainer AbilityTypesToIgnore;
	AbilityTypesToIgnore.AddTag(YQZYGameplayTags::Ability_Behavior_SurvivesDeath);

	// Cancel all abilities and block others from starting.
	YQZYASC->CancelAbilities(nullptr, &AbilityTypesToIgnore, this);

	SetCanBeCanceled(false);

	if (!ChangeActivationGroup(EYQZYAbilityActivationGroup::Exclusive_Blocking))
	{
		UE_LOG(YQZYLog, Error, TEXT("UYQZYGameplayAbility_Death::ActivateAbility: Ability [%s] failed to change activation group to blocking."), *GetName());
	}

	if (bAutoStartDeath)
	{
		StartDeath();
	}

	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
}

void UYQZYGameplayAbility_Death::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	check(ActorInfo);

	// Always try to finish the death when the ability ends in case the ability doesn't.
	// This won't do anything if the death hasn't been started.
	FinishDeath();

	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}

void UYQZYGameplayAbility_Death::StartDeath()
{
	if (UYQZYHealthComponent* HealthComponent = UYQZYHealthComponent::FindHealthComponent(GetAvatarActorFromActorInfo()))
	{
		if (HealthComponent->GetDeathState() == EYQZYDeathState::NotDead)
		{
			HealthComponent->StartDeath();
		}
	}
}

void UYQZYGameplayAbility_Death::FinishDeath()
{
	if (UYQZYHealthComponent* HealthComponent = UYQZYHealthComponent::FindHealthComponent(GetAvatarActorFromActorInfo()))
	{
		if (HealthComponent->GetDeathState() == EYQZYDeathState::DeathStarted)
		{
			HealthComponent->FinishDeath();
		}
	}
}

