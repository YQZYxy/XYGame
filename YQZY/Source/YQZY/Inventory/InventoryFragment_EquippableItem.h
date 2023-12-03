// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Inventory/YQZYInventoryItemDefinition.h"
#include "Templates/SubclassOf.h"

#include "InventoryFragment_EquippableItem.generated.h"

class UYQZYEquipmentDefinition;
class UObject;

UCLASS()
class UInventoryFragment_EquippableItem : public UYQZYInventoryItemFragment
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Category=YQZY)
	TSubclassOf<UYQZYEquipmentDefinition> EquipmentDefinition;
};
