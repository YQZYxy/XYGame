// Copyright Epic Games, Inc. All Rights Reserved.

#include "YQZYPlayerController.h"
#include "CommonInputTypeEnum.h"
#include "Components/PrimitiveComponent.h"
#include "YQZYLog.h"
#include "YQZYCheatManager.h"
#include "YQZYPlayerState.h"
#include "Camera/YQZYPlayerCameraManager.h"
#include "UI/YQZYHUD.h"
#include "AbilitySystem/YQZYAbilitySystemComponent.h"
#include "EngineUtils.h"
#include "YQZYGameplayTags.h"
#include "GameFramework/Pawn.h"
#include "AbilitySystemGlobals.h"
#include "CommonInputSubsystem.h"
#include "YQZYLocalPlayer.h"
#include "Settings/YQZYSettingsShared.h"
#include "Development/YQZYDeveloperSettings.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(YQZYPlayerController)

namespace YQZY
{
	namespace Input
	{
		static int32 ShouldAlwaysPlayForceFeedback = 0;
		static FAutoConsoleVariableRef CVarShouldAlwaysPlayForceFeedback(TEXT("YQZYPC.ShouldAlwaysPlayForceFeedback"),
			ShouldAlwaysPlayForceFeedback,
			TEXT("Should force feedback effects be played, even if the last input device was not a gamepad?"));
	}
}

AYQZYPlayerController::AYQZYPlayerController(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	PlayerCameraManagerClass = AYQZYPlayerCameraManager::StaticClass();

#if USING_CHEAT_MANAGER
	CheatClass = UYQZYCheatManager::StaticClass();
#endif // #if USING_CHEAT_MANAGER
}

void AYQZYPlayerController::PreInitializeComponents()
{
	Super::PreInitializeComponents();
}

void AYQZYPlayerController::BeginPlay()
{
	Super::BeginPlay();
	SetActorHiddenInGame(false);
}

void AYQZYPlayerController::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}

void AYQZYPlayerController::ReceivedPlayer()
{
	Super::ReceivedPlayer();
}

void AYQZYPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	// If we are auto running then add some player input
	if (GetIsAutoRunning())
	{
		if (APawn* CurrentPawn = GetPawn())
		{
			const FRotator MovementRotation(0.0f, GetControlRotation().Yaw, 0.0f);
			const FVector MovementDirection = MovementRotation.RotateVector(FVector::ForwardVector);
			CurrentPawn->AddMovementInput(MovementDirection, 1.0f);	
		}
	}
}

AYQZYPlayerState* AYQZYPlayerController::GetYQZYPlayerState() const
{
	return CastChecked<AYQZYPlayerState>(PlayerState, ECastCheckedType::NullAllowed);
}

UYQZYAbilitySystemComponent* AYQZYPlayerController::GetYQZYAbilitySystemComponent() const
{
	const AYQZYPlayerState* YQZYPS = GetYQZYPlayerState();
	return (YQZYPS ? YQZYPS->GetYQZYAbilitySystemComponent() : nullptr);
}

AYQZYHUD* AYQZYPlayerController::GetYQZYHUD() const
{
	return CastChecked<AYQZYHUD>(GetHUD(), ECastCheckedType::NullAllowed);
}

void AYQZYPlayerController::OnPlayerStateChangedTeam(UObject* TeamAgent, int32 OldTeam, int32 NewTeam)
{
	ConditionalBroadcastTeamChanged(this, IntegerToGenericTeamId(OldTeam), IntegerToGenericTeamId(NewTeam));
}

void AYQZYPlayerController::OnPlayerStateChanged()
{
	// Empty, place for derived classes to implement without having to hook all the other events
}

void AYQZYPlayerController::BroadcastOnPlayerStateChanged()
{
	OnPlayerStateChanged();

	// Unbind from the old player state, if any
	FGenericTeamId OldTeamID = FGenericTeamId::NoTeam;
	if (LastSeenPlayerState != nullptr)
	{
		if (IYQZYTeamAgentInterface* PlayerStateTeamInterface = Cast<IYQZYTeamAgentInterface>(LastSeenPlayerState))
		{
			OldTeamID = PlayerStateTeamInterface->GetGenericTeamId();
			PlayerStateTeamInterface->GetTeamChangedDelegateChecked().RemoveAll(this);
		}
	}

	// Bind to the new player state, if any
	FGenericTeamId NewTeamID = FGenericTeamId::NoTeam;
	if (PlayerState != nullptr)
	{
		if (IYQZYTeamAgentInterface* PlayerStateTeamInterface = Cast<IYQZYTeamAgentInterface>(PlayerState))
		{
			NewTeamID = PlayerStateTeamInterface->GetGenericTeamId();
			PlayerStateTeamInterface->GetTeamChangedDelegateChecked().AddDynamic(this, &ThisClass::OnPlayerStateChangedTeam);
		}
	}

	// Broadcast the team change (if it really has)
	ConditionalBroadcastTeamChanged(this, OldTeamID, NewTeamID);

	LastSeenPlayerState = PlayerState;
}

