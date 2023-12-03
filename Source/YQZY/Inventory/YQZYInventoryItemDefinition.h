// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"

#include "YQZYInventoryItemDefinition.generated.h"

template <typename T> class TSubclassOf;

class UYQZYInventoryItemInstance;
struct FFrame;

//////////////////////////////////////////////////////////////////////

// Represents a fragment of an item definition
UCLASS(DefaultToInstanced, EditInlineNew, Abstract)
class YQZY_API UYQZYInventoryItemFragment : public UObject
{
	GENERATED_BODY()

public:
	virtual void OnInstanceCreated(UYQZYInventoryItemInstance* Instance) const {}
};

//////////////////////////////////////////////////////////////////////

/**
 * UYQZYInventoryItemDefinition
 */
UCLASS(Blueprintable, Const, Abstract)
class UYQZYInventoryItemDefinition : public UObject
{
	GENERATED_BODY()

public:
	UYQZYInventoryItemDefinition(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=Display)
	FText DisplayName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=Display, Instanced)
	TArray<TObjectPtr<UYQZYInventoryItemFragment>> Fragments;

public:
	const UYQZYInventoryItemFragment* FindFragmentByClass(TSubclassOf<UYQZYInventoryItemFragment> FragmentClass) const;
};

//@TODO: Make into a subsystem instead?
UCLASS()
class UYQZYInventoryFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

	UFUNCTION(BlueprintCallable, meta=(DeterminesOutputType=FragmentClass))
	static const UYQZYInventoryItemFragment* FindItemDefinitionFragment(TSubclassOf<UYQZYInventoryItemDefinition> ItemDef, TSubclassOf<UYQZYInventoryItemFragment> FragmentClass);
};
