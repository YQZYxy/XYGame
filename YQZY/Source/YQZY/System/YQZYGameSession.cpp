// Copyright Epic Games, Inc. All Rights Reserved.

#include "YQZYGameSession.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(YQZYGameSession)


AYQZYGameSession::AYQZYGameSession(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

bool AYQZYGameSession::ProcessAutoLogin()
{
	// This is actually handled in YQZYGameMode::TryDedicatedServerLogin
	return true;
}

void AYQZYGameSession::HandleMatchHasStarted()
{
	Super::HandleMatchHasStarted();
}

void AYQZYGameSession::HandleMatchHasEnded()
{
	Super::HandleMatchHasEnded();
}

