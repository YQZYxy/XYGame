// Copyright Epic Games, Inc. All Rights Reserved.

#include "YQZYAimSensitivityData.h"

#include "Settings/YQZYSettingsShared.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(YQZYAimSensitivityData)

UYQZYAimSensitivityData::UYQZYAimSensitivityData(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	SensitivityMap =
	{
		{ EYQZYGamepadSensitivity::Slow,			0.5f },
		{ EYQZYGamepadSensitivity::SlowPlus,		0.75f },
		{ EYQZYGamepadSensitivity::SlowPlusPlus,	0.9f },
		{ EYQZYGamepadSensitivity::Normal,		1.0f },
		{ EYQZYGamepadSensitivity::NormalPlus,	1.1f },
		{ EYQZYGamepadSensitivity::NormalPlusPlus,1.25f },
		{ EYQZYGamepadSensitivity::Fast,			1.5f },
		{ EYQZYGamepadSensitivity::FastPlus,		1.75f },
		{ EYQZYGamepadSensitivity::FastPlusPlus,	2.0f },
		{ EYQZYGamepadSensitivity::Insane,		2.5f },
	};
}

const float UYQZYAimSensitivityData::SensitivtyEnumToFloat(const EYQZYGamepadSensitivity InSensitivity) const
{
	if (const float* Sens = SensitivityMap.Find(InSensitivity))
	{
		return *Sens;
	}

	return 1.0f;
}

