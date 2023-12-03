// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "NativeGameplayTags.h"

namespace YQZYGameplayTags
{
	YQZY_API	FGameplayTag FindTagByString(const FString& TagString, bool bMatchPartialString = false);

	// Declare all of the custom native tags that YQZY will use
	YQZY_API	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Ability_ActivateFail_IsDead);
	YQZY_API	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Ability_ActivateFail_Cooldown);
	YQZY_API	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Ability_ActivateFail_Cost);
	YQZY_API	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Ability_ActivateFail_TagsBlocked);
	YQZY_API	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Ability_ActivateFail_TagsMissing);
	YQZY_API	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Ability_ActivateFail_Networking);
	YQZY_API	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Ability_ActivateFail_ActivationGroup);

	YQZY_API	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Ability_Behavior_SurvivesDeath);

	YQZY_API	UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_Move);
	YQZY_API	UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_Look_Mouse);
	YQZY_API	UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_Look_Stick);
	YQZY_API	UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_Crouch);
	YQZY_API	UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_AutoRun);

	YQZY_API	UE_DECLARE_GAMEPLAY_TAG_EXTERN(InitState_Spawned);
	YQZY_API	UE_DECLARE_GAMEPLAY_TAG_EXTERN(InitState_DataAvailable);
	YQZY_API	UE_DECLARE_GAMEPLAY_TAG_EXTERN(InitState_DataInitialized);
	YQZY_API	UE_DECLARE_GAMEPLAY_TAG_EXTERN(InitState_GameplayReady);

	YQZY_API	UE_DECLARE_GAMEPLAY_TAG_EXTERN(GameplayEvent_Death);
	YQZY_API	UE_DECLARE_GAMEPLAY_TAG_EXTERN(GameplayEvent_Reset);
	YQZY_API	UE_DECLARE_GAMEPLAY_TAG_EXTERN(GameplayEvent_RequestReset);

	YQZY_API	UE_DECLARE_GAMEPLAY_TAG_EXTERN(SetByCaller_Damage);
	YQZY_API	UE_DECLARE_GAMEPLAY_TAG_EXTERN(SetByCaller_Heal);

	YQZY_API	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Cheat_GodMode);
	YQZY_API	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Cheat_UnlimitedHealth);

	YQZY_API	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Status_Crouching);
	YQZY_API	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Status_AutoRunning);
	YQZY_API	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Status_Death);
	YQZY_API	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Status_Death_Dying);
	YQZY_API	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Status_Death_Dead);

	// These are mappings from MovementMode enums to GameplayTags associated with those enums (below)
	YQZY_API	extern const TMap<uint8, FGameplayTag> MovementModeTagMap;
	YQZY_API	extern const TMap<uint8, FGameplayTag> CustomMovementModeTagMap;

	YQZY_API	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Movement_Mode_Walking);
	YQZY_API	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Movement_Mode_NavWalking);
	YQZY_API	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Movement_Mode_Falling);
	YQZY_API	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Movement_Mode_Swimming);
	YQZY_API	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Movement_Mode_Flying);

	YQZY_API	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Movement_Mode_Custom);
};
