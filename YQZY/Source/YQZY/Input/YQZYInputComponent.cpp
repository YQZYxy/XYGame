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

	UYQZYLocalPlayer* LocalPlayer = InputSubsystem->GetLocalPlayer<UYQZYLocalPlayer>();
	check(LocalPlayer);

	// Add any registered input mappings from the settings!
	if (UYQZYSettingsLocal* LocalSettings = UYQZYSettingsLocal::Get())
	{	
		// Tell enhanced input about any custom keymappings that the player may have customized
		for (const TPair<FName, FKey>& Pair : LocalSettings->GetCustomPlayerInputConfig())
		{
			if (Pair.Key != NAME_None && Pair.Value.IsValid())
			{
				InputSubsystem->AddPlayerMappedKeyInSlot(Pair.Key, Pair.Value);
			}
		}
	}
}

void UYQZYInputComponent::RemoveInputMappings(const UYQZYInputConfig* InputConfig, UEnhancedInputLocalPlayerSubsystem* InputSubsystem) const
{
	check(InputConfig);
	check(InputSubsystem);

	UYQZYLocalPlayer* LocalPlayer = InputSubsystem->GetLocalPlayer<UYQZYLocalPlayer>();
	check(LocalPlayer);
	
	if (UYQZYSettingsLocal* LocalSettings = UYQZYSettingsLocal::Get())
	{
		// Remove any registered input contexts
		const TArray<FLoadedMappableConfigPair>& Configs = LocalSettings->GetAllRegisteredInputConfigs();
		for (const FLoadedMappableConfigPair& Pair : Configs)
		{
			InputSubsystem->RemovePlayerMappableConfig(Pair.Config);
		}
		
		// Clear any player mapped keys from enhanced input
		for (const TPair<FName, FKey>& Pair : LocalSettings->GetCustomPlayerInputConfig())
		{
			InputSubsystem->RemovePlayerMappedKeyInSlot(Pair.Key);
		}
	}
}

void UYQZYInputComponent::RemoveBinds(TArray<uint32>& BindHandles)
{
	for (uint32 Handle : BindHandles)
	{
		RemoveBindingByHandle(Handle);
	}
	BindHandles.Reset();
}
