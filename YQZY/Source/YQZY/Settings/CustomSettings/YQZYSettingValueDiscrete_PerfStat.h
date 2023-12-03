// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "GameSettingValueDiscrete.h"

#include "YQZYSettingValueDiscrete_PerfStat.generated.h"

enum class EYQZYDisplayablePerformanceStat : uint8;
enum class EYQZYStatDisplayMode : uint8;

class UObject;

UCLASS()
class UYQZYSettingValueDiscrete_PerfStat : public UGameSettingValueDiscrete
{
	GENERATED_BODY()
	
public:

	UYQZYSettingValueDiscrete_PerfStat();

	void SetStat(EYQZYDisplayablePerformanceStat InStat);

	/** UGameSettingValue */
	virtual void StoreInitial() override;
	virtual void ResetToDefault() override;
	virtual void RestoreToInitial() override;

	/** UGameSettingValueDiscrete */
	virtual void SetDiscreteOptionByIndex(int32 Index) override;
	virtual int32 GetDiscreteOptionIndex() const override;
	virtual TArray<FText> GetDiscreteOptions() const override;

protected:
	/** UGameSettingValue */
	virtual void OnInitialized() override;
	
	void AddMode(FText&& Label, EYQZYStatDisplayMode Mode);
protected:
	TArray<FText> Options;
	TArray<EYQZYStatDisplayMode> DisplayModes;

	EYQZYDisplayablePerformanceStat StatToDisplay;
	EYQZYStatDisplayMode InitialMode;
};
