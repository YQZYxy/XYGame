// Copyright Epic Games, Inc. All Rights Reserved.

#include "AssetTypeActions_YQZYContextEffectsLibrary.h"

#include "Feedback/ContextEffects/YQZYContextEffectsLibrary.h"

class UClass;

#define LOCTEXT_NAMESPACE "AssetTypeActions"

UClass* FAssetTypeActions_YQZYContextEffectsLibrary::GetSupportedClass() const
{
	return UYQZYContextEffectsLibrary::StaticClass();
}

#undef LOCTEXT_NAMESPACE
