// Copyright Epic Games, Inc. All Rights Reserved.

#include "YQZYPerformanceSettings.h"

#include "Engine/PlatformSettingsManager.h"
#include "Misc/EnumRange.h"
#include "Performance/YQZYPerformanceStatTypes.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(YQZYPerformanceSettings)

//////////////////////////////////////////////////////////////////////

UYQZYPlatformSpecificRenderingSettings::UYQZYPlatformSpecificRenderingSettings()
{
	MobileFrameRateLimits.Append({ 20, 30, 45, 60, 90, 120 });
}

const UYQZYPlatformSpecificRenderingSettings* UYQZYPlatformSpecificRenderingSettings::Get()
{
	UYQZYPlatformSpecificRenderingSettings* Result = UPlatformSettingsManager::Get().GetSettingsForPlatform<ThisClass>();
	check(Result);
	return Result;
}

//////////////////////////////////////////////////////////////////////

UYQZYPerformanceSettings::UYQZYPerformanceSettings()
{
	PerPlatformSettings.Initialize(UYQZYPlatformSpecificRenderingSettings::StaticClass());

	CategoryName = TEXT("Game");

	DesktopFrameRateLimits.Append({ 30, 60, 120, 144, 160, 165, 180, 200, 240, 360 });

	// Default to all stats are allowed
	FYQZYPerformanceStatGroup& StatGroup = UserFacingPerformanceStats.AddDefaulted_GetRef();
	for (EYQZYDisplayablePerformanceStat PerfStat : TEnumRange<EYQZYDisplayablePerformanceStat>())
	{
		StatGroup.AllowedStats.Add(PerfStat);
	}
}