void AYQZYPlayerController::InitPlayerState()
{
	Super::InitPlayerState();
	BroadcastOnPlayerStateChanged();
}

void AYQZYPlayerController::CleanupPlayerState()
{
	Super::CleanupPlayerState();
	BroadcastOnPlayerStateChanged();
}

void AYQZYPlayerController::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();
	BroadcastOnPlayerStateChanged();
}

void AYQZYPlayerController::SetPlayer(UPlayer* InPlayer)
{
	Super::SetPlayer(InPlayer);

	if (const UYQZYLocalPlayer* YQZYLocalPlayer = Cast<UYQZYLocalPlayer>(InPlayer))
	{
		UYQZYSettingsShared* UserSettings = YQZYLocalPlayer->GetSharedSettings();
		UserSettings->OnSettingChanged.AddUObject(this, &ThisClass::OnSettingsChanged);

		OnSettingsChanged(UserSettings);
	}
}

void AYQZYPlayerController::OnSettingsChanged(UYQZYSettingsShared* InSettings)
{
	bForceFeedbackEnabled = InSettings->GetForceFeedbackEnabled();
}

void AYQZYPlayerController::AddCheats(bool bForce)
{
#if USING_CHEAT_MANAGER
	Super::AddCheats(true);
#else //#if USING_CHEAT_MANAGER
	Super::AddCheats(bForce);
#endif // #else //#if USING_CHEAT_MANAGER
}

void AYQZYPlayerController::ServerCheat_Implementation(const FString& Msg)
{
#if USING_CHEAT_MANAGER
	if (CheatManager)
	{
		UE_LOG(YQZYLog, Warning, TEXT("ServerCheat: %s"), *Msg);
		ClientMessage(ConsoleCommand(Msg));
	}
#endif // #if USING_CHEAT_MANAGER
}

bool AYQZYPlayerController::ServerCheat_Validate(const FString& Msg)
{
	return true;
}

void AYQZYPlayerController::ServerCheatAll_Implementation(const FString& Msg)
{
#if USING_CHEAT_MANAGER
	if (CheatManager)
	{
		UE_LOG(YQZYLog, Warning, TEXT("ServerCheatAll: %s"), *Msg);
		for (TActorIterator<AYQZYPlayerController> It(GetWorld()); It; ++It)
		{
			AYQZYPlayerController* YQZYPC = (*It);
			if (YQZYPC)
			{
				YQZYPC->ClientMessage(YQZYPC->ConsoleCommand(Msg));
			}
		}
	}
#endif // #if USING_CHEAT_MANAGER
}

bool AYQZYPlayerController::ServerCheatAll_Validate(const FString& Msg)
{
	return true;
}

void AYQZYPlayerController::PreProcessInput(const float DeltaTime, const bool bGamePaused)
{
	Super::PreProcessInput(DeltaTime, bGamePaused);
}

void AYQZYPlayerController::PostProcessInput(const float DeltaTime, const bool bGamePaused)
{
	if (UYQZYAbilitySystemComponent* YQZYASC = GetYQZYAbilitySystemComponent())
	{
		YQZYASC->ProcessAbilityInput(DeltaTime, bGamePaused);
	}

	Super::PostProcessInput(DeltaTime, bGamePaused);
}

void AYQZYPlayerController::OnCameraPenetratingTarget()
{
	bHideViewTargetPawnNextFrame = true;
}

void AYQZYPlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

#if WITH_SERVER_CODE && WITH_EDITOR
	if (GIsEditor && (InPawn != nullptr) && (GetPawn() == InPawn))
	{
		for (const FYQZYCheatToRun& CheatRow : GetDefault<UYQZYDeveloperSettings>()->CheatsToRun)
		{
			if (CheatRow.Phase == ECheatExecutionTime::OnPlayerPawnPossession)
			{
				ConsoleCommand(CheatRow.Cheat, /*bWriteToLog=*/ true);
			}
		}
	}
#endif

	SetIsAutoRunning(false);
}

void AYQZYPlayerController::SetIsAutoRunning(const bool bEnabled)
{
	const bool bIsAutoRunning = GetIsAutoRunning();
	if (bEnabled != bIsAutoRunning)
	{
		if (!bEnabled)
		{
			OnEndAutoRun();
		}
		else
		{
			OnStartAutoRun();
		}
	}
}

bool AYQZYPlayerController::GetIsAutoRunning() const
{
	bool bIsAutoRunning = false;
	if (const UYQZYAbilitySystemComponent* YQZYASC = GetYQZYAbilitySystemComponent())
	{
		bIsAutoRunning = YQZYASC->GetTagCount(YQZYGameplayTags::Status_AutoRunning) > 0;
	}
	return bIsAutoRunning;
}

void AYQZYPlayerController::OnStartAutoRun()
{
	if (UYQZYAbilitySystemComponent* YQZYASC = GetYQZYAbilitySystemComponent())
	{
		YQZYASC->SetLooseGameplayTagCount(YQZYGameplayTags::Status_AutoRunning, 1);
		K2_OnStartAutoRun();
	}	
}

