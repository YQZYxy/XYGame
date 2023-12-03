// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CommonUserWidget.h"
#include "Performance/YQZYPerformanceStatTypes.h"

#include "YQZYPerfStatContainerBase.generated.h"

class UObject;
struct FFrame;

/**
 * UYQZYPerfStatsContainerBase
 *
 * Panel that contains a set of UYQZYPerfStatWidgetBase widgets and manages
 * their visibility based on user settings.
 */
 UCLASS(Abstract)
class UYQZYPerfStatContainerBase : public UCommonUserWidget
{
public:
	UYQZYPerfStatContainerBase(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	GENERATED_BODY()

	//~UUserWidget interface
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;
	//~End of UUserWidget interface

	UFUNCTION(BlueprintCallable)
	void UpdateVisibilityOfChildren();

protected:
	// Are we showing text or graph stats?
	UPROPERTY(EditAnywhere, Category=Display)
	EYQZYStatDisplayMode StatDisplayModeFilter = EYQZYStatDisplayMode::TextAndGraph;
};
