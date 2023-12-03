// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "GameFramework/GameSession.h"

#include "YQZYGameSession.generated.h"

class UObject;


UCLASS(Config = Game)
class AYQZYGameSession : public AGameSession
{
	GENERATED_BODY()

public:

	AYQZYGameSession(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

protected:

	/** Override to disable the default behavior */
	virtual bool ProcessAutoLogin() override;

	virtual void HandleMatchHasStarted() override;
	virtual void HandleMatchHasEnded() override;
};
