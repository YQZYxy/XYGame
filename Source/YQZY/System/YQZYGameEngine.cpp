// Copyright Epic Games, Inc. All Rights Reserved.

#include "YQZYGameEngine.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(YQZYGameEngine)

class IEngineLoop;


UYQZYGameEngine::UYQZYGameEngine(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

void UYQZYGameEngine::Init(IEngineLoop* InEngineLoop)
{
	Super::Init(InEngineLoop);
}

