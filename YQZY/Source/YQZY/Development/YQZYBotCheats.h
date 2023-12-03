// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "GameFramework/CheatManager.h"

#include "YQZYBotCheats.generated.h"

class UYQZYBotCreationComponent;
class UObject;
struct FFrame;

/** Cheats related to bots */
UCLASS(NotBlueprintable)
class UYQZYBotCheats final : public UCheatManagerExtension
{
	GENERATED_BODY()

public:
	UYQZYBotCheats();

	// Adds a bot player
	UFUNCTION(Exec, BlueprintAuthorityOnly)
	void AddPlayerBot();

	// Removes a random bot player
	UFUNCTION(Exec, BlueprintAuthorityOnly)
	void RemovePlayerBot();

private:
	UYQZYBotCreationComponent* GetBotComponent() const;
};
