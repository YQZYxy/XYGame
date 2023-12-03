// Copyright Epic Games, Inc. All Rights Reserved.

#include "YQZYControllerDisconnectedScreen.h"

#include "Components/HorizontalBox.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(YQZYControllerDisconnectedScreen)

void UYQZYControllerDisconnectedScreen::NativeOnActivated()
{
	Super::NativeOnActivated();

	HBox_SwitchUser->SetVisibility(ESlateVisibility::Collapsed);

//#if PLATFORM_HAS_STRICT_CONTROLLER_PAIRING
//	if (FPlatformApplicationMisc::GetControllerIdForUnpairedControllers() != INDEX_NONE)
//	{
//		HBox_SwitchUser->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
//	}
//#endif
}


