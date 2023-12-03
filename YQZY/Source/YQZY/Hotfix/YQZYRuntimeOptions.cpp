// Copyright Epic Games, Inc. All Rights Reserved.

#include "YQZYRuntimeOptions.h"

#include "UObject/Class.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(YQZYRuntimeOptions)

UYQZYRuntimeOptions::UYQZYRuntimeOptions()
{
	OptionCommandPrefix = TEXT("ro");
}

UYQZYRuntimeOptions* UYQZYRuntimeOptions::GetRuntimeOptions()
{
	return GetMutableDefault<UYQZYRuntimeOptions>();
}

const UYQZYRuntimeOptions& UYQZYRuntimeOptions::Get()
{
	const UYQZYRuntimeOptions& RuntimeOptions = *GetDefault<UYQZYRuntimeOptions>();
	return RuntimeOptions;
}
