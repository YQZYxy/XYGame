// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Camera/YQZYCameraMode.h"
#include "Curves/CurveFloat.h"

#include "XYGameCamera.generated.h"

class UObject;


UCLASS(Abstract, Blueprintable)
class UXYGameCamera : public UYQZYCameraMode
{
	GENERATED_BODY()

public:

	UXYGameCamera();

protected:


	virtual void UpdateView(float DeltaTime) override;

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Third Person")
	float ArenaWidth;

	UPROPERTY(EditDefaultsOnly, Category = "Third Person")
	float ArenaHeight;

	UPROPERTY(EditDefaultsOnly, Category = "Third Person")
	FRotator DefaultPivotRotation;

	UPROPERTY(EditDefaultsOnly, Category = "Third Person")
	FRuntimeFloatCurve BoundsSizeToDistance;
};
