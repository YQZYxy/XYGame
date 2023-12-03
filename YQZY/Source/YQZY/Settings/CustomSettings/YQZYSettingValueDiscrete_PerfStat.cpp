// Copyright Epic Games, Inc. All Rights Reserved.

#include "YQZYSettingValueDiscrete_PerfStat.h"

#include "CommonUIVisibilitySubsystem.h"
#include "Performance/YQZYPerformanceSettings.h"
#include "Performance/YQZYPerformanceStatTypes.h"
#include "Settings/YQZYSettingsLocal.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(YQZYSettingValueDiscrete_PerfStat)

class ULocalPlayer;

#define LOCTEXT_NAMESPACE "YQZYSettings"

//////////////////////////////////////////////////////////////////////

class FGameSettingEditCondition_PerfStatAllowed : public FGameSettingEditCondition
{
public:
	static TSharedRef<FGameSettingEditCondition_PerfStatAllowed> Get(EYQZYDisplayablePerformanceStat Stat)
	{
		return MakeShared<FGameSettingEditCondition_PerfStatAllowed>(Stat);
	}

	FGameSettingEditCondition_PerfStatAllowed(EYQZYDisplayablePerformanceStat Stat)
		: AssociatedStat(Stat)
	{
	}

	//~FGameSettingEditCondition interface
	virtual void GatherEditState(const ULocalPlayer* InLocalPlayer, FGameSettingEditableState& InOutEditState) const override
	{
		const FGameplayTagContainer& VisibilityTags = UCommonUIVisibilitySubsystem::GetChecked(InLocalPlayer)->GetVisibilityTags();

		bool bCanShowStat = false;
		for (const FYQZYPerformanceStatGroup& Group : GetDefault<UYQZYPerformanceSettings>()->UserFacingPerformanceStats) //@TODO: Move this stuff to per-platform instead of doing vis queries too?
		{
			if (Group.AllowedStats.Contains(AssociatedStat))
			{
				const bool bShowGroup = (Group.VisibilityQuery.IsEmpty() || Group.VisibilityQuery.Matches(VisibilityTags));
				if (bShowGroup)
				{
					bCanShowStat = true;
					break;
				}
			}
		}

		if (!bCanShowStat)
		{
			InOutEditState.Hide(TEXT("Stat is not listed in UYQZYPerformanceSettings or is suppressed by current platform traits"));
		}
	}
	//~End of FGameSettingEditCondition interface

private:
	EYQZYDisplayablePerformanceStat AssociatedStat;
};

//////////////////////////////////////////////////////////////////////

UYQZYSettingValueDiscrete_PerfStat::UYQZYSettingValueDiscrete_PerfStat()
{
}

void UYQZYSettingValueDiscrete_PerfStat::SetStat(EYQZYDisplayablePerformanceStat InStat)
{
	StatToDisplay = InStat;
	SetDevName(FName(*FString::Printf(TEXT("PerfStat_%d"), (int32)StatToDisplay)));
	AddEditCondition(FGameSettingEditCondition_PerfStatAllowed::Get(StatToDisplay));
}

void UYQZYSettingValueDiscrete_PerfStat::AddMode(FText&& Label, EYQZYStatDisplayMode Mode)
{
	Options.Emplace(MoveTemp(Label));
	DisplayModes.Add(Mode);
}

void UYQZYSettingValueDiscrete_PerfStat::OnInitialized()
{
	Super::OnInitialized();

	AddMode(LOCTEXT("PerfStatDisplayMode_None", "None"), EYQZYStatDisplayMode::Hidden);
	AddMode(LOCTEXT("PerfStatDisplayMode_TextOnly", "Text Only"), EYQZYStatDisplayMode::TextOnly);
	AddMode(LOCTEXT("PerfStatDisplayMode_GraphOnly", "Graph Only"), EYQZYStatDisplayMode::GraphOnly);
	AddMode(LOCTEXT("PerfStatDisplayMode_TextAndGraph", "Text and Graph"), EYQZYStatDisplayMode::TextAndGraph);
}

void UYQZYSettingValueDiscrete_PerfStat::StoreInitial()
{
	const UYQZYSettingsLocal* Settings = UYQZYSettingsLocal::Get();
	InitialMode = Settings->GetPerfStatDisplayState(StatToDisplay);
}

void UYQZYSettingValueDiscrete_PerfStat::ResetToDefault()
{
	UYQZYSettingsLocal* Settings = UYQZYSettingsLocal::Get();
	Settings->SetPerfStatDisplayState(StatToDisplay, EYQZYStatDisplayMode::Hidden);
	NotifySettingChanged(EGameSettingChangeReason::ResetToDefault);
}

void UYQZYSettingValueDiscrete_PerfStat::RestoreToInitial()
{
	UYQZYSettingsLocal* Settings = UYQZYSettingsLocal::Get();
	Settings->SetPerfStatDisplayState(StatToDisplay, InitialMode);
	NotifySettingChanged(EGameSettingChangeReason::RestoreToInitial);
}

void UYQZYSettingValueDiscrete_PerfStat::SetDiscreteOptionByIndex(int32 Index)
{
	if (DisplayModes.IsValidIndex(Index))
	{
		const EYQZYStatDisplayMode DisplayMode = DisplayModes[Index];

		UYQZYSettingsLocal* Settings = UYQZYSettingsLocal::Get();
		Settings->SetPerfStatDisplayState(StatToDisplay, DisplayMode);
	}
	NotifySettingChanged(EGameSettingChangeReason::Change);
}

int32 UYQZYSettingValueDiscrete_PerfStat::GetDiscreteOptionIndex() const
{
	const UYQZYSettingsLocal* Settings = UYQZYSettingsLocal::Get();
	return DisplayModes.Find(Settings->GetPerfStatDisplayState(StatToDisplay));
}

TArray<FText> UYQZYSettingValueDiscrete_PerfStat::GetDiscreteOptions() const
{
	return Options;
}

#undef LOCTEXT_NAMESPACE
