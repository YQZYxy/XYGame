// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Inventory/YQZYInventoryItemDefinition.h"

#include "InventoryFragment_ReticleConfig.generated.h"

class UYQZYReticleWidgetBase;
class UObject;

UCLASS()
class UInventoryFragment_ReticleConfig : public UYQZYInventoryItemFragment
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Reticle)
	TArray<TSubclassOf<UYQZYReticleWidgetBase>> ReticleWidgets;
};
