// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "YQZYGameplayAbility.h"

#include "YQZYGameplayAbility_Jump.generated.h"

class UObject;
struct FFrame;
struct FGameplayAbilityActorInfo;
struct FGameplayTagContainer;


/**
 * UYQZYGameplayAbility_Jump
 *
 *	Gameplay ability used for character jumping.
 */
UCLASS(Abstract)
class UYQZYGameplayAbility_Jump : public UYQZYGameplayAbility
{
	GENERATED_BODY()

public:

	UYQZYGameplayAbility_Jump(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

protected:

	virtual bool CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags, const FGameplayTagContainer* TargetTags, FGameplayTagContainer* OptionalRelevantTags) const override;
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;

	UFUNCTION(BlueprintCallable, Category = "YQZY|Ability")
	void CharacterJumpStart();

	UFUNCTION(BlueprintCallable, Category = "YQZY|Ability")
	void CharacterJumpStop();
};
