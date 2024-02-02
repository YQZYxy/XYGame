// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "PlayGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class PLAY_API APlayGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

		virtual void StartPlay() override;

};
