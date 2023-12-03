// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Engine/DebugCameraController.h"

#include "YQZYDebugCameraController.generated.h"

class UObject;


/**
 * AYQZYDebugCameraController
 *
 *	Used for controlling the debug camera when it is enabled via the cheat manager.
 */
UCLASS()
class AYQZYDebugCameraController : public ADebugCameraController
{
	GENERATED_BODY()

public:

	AYQZYDebugCameraController(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

protected:

	virtual void AddCheats(bool bForce) override;
};
