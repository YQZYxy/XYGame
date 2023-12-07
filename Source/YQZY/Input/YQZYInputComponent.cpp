// Copyright Epic Games, Inc. All Rights Reserved.

#include "YQZYInputComponent.h"

#include "EnhancedInputSubsystems.h"
#include "Player/YQZYLocalPlayer.h"
#include "Settings/YQZYSettingsLocal.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(YQZYInputComponent)

class UYQZYInputConfig;

UYQZYInputComponent::UYQZYInputComponent(const FObjectInitializer& ObjectInitializer)
{
}

void UYQZYInputComponent::AddInputMappings(const UYQZYInputConfig* InputConfig, UEnhancedInputLocalPlayerSubsystem* InputSubsystem) const
{
	check(InputConfig);
	check(InputSubsystem);

	// Here you can handle any custom logic to add something from your input config if required
}

void UYQZYInputComponent::RemoveInputMappings(const UYQZYInputConfig* InputConfig, UEnhancedInputLocalPlayerSubsystem* InputSubsystem) const
{
	check(InputConfig);
	check(InputSubsystem);

	// Here you can handle any custom logic to remove input mappings that you may have added above
}

void UYQZYInputComponent::RemoveBinds(TArray<uint32>& BindHandles)
{
	for (uint32 Handle : BindHandles)
	{
		RemoveBindingByHandle(Handle);
	}
	BindHandles.Reset();
}
