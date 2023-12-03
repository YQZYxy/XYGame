// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Character/YQZYCharacterMovementComponent.h"

#include "XYGameMovementComponent.generated.h"

class UObject;

UCLASS()
class UXYGameMovementComponent : public UYQZYCharacterMovementComponent
{
	GENERATED_BODY()

public:

	UXYGameMovementComponent(const FObjectInitializer& ObjectInitializer);

	//~UMovementComponent interface
	virtual float GetMaxSpeed() const override;
	//~End of UMovementComponent interface

};
