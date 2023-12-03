// Copyright Epic Games, Inc. All Rights Reserved.

#include "YQZYPlayerCameraManager.h"

#include "Async/TaskGraphInterfaces.h"
#include "Engine/Canvas.h"
#include "Engine/Engine.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/PlayerController.h"
#include "YQZYCameraComponent.h"
#include "YQZYUICameraManagerComponent.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(YQZYPlayerCameraManager)

class FDebugDisplayInfo;

static FName UICameraComponentName(TEXT("UICamera"));

AYQZYPlayerCameraManager::AYQZYPlayerCameraManager(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	DefaultFOV = YQZY_CAMERA_DEFAULT_FOV;
	ViewPitchMin = YQZY_CAMERA_DEFAULT_PITCH_MIN;
	ViewPitchMax = YQZY_CAMERA_DEFAULT_PITCH_MAX;

	UICamera = CreateDefaultSubobject<UYQZYUICameraManagerComponent>(UICameraComponentName);
}

UYQZYUICameraManagerComponent* AYQZYPlayerCameraManager::GetUICameraComponent() const
{
	return UICamera;
}

void AYQZYPlayerCameraManager::UpdateViewTarget(FTViewTarget& OutVT, float DeltaTime)
{
	// If the UI Camera is looking at something, let it have priority.
	if (UICamera->NeedsToUpdateViewTarget())
	{
		Super::UpdateViewTarget(OutVT, DeltaTime);
		UICamera->UpdateViewTarget(OutVT, DeltaTime);
		return;
	}

	Super::UpdateViewTarget(OutVT, DeltaTime);
}

void AYQZYPlayerCameraManager::DisplayDebug(UCanvas* Canvas, const FDebugDisplayInfo& DebugDisplay, float& YL, float& YPos)
{
	check(Canvas);

	FDisplayDebugManager& DisplayDebugManager = Canvas->DisplayDebugManager;

	DisplayDebugManager.SetFont(GEngine->GetSmallFont());
	DisplayDebugManager.SetDrawColor(FColor::Yellow);
	DisplayDebugManager.DrawString(FString::Printf(TEXT("YQZYPlayerCameraManager: %s"), *GetNameSafe(this)));

	Super::DisplayDebug(Canvas, DebugDisplay, YL, YPos);

	const APawn* Pawn = (PCOwner ? PCOwner->GetPawn() : nullptr);

	if (const UYQZYCameraComponent* CameraComponent = UYQZYCameraComponent::FindCameraComponent(Pawn))
	{
		CameraComponent->DrawDebug(Canvas);
	}
}