void AYQZYPlayerController::OnEndAutoRun()
{
	if (UYQZYAbilitySystemComponent* YQZYASC = GetYQZYAbilitySystemComponent())
	{
		YQZYASC->SetLooseGameplayTagCount(YQZYGameplayTags::Status_AutoRunning, 0);
		K2_OnEndAutoRun();
	}
}

void AYQZYPlayerController::UpdateForceFeedback(IInputInterface* InputInterface, const int32 ControllerId)
{
	if (bForceFeedbackEnabled)
	{
		if (const UCommonInputSubsystem* CommonInputSubsystem = UCommonInputSubsystem::Get(GetLocalPlayer()))
		{
			const ECommonInputType CurrentInputType = CommonInputSubsystem->GetCurrentInputType();
			if (YQZY::Input::ShouldAlwaysPlayForceFeedback || CurrentInputType == ECommonInputType::Gamepad || CurrentInputType == ECommonInputType::Touch)
			{
				InputInterface->SetForceFeedbackChannelValues(ControllerId, ForceFeedbackValues);
				return;
			}
		}
	}
	
	InputInterface->SetForceFeedbackChannelValues(ControllerId, FForceFeedbackValues());
}

void AYQZYPlayerController::UpdateHiddenComponents(const FVector& ViewLocation, TSet<FPrimitiveComponentId>& OutHiddenComponents)
{
	Super::UpdateHiddenComponents(ViewLocation, OutHiddenComponents);

	if (bHideViewTargetPawnNextFrame)
	{
		AActor* const ViewTargetPawn = PlayerCameraManager ? Cast<AActor>(PlayerCameraManager->GetViewTarget()) : nullptr;
		if (ViewTargetPawn)
		{
			// internal helper func to hide all the components
			auto AddToHiddenComponents = [&OutHiddenComponents](const TInlineComponentArray<UPrimitiveComponent*>& InComponents)
			{
				// add every component and all attached children
				for (UPrimitiveComponent* Comp : InComponents)
				{
					if (Comp->IsRegistered())
					{
						OutHiddenComponents.Add(Comp->ComponentId);

						for (USceneComponent* AttachedChild : Comp->GetAttachChildren())
						{
							static FName NAME_NoParentAutoHide(TEXT("NoParentAutoHide"));
							UPrimitiveComponent* AttachChildPC = Cast<UPrimitiveComponent>(AttachedChild);
							if (AttachChildPC && AttachChildPC->IsRegistered() && !AttachChildPC->ComponentTags.Contains(NAME_NoParentAutoHide))
							{
								OutHiddenComponents.Add(AttachChildPC->ComponentId);
							}
						}
					}
				}
			};

			//TODO Solve with an interface.  Gather hidden components or something.
			//TODO Hiding isn't awesome, sometimes you want the effect of a fade out over a proximity, needs to bubble up to designers.

			// hide pawn's components
			TInlineComponentArray<UPrimitiveComponent*> PawnComponents;
			ViewTargetPawn->GetComponents(PawnComponents);
			AddToHiddenComponents(PawnComponents);

			//// hide weapon too
			//if (ViewTargetPawn->CurrentWeapon)
			//{
			//	TInlineComponentArray<UPrimitiveComponent*> WeaponComponents;
			//	ViewTargetPawn->CurrentWeapon->GetComponents(WeaponComponents);
			//	AddToHiddenComponents(WeaponComponents);
			//}
		}

		// we consumed it, reset for next frame
		bHideViewTargetPawnNextFrame = false;
	}
}

void AYQZYPlayerController::SetGenericTeamId(const FGenericTeamId& NewTeamID)
{
	UE_LOG(YQZYLog, Error, TEXT("You can't set the team ID on a player controller (%s); it's driven by the associated player state"), *GetPathNameSafe(this));
}

FGenericTeamId AYQZYPlayerController::GetGenericTeamId() const
{
	if (const IYQZYTeamAgentInterface* PSWithTeamInterface = Cast<IYQZYTeamAgentInterface>(PlayerState))
	{
		return PSWithTeamInterface->GetGenericTeamId();
	}
	return FGenericTeamId::NoTeam;
}

FOnYQZYTeamIndexChangedDelegate* AYQZYPlayerController::GetOnTeamIndexChangedDelegate()
{
	return &OnTeamChangedDelegate;
}

void AYQZYPlayerController::OnUnPossess()
{
	// Make sure the pawn that is being unpossessed doesn't remain our ASC's avatar actor
	if (APawn* PawnBeingUnpossessed = GetPawn())
	{
		if (UAbilitySystemComponent* ASC = UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(PlayerState))
		{
			if (ASC->GetAvatarActor() == PawnBeingUnpossessed)
			{
				ASC->SetAvatarActor(nullptr);
			}
		}
	}

	Super::OnUnPossess();
}

//////////////////////////////////////////////////////////////////////
// AYQZYReplayPlayerController

void AYQZYReplayPlayerController::SetPlayer(UPlayer* InPlayer)
{
	Super::SetPlayer(InPlayer);
}

