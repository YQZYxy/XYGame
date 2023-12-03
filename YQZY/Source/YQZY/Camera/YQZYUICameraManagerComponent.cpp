// Copyright Epic Games, Inc. All Rights Reserved.

#include "YQZYUICameraManagerComponent.h"

#include "GameFramework/HUD.h"
#include "GameFramework/PlayerController.h"
#include "YQZYPlayerCameraManager.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(YQZYUICameraManagerComponent)

class AActor;
class FDebugDisplayInfo;

UYQZYUICameraManagerComponent* UYQZYUICameraManagerComponent::GetComponent(APlayerController* PC)
{
	if (PC != nullptr)
	{
		if (AYQZYPlayerCameraManager* PCCamera = Cast<AYQZYPlayerCameraManager>(PC->PlayerCameraManager))
		{
			return PCCamera->GetUICameraComponent();
		}
	}

	return nullptr;
}

UYQZYUICameraManagerComponent::UYQZYUICameraManagerComponent()
{
	bWantsInitializeComponent = true;

	if (!HasAnyFlags(RF_ClassDefaultObject))
	{
		// Register "showdebug" hook.
		if (!IsRunningDedicatedServer())
		{
			AHUD::OnShowDebugInfo.AddUObject(this, &ThisClass::OnShowDebugInfo);
		}
	}
}

void UYQZYUICameraManagerComponent::InitializeComponent()
{
	Super::InitializeComponent();
}

void UYQZYUICameraManagerComponent::SetViewTarget(AActor* InViewTarget, FViewTargetTransitionParams TransitionParams)
{
	TGuardValue<bool> UpdatingViewTargetGuard(bUpdatingViewTarget, true);

	ViewTarget = InViewTarget;
	CastChecked<AYQZYPlayerCameraManager>(GetOwner())->SetViewTarget(ViewTarget, TransitionParams);
}

bool UYQZYUICameraManagerComponent::NeedsToUpdateViewTarget() const
{
	return false;
}

void UYQZYUICameraManagerComponent::UpdateViewTarget(struct FTViewTarget& OutVT, float DeltaTime)
{
}

void UYQZYUICameraManagerComponent::OnShowDebugInfo(AHUD* HUD, UCanvas* Canvas, const FDebugDisplayInfo& DisplayInfo, float& YL, float& YPos)
{
}
