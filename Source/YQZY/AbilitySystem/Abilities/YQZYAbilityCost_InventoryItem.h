// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "YQZYAbilityCost.h"
#include "ScalableFloat.h"
#include "Templates/SubclassOf.h"

#include "YQZYAbilityCost_InventoryItem.generated.h"

struct FGameplayAbilityActivationInfo;
struct FGameplayAbilitySpecHandle;

class UYQZYGameplayAbility;
class UYQZYInventoryItemDefinition;
class UObject;
struct FGameplayAbilityActorInfo;
struct FGameplayTagContainer;

/**
 * Represents a cost that requires expending a quantity of an inventory item
 */
UCLASS(meta=(DisplayName="Inventory Item"))
class UYQZYAbilityCost_InventoryItem : public UYQZYAbilityCost
{
	GENERATED_BODY()

public:
	UYQZYAbilityCost_InventoryItem();

	//~UYQZYAbilityCost interface
	virtual bool CheckCost(const UYQZYGameplayAbility* Ability, const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, FGameplayTagContainer* OptionalRelevantTags) const override;
	virtual void ApplyCost(const UYQZYGameplayAbility* Ability, const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo) override;
	//~End of UYQZYAbilityCost interface

protected:
	/** How much of the item to spend (keyed on ability level) */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=AbilityCost)
	FScalableFloat Quantity;

	/** Which item to consume */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=AbilityCost)
	TSubclassOf<UYQZYInventoryItemDefinition> ItemDefinition;
};
