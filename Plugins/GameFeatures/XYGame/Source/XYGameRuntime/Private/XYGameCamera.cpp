// Copyright Epic Games, Inc. All Rights Reserved.

#include "XYGameCamera.h"


#include UE_INLINE_GENERATED_CPP_BY_NAME(XYGameCamera)

UXYGameCamera::UXYGameCamera()
{
	ArenaWidth = 1000.0f;
	ArenaHeight = 1000.0f;
}

void UXYGameCamera::UpdateView(float DeltaTime)
{
	FBox ArenaBounds(FVector(-ArenaWidth, -ArenaHeight, 0.0f), FVector(ArenaWidth, ArenaHeight, 100.0f));

	const double BoundsMaxComponent = ArenaBounds.GetSize().GetMax();

	const double CameraLoftDistance = BoundsSizeToDistance.GetRichCurveConst()->Eval(BoundsMaxComponent);
	
	FVector PivotLocation = ArenaBounds.GetCenter() - DefaultPivotRotation.Vector() * CameraLoftDistance;
	
	FRotator PivotRotation = DefaultPivotRotation;

	View.Location = PivotLocation;
	View.Rotation = PivotRotation;
	View.ControlRotation = View.Rotation;
	View.FieldOfView = FieldOfView;
}

