// Copyright Epic Games, Inc. All Rights Reserved.

#include "YQZYWeaponDebugSettings.h"
#include "Misc/App.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(YQZYWeaponDebugSettings)

UYQZYWeaponDebugSettings::UYQZYWeaponDebugSettings()
{
}

FName UYQZYWeaponDebugSettings::GetCategoryName() const
{
	return FApp::GetProjectName();
}

