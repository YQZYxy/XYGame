// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "YQZYActivatableWidget.h"

#include "YQZYHUDLayout.generated.h"

class UCommonActivatableWidget;
class UObject;


/**
 * UYQZYHUDLayout
 *
 *	Widget used to lay out the player's HUD (typically specified by an Add Widgets action in the experience)
 */
UCLASS(Abstract, BlueprintType, Blueprintable, Meta = (DisplayName = "YQZY HUD Layout", Category = "YQZY|HUD"))
class UYQZYHUDLayout : public UYQZYActivatableWidget
{
	GENERATED_BODY()

public:

	UYQZYHUDLayout(const FObjectInitializer& ObjectInitializer);

	void NativeOnInitialized() override;

protected:
	void HandleEscapeAction();

	UPROPERTY(EditDefaultsOnly)
	TSoftClassPtr<UCommonActivatableWidget> EscapeMenuClass;
};
