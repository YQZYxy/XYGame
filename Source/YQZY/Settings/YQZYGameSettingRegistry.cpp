// Copyright Epic Games, Inc. All Rights Reserved.

#include "YQZYGameSettingRegistry.h"

#include "GameSettingCollection.h"
#include "YQZYSettingsLocal.h"
#include "YQZYSettingsShared.h"
#include "Player/YQZYLocalPlayer.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(YQZYGameSettingRegistry)

DEFINE_LOG_CATEGORY(LogYQZYGameSettingRegistry);

#define LOCTEXT_NAMESPACE "YQZY"

//--------------------------------------
// UYQZYGameSettingRegistry
//--------------------------------------

UYQZYGameSettingRegistry::UYQZYGameSettingRegistry()
{
}

UYQZYGameSettingRegistry* UYQZYGameSettingRegistry::Get(UYQZYLocalPlayer* InLocalPlayer)
{
	UYQZYGameSettingRegistry* Registry = FindObject<UYQZYGameSettingRegistry>(InLocalPlayer, TEXT("YQZYGameSettingRegistry"), true);
	if (Registry == nullptr)
	{
		Registry = NewObject<UYQZYGameSettingRegistry>(InLocalPlayer, TEXT("YQZYGameSettingRegistry"));
		Registry->Initialize(InLocalPlayer);
	}

	return Registry;
}

bool UYQZYGameSettingRegistry::IsFinishedInitializing() const
{
	if (Super::IsFinishedInitializing())
	{
		if (UYQZYLocalPlayer* LocalPlayer = Cast<UYQZYLocalPlayer>(OwningLocalPlayer))
		{
			if (LocalPlayer->GetSharedSettings() == nullptr)
			{
				return false;
			}
		}

		return true;
	}

	return false;
}

void UYQZYGameSettingRegistry::OnInitialize(ULocalPlayer* InLocalPlayer)
{
	UYQZYLocalPlayer* YQZYLocalPlayer = Cast<UYQZYLocalPlayer>(InLocalPlayer);

	VideoSettings = InitializeVideoSettings(YQZYLocalPlayer);
	InitializeVideoSettings_FrameRates(VideoSettings, YQZYLocalPlayer);
	RegisterSetting(VideoSettings);

	AudioSettings = InitializeAudioSettings(YQZYLocalPlayer);
	RegisterSetting(AudioSettings);

	GameplaySettings = InitializeGameplaySettings(YQZYLocalPlayer);
	RegisterSetting(GameplaySettings);

	MouseAndKeyboardSettings = InitializeMouseAndKeyboardSettings(YQZYLocalPlayer);
	RegisterSetting(MouseAndKeyboardSettings);

	GamepadSettings = InitializeGamepadSettings(YQZYLocalPlayer);
	RegisterSetting(GamepadSettings);
}

void UYQZYGameSettingRegistry::SaveChanges()
{
	Super::SaveChanges();
	
	if (UYQZYLocalPlayer* LocalPlayer = Cast<UYQZYLocalPlayer>(OwningLocalPlayer))
	{
		// Game user settings need to be applied to handle things like resolution, this saves indirectly
		LocalPlayer->GetLocalSettings()->ApplySettings(false);
		
		LocalPlayer->GetSharedSettings()->ApplySettings();
		LocalPlayer->GetSharedSettings()->SaveSettings();
	}
}

#undef LOCTEXT_NAMESPACE

