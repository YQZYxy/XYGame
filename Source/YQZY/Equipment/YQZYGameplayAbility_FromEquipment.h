// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "AbilitySystem/Abilities/YQZYGameplayAbility.h"

#include "YQZYGameplayAbility_FromEquipment.generated.h"

class UYQZYEquipmentInstance;
class UYQZYInventoryItemInstance;

/**
 * UYQZYGameplayAbility_FromEquipment
 *
 * An ability granted by and associated with an equipment instance
 */
UCLASS()
class UYQZYGameplayAbility_FromEquipment : public UYQZYGameplayAbility
{
	GENERATED_BODY()

public:

	UYQZYGameplayAbility_FromEquipment(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	UFUNCTION(BlueprintCallable, Category="YQZY|Ability")
	UYQZYEquipmentInstance* GetAssociatedEquipment() const;

	UFUNCTION(BlueprintCallable, Category = "YQZY|Ability")
	UYQZYInventoryItemInstance* GetAssociatedItem() const;

#if WITH_EDITOR
	virtual EDataValidationResult IsDataValid(class FDataValidationContext& Context) const override;
#endif

};
