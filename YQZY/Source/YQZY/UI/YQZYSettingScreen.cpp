// Copyright Epic Games, Inc. All Rights Reserved.

#include "YQZYSettingScreen.h"

#include "Input/CommonUIInputTypes.h"
#include "Player/YQZYLocalPlayer.h"
#include "Settings/YQZYGameSettingRegistry.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(YQZYSettingScreen)

class UGameSettingRegistry;

void UYQZYSettingScreen::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	BackHandle = RegisterUIActionBinding(FBindUIActionArgs(BackInputActionData, true, FSimpleDelegate::CreateUObject(this, &ThisClass::HandleBackAction)));
	ApplyHandle = RegisterUIActionBinding(FBindUIActionArgs(ApplyInputActionData, true, FSimpleDelegate::CreateUObject(this, &ThisClass::HandleApplyAction)));
	CancelChangesHandle = RegisterUIActionBinding(FBindUIActionArgs(CancelChangesInputActionData, true, FSimpleDelegate::CreateUObject(this, &ThisClass::HandleCancelChangesAction)));
}

UGameSettingRegistry* UYQZYSettingScreen::CreateRegistry()
{
	UYQZYGameSettingRegistry* NewRegistry = NewObject<UYQZYGameSettingRegistry>();

	if (UYQZYLocalPlayer* LocalPlayer = CastChecked<UYQZYLocalPlayer>(GetOwningLocalPlayer()))
	{
		NewRegistry->Initialize(LocalPlayer);
	}

	return NewRegistry;
}

void UYQZYSettingScreen::HandleBackAction()
{
	if (AttemptToPopNavigation())
	{
		return;
	}

	ApplyChanges();

	DeactivateWidget();
}

void UYQZYSettingScreen::HandleApplyAction()
{
	ApplyChanges();
}

void UYQZYSettingScreen::HandleCancelChangesAction()
{
	CancelChanges();
}

void UYQZYSettingScreen::OnSettingsDirtyStateChanged_Implementation(bool bSettingsDirty)
{
	if (bSettingsDirty)
	{
		if (!GetActionBindings().Contains(ApplyHandle))
		{
			AddActionBinding(ApplyHandle);
		}
		if (!GetActionBindings().Contains(CancelChangesHandle))
		{
			AddActionBinding(CancelChangesHandle);
		}
	}
	else
	{
		RemoveActionBinding(ApplyHandle);
		RemoveActionBinding(CancelChangesHandle);
	}
}
