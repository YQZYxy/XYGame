// Copyright Epic Games, Inc. All Rights Reserved.

#include "YQZYSettingValueDiscrete_MobileFPSType.h"

#include "Performance/YQZYPerformanceSettings.h"
#include "Settings/YQZYSettingsLocal.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(YQZYSettingValueDiscrete_MobileFPSType)

#define LOCTEXT_NAMESPACE "YQZYSettings"

UYQZYSettingValueDiscrete_MobileFPSType::UYQZYSettingValueDiscrete_MobileFPSType()
{
}

void UYQZYSettingValueDiscrete_MobileFPSType::OnInitialized()
{
	Super::OnInitialized();

	const UYQZYPlatformSpecificRenderingSettings* PlatformSettings = UYQZYPlatformSpecificRenderingSettings::Get();
	const UYQZYSettingsLocal* UserSettings = UYQZYSettingsLocal::Get();

	for (int32 TestLimit : PlatformSettings->MobileFrameRateLimits)
	{
		if (UYQZYSettingsLocal::IsSupportedMobileFramePace(TestLimit))
		{
			FPSOptions.Add(TestLimit, MakeLimitString(TestLimit));
		}
	}

	const int32 FirstFrameRateWithQualityLimit = UserSettings->GetFirstFrameRateWithQualityLimit();
	if (FirstFrameRateWithQualityLimit > 0)
	{
		SetWarningRichText(FText::Format(LOCTEXT("MobileFPSType_Note", "<strong>Note: Changing the framerate setting to {0} or higher might lower your Quality Presets.</>"), MakeLimitString(FirstFrameRateWithQualityLimit)));
	}
}

int32 UYQZYSettingValueDiscrete_MobileFPSType::GetDefaultFPS() const
{
	return UYQZYSettingsLocal::GetDefaultMobileFrameRate();
}

FText UYQZYSettingValueDiscrete_MobileFPSType::MakeLimitString(int32 Number)
{
	return FText::Format(LOCTEXT("MobileFrameRateOption", "{0} FPS"), FText::AsNumber(Number));
}

void UYQZYSettingValueDiscrete_MobileFPSType::StoreInitial()
{
	InitialValue = GetValue();
}

void UYQZYSettingValueDiscrete_MobileFPSType::ResetToDefault()
{
	SetValue(GetDefaultFPS(), EGameSettingChangeReason::ResetToDefault);
}

void UYQZYSettingValueDiscrete_MobileFPSType::RestoreToInitial()
{
	SetValue(InitialValue, EGameSettingChangeReason::RestoreToInitial);
}

void UYQZYSettingValueDiscrete_MobileFPSType::SetDiscreteOptionByIndex(int32 Index)
{
	TArray<int32> FPSOptionsModes;
	FPSOptions.GenerateKeyArray(FPSOptionsModes);

	int32 NewMode = FPSOptionsModes.IsValidIndex(Index) ? FPSOptionsModes[Index] : GetDefaultFPS();

	SetValue(NewMode, EGameSettingChangeReason::Change);
}

int32 UYQZYSettingValueDiscrete_MobileFPSType::GetDiscreteOptionIndex() const
{
	TArray<int32> FPSOptionsModes;
	FPSOptions.GenerateKeyArray(FPSOptionsModes);
	return FPSOptionsModes.IndexOfByKey(GetValue());
}

TArray<FText> UYQZYSettingValueDiscrete_MobileFPSType::GetDiscreteOptions() const
{
	TArray<FText> Options;
	FPSOptions.GenerateValueArray(Options);

	return Options;
}

int32 UYQZYSettingValueDiscrete_MobileFPSType::GetValue() const
{
	return UYQZYSettingsLocal::Get()->GetDesiredMobileFrameRateLimit();
}

void UYQZYSettingValueDiscrete_MobileFPSType::SetValue(int32 NewLimitFPS, EGameSettingChangeReason InReason)
{
	UYQZYSettingsLocal::Get()->SetDesiredMobileFrameRateLimit(NewLimitFPS);

	NotifySettingChanged(InReason);
}

#undef LOCTEXT_NAMESPACE

