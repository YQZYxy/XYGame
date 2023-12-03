// Copyright Epic Games, Inc. All Rights Reserved.

#include "YQZYDebugCameraController.h"
#include "YQZYCheatManager.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(YQZYDebugCameraController)


AYQZYDebugCameraController::AYQZYDebugCameraController(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	// Use the same cheat class as YQZYPlayerController to allow toggling the debug camera through cheats.
	CheatClass = UYQZYCheatManager::StaticClass();
}

void AYQZYDebugCameraController::AddCheats(bool bForce)
{
	// Mirrors YQZYPlayerController's AddCheats() to avoid the player becoming stuck in the debug camera.
#if USING_CHEAT_MANAGER
	Super::AddCheats(true);
#else //#if USING_CHEAT_MANAGER
	Super::AddCheats(bForce);
#endif // #else //#if USING_CHEAT_MANAGER
}

