// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

//#include "Settings/YQZYMobilePerformance.h"
#include "GameSettingValueDiscrete.h"

#include "YQZYSettingValueDiscrete_MobileFPSType.generated.h"

enum class EGameSettingChangeReason : uint8;

class UObject;

UCLASS()
class UYQZYSettingValueDiscrete_MobileFPSType : public UGameSettingValueDiscrete
{
	GENERATED_BODY()
	
public:

	UYQZYSettingValueDiscrete_MobileFPSType();

	//~UGameSettingValue interface
	virtual void StoreInitial() override;
	virtual void ResetToDefault() override;
	virtual void RestoreToInitial() override;
	//~End of UGameSettingValue interface

	//~UGameSettingValueDiscrete interface
	virtual void SetDiscreteOptionByIndex(int32 Index) override;
	virtual int32 GetDiscreteOptionIndex() const override;
	virtual TArray<FText> GetDiscreteOptions() const override;
	//~End of UGameSettingValueDiscrete interface

protected:
	/** UFortSettingValue */
	virtual void OnInitialized() override;

	int32 GetValue() const;
	void SetValue(int32 NewLimitFPS, EGameSettingChangeReason InReason);

	int32 GetDefaultFPS() const;

	static FText MakeLimitString(int32 Number);

protected:
	int32 InitialValue;
	TSortedMap<int32, FText> FPSOptions;
};
