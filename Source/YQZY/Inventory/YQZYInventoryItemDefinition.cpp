// Copyright Epic Games, Inc. All Rights Reserved.

#include "YQZYInventoryItemDefinition.h"

#include "Templates/SubclassOf.h"
#include "UObject/ObjectPtr.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(YQZYInventoryItemDefinition)

//////////////////////////////////////////////////////////////////////
// UYQZYInventoryItemDefinition

UYQZYInventoryItemDefinition::UYQZYInventoryItemDefinition(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

const UYQZYInventoryItemFragment* UYQZYInventoryItemDefinition::FindFragmentByClass(TSubclassOf<UYQZYInventoryItemFragment> FragmentClass) const
{
	if (FragmentClass != nullptr)
	{
		for (UYQZYInventoryItemFragment* Fragment : Fragments)
		{
			if (Fragment && Fragment->IsA(FragmentClass))
			{
				return Fragment;
			}
		}
	}

	return nullptr;
}

//////////////////////////////////////////////////////////////////////
// UYQZYInventoryItemDefinition

const UYQZYInventoryItemFragment* UYQZYInventoryFunctionLibrary::FindItemDefinitionFragment(TSubclassOf<UYQZYInventoryItemDefinition> ItemDef, TSubclassOf<UYQZYInventoryItemFragment> FragmentClass)
{
	if ((ItemDef != nullptr) && (FragmentClass != nullptr))
	{
		return GetDefault<UYQZYInventoryItemDefinition>(ItemDef)->FindFragmentByClass(FragmentClass);
	}
	return nullptr;
}

