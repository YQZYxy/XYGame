// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Engine/GameEngine.h"

#include "YQZYGameEngine.generated.h"

class IEngineLoop;
class UObject;


UCLASS()
class UYQZYGameEngine : public UGameEngine
{
	GENERATED_BODY()

public:

	UYQZYGameEngine(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

protected:

	virtual void Init(IEngineLoop* InEngineLoop) override;
};
