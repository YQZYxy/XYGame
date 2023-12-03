// Copyright Epic Games, Inc. All Rights Reserved.

#include "YQZYHeroComponent.h"
#include "Components/GameFrameworkComponentDelegates.h"
#include "Logging/MessageLog.h"
#include "Input/YQZYMappableConfigPair.h"
#include "YQZYLog.h"
#include "EnhancedInputSubsystems.h"
#include "Player/YQZYPlayerController.h"
#include "Player/YQZYPlayerState.h"
#include "Player/YQZYLocalPlayer.h"
#include "Character/YQZYPawnExtensionComponent.h"
#include "Character/YQZYPawnData.h"
#include "Character/YQZYCharacter.h"
#include "AbilitySystem/YQZYAbilitySystemComponent.h"
#include "Input/YQZYInputConfig.h"
#include "Input/YQZYInputComponent.h"
#include "Camera/YQZYCameraComponent.h"
#include "YQZYGameplayTags.h"
#include "Components/GameFrameworkComponentManager.h"
#include "PlayerMappableInputConfig.h"
#include "Camera/YQZYCameraMode.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(YQZYHeroComponent)

#if WITH_EDITOR
#include "Misc/UObjectToken.h"
#endif	// WITH_EDITOR

namespace YQZYHero
{
	static const float LookYawRate = 300.0f;
	static const float LookPitchRate = 165.0f;
};

const FName UYQZYHeroComponent::NAME_BindInputsNow("BindInputsNow");
const FName UYQZYHeroComponent::NAME_ActorFeatureName("Hero");

UYQZYHeroComponent::UYQZYHeroComponent(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	AbilityCameraMode = nullptr;
	bReadyToBindInputs = false;
}

void UYQZYHeroComponent::OnRegister()
{
	Super::OnRegister();

	if (!GetPawn<APawn>())
	{
		UE_LOG(YQZYLog, Error, TEXT("[UYQZYHeroComponent::OnRegister] This component has been added to a blueprint whose base class is not a Pawn. To use this component, it MUST be placed on a Pawn Blueprint."));

#if WITH_EDITOR
		if (GIsEditor)
		{
			static const FText Message = NSLOCTEXT("YQZYHeroComponent", "NotOnPawnError", "has been added to a blueprint whose base class is not a Pawn. To use this component, it MUST be placed on a Pawn Blueprint. This will cause a crash if you PIE!");
			static const FName HeroMessageLogName = TEXT("YQZYHeroComponent");
			
			FMessageLog(HeroMessageLogName).Error()
				->AddToken(FUObjectToken::Create(this, FText::FromString(GetNameSafe(this))))
				->AddToken(FTextToken::Create(Message));
				
			FMessageLog(HeroMessageLogName).Open();
		}
#endif
	}
	else
	{
		// Register with the init state system early, this will only work if this is a game world
		RegisterInitStateFeature();
	}
}

bool UYQZYHeroComponent::CanChangeInitState(UGameFrameworkComponentManager* Manager, FGameplayTag CurrentState, FGameplayTag DesiredState) const
{
	check(Manager);

	APawn* Pawn = GetPawn<APawn>();

	if (!CurrentState.IsValid() && DesiredState == YQZYGameplayTags::InitState_Spawned)
	{
		// As long as we have a real pawn, let us transition
		if (Pawn)
		{
			return true;
		}
	}
	else if (CurrentState == YQZYGameplayTags::InitState_Spawned && DesiredState == YQZYGameplayTags::InitState_DataAvailable)
	{
		// The player state is required.
		if (!GetPlayerState<AYQZYPlayerState>())
		{
			return false;
		}

		// If we're authority or autonomous, we need to wait for a controller with registered ownership of the player state.
		if (Pawn->GetLocalRole() != ROLE_SimulatedProxy)
		{
			AController* Controller = GetController<AController>();

			const bool bHasControllerPairedWithPS = (Controller != nullptr) && \
				(Controller->PlayerState != nullptr) && \
				(Controller->PlayerState->GetOwner() == Controller);

			if (!bHasControllerPairedWithPS)
			{
				return false;
			}
		}

		const bool bIsLocallyControlled = Pawn->IsLocallyControlled();
		const bool bIsBot = Pawn->IsBotControlled();

		if (bIsLocallyControlled && !bIsBot)
		{
			AYQZYPlayerController* YQZYPC = GetController<AYQZYPlayerController>();

			// The input component and local player is required when locally controlled.
			if (!Pawn->InputComponent || !YQZYPC || !YQZYPC->GetLocalPlayer())
			{
				return false;
			}
		}

		return true;
	}
	else if (CurrentState == YQZYGameplayTags::InitState_DataAvailable && DesiredState == YQZYGameplayTags::InitState_DataInitialized)
	{
		// Wait for player state and extension component
		AYQZYPlayerState* YQZYPS = GetPlayerState<AYQZYPlayerState>();

		return YQZYPS && Manager->HasFeatureReachedInitState(Pawn, UYQZYPawnExtensionComponent::NAME_ActorFeatureName, YQZYGameplayTags::InitState_DataInitialized);
	}
	else if (CurrentState == YQZYGameplayTags::InitState_DataInitialized && DesiredState == YQZYGameplayTags::InitState_GameplayReady)
	{
		// TODO add ability initialization checks?
		return true;
	}

	return false;
}

void UYQZYHeroComponent::HandleChangeInitState(UGameFrameworkComponentManager* Manager, FGameplayTag CurrentState, FGameplayTag DesiredState)
{
	if (CurrentState == YQZYGameplayTags::InitState_DataAvailable && DesiredState == YQZYGameplayTags::InitState_DataInitialized)
	{
		APawn* Pawn = GetPawn<APawn>();
		AYQZYPlayerState* YQZYPS = GetPlayerState<AYQZYPlayerState>();
		if (!ensure(Pawn && YQZYPS))
		{
			return;
		}

		const bool bIsLocallyControlled = Pawn->IsLocallyControlled();
		const UYQZYPawnData* PawnData = nullptr;

		if (UYQZYPawnExtensionComponent* PawnExtComp = UYQZYPawnExtensionComponent::FindPawnExtensionComponent(Pawn))
		{
			PawnData = PawnExtComp->GetPawnData<UYQZYPawnData>();

			// The player state holds the persistent data for this player (state that persists across deaths and multiple pawns).
			// The ability system component and attribute sets live on the player state.
			PawnExtComp->InitializeAbilitySystem(YQZYPS->GetYQZYAbilitySystemComponent(), YQZYPS);
		}

		if (AYQZYPlayerController* YQZYPC = GetController<AYQZYPlayerController>())
		{
			if (Pawn->InputComponent != nullptr)
			{
				InitializePlayerInput(Pawn->InputComponent);
			}
		}

		if (bIsLocallyControlled && PawnData)
		{
			if (UYQZYCameraComponent* CameraComponent = UYQZYCameraComponent::FindCameraComponent(Pawn))
			{
				CameraComponent->DetermineCameraModeDelegate.BindUObject(this, &ThisClass::DetermineCameraMode);
			}
		}
	}
}

void UYQZYHeroComponent::OnActorInitStateChanged(const FActorInitStateChangedParams& Params)
{
	if (Params.FeatureName == UYQZYPawnExtensionComponent::NAME_ActorFeatureName)
	{
		if (Params.FeatureState == YQZYGameplayTags::InitState_DataInitialized)
		{
			// If the extension component says all all other components are initialized, try to progress to next state
			CheckDefaultInitialization();
		}
	}
}

void UYQZYHeroComponent::CheckDefaultInitialization()
{
	static const TArray<FGameplayTag> StateChain = { YQZYGameplayTags::InitState_Spawned, YQZYGameplayTags::InitState_DataAvailable, YQZYGameplayTags::InitState_DataInitialized, YQZYGameplayTags::InitState_GameplayReady };

	// This will try to progress from spawned (which is only set in BeginPlay) through the data initialization stages until it gets to gameplay ready
	ContinueInitStateChain(StateChain);
}

void UYQZYHeroComponent::BeginPlay()
{
	Super::BeginPlay();

	// Listen for when the pawn extension component changes init state
	BindOnActorInitStateChanged(UYQZYPawnExtensionComponent::NAME_ActorFeatureName, FGameplayTag(), false);

	// Notifies that we are done spawning, then try the rest of initialization
	ensure(TryToChangeInitState(YQZYGameplayTags::InitState_Spawned));
	CheckDefaultInitialization();
}

void UYQZYHeroComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	UnregisterInitStateFeature();

	Super::EndPlay(EndPlayReason);
}

void UYQZYHeroComponent::InitializePlayerInput(UInputComponent* PlayerInputComponent)
{
	check(PlayerInputComponent);

	const APawn* Pawn = GetPawn<APawn>();
	if (!Pawn)
	{
		return;
	}

	const APlayerController* PC = GetController<APlayerController>();
	check(PC);

	const UYQZYLocalPlayer* LP = Cast<UYQZYLocalPlayer>(PC->GetLocalPlayer());
	check(LP);

	UEnhancedInputLocalPlayerSubsystem* Subsystem = LP->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();
	check(Subsystem);

	Subsystem->ClearAllMappings();

	if (const UYQZYPawnExtensionComponent* PawnExtComp = UYQZYPawnExtensionComponent::FindPawnExtensionComponent(Pawn))
	{
		if (const UYQZYPawnData* PawnData = PawnExtComp->GetPawnData<UYQZYPawnData>())
		{
			if (const UYQZYInputConfig* InputConfig = PawnData->InputConfig)
			{
				// Register any default input configs with the settings so that they will be applied to the player during AddInputMappings
				for (const FMappableConfigPair& Pair : DefaultInputConfigs)
				{
					if (Pair.bShouldActivateAutomatically && Pair.CanBeActivated())
					{
						FModifyContextOptions Options = {};
						Options.bIgnoreAllPressedKeysUntilRelease = false;
						// Actually add the config to the local player							
						Subsystem->AddPlayerMappableConfig(Pair.Config.LoadSynchronous(), Options);	
					}
				}

				// The YQZY Input Component has some additional functions to map Gameplay Tags to an Input Action.
				// If you want this functionality but still want to change your input component class, make it a subclass
				// of the UYQZYInputComponent or modify this component accordingly.
				UYQZYInputComponent* YQZYIC = Cast<UYQZYInputComponent>(PlayerInputComponent);
				if (ensureMsgf(YQZYIC, TEXT("Unexpected Input Component class! The Gameplay Abilities will not be bound to their inputs. Change the input component to UYQZYInputComponent or a subclass of it.")))
				{
					// Add the key mappings that may have been set by the player
					YQZYIC->AddInputMappings(InputConfig, Subsystem);

					// This is where we actually bind and input action to a gameplay tag, which means that Gameplay Ability Blueprints will
					// be triggered directly by these input actions Triggered events. 
					TArray<uint32> BindHandles;
					YQZYIC->BindAbilityActions(InputConfig, this, &ThisClass::Input_AbilityInputTagPressed, &ThisClass::Input_AbilityInputTagReleased, /*out*/ BindHandles);

					YQZYIC->BindNativeAction(InputConfig, YQZYGameplayTags::InputTag_Move, ETriggerEvent::Triggered, this, &ThisClass::Input_Move, /*bLogIfNotFound=*/ false);
					YQZYIC->BindNativeAction(InputConfig, YQZYGameplayTags::InputTag_Look_Mouse, ETriggerEvent::Triggered, this, &ThisClass::Input_LookMouse, /*bLogIfNotFound=*/ false);
					YQZYIC->BindNativeAction(InputConfig, YQZYGameplayTags::InputTag_Look_Stick, ETriggerEvent::Triggered, this, &ThisClass::Input_LookStick, /*bLogIfNotFound=*/ false);
					YQZYIC->BindNativeAction(InputConfig, YQZYGameplayTags::InputTag_Crouch, ETriggerEvent::Triggered, this, &ThisClass::Input_Crouch, /*bLogIfNotFound=*/ false);
					YQZYIC->BindNativeAction(InputConfig, YQZYGameplayTags::InputTag_AutoRun, ETriggerEvent::Triggered, this, &ThisClass::Input_AutoRun, /*bLogIfNotFound=*/ false);
				}
			}
		}
	}

	if (ensure(!bReadyToBindInputs))
	{
		bReadyToBindInputs = true;
	}
 
	UGameFrameworkComponentManager::SendGameFrameworkComponentExtensionEvent(const_cast<APlayerController*>(PC), NAME_BindInputsNow);
	UGameFrameworkComponentManager::SendGameFrameworkComponentExtensionEvent(const_cast<APawn*>(Pawn), NAME_BindInputsNow);
}

void UYQZYHeroComponent::AddAdditionalInputConfig(const UYQZYInputConfig* InputConfig)
{
	TArray<uint32> BindHandles;

	const APawn* Pawn = GetPawn<APawn>();
	if (!Pawn)
	{
		return;
	}
	
	const APlayerController* PC = GetController<APlayerController>();
	check(PC);

	const ULocalPlayer* LP = PC->GetLocalPlayer();
	check(LP);

	UEnhancedInputLocalPlayerSubsystem* Subsystem = LP->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();
	check(Subsystem);

	if (const UYQZYPawnExtensionComponent* PawnExtComp = UYQZYPawnExtensionComponent::FindPawnExtensionComponent(Pawn))
	{
		UYQZYInputComponent* YQZYIC = Pawn->FindComponentByClass<UYQZYInputComponent>();
		if (ensureMsgf(YQZYIC, TEXT("Unexpected Input Component class! The Gameplay Abilities will not be bound to their inputs. Change the input component to UYQZYInputComponent or a subclass of it.")))
		{
			YQZYIC->BindAbilityActions(InputConfig, this, &ThisClass::Input_AbilityInputTagPressed, &ThisClass::Input_AbilityInputTagReleased, /*out*/ BindHandles);
		}
	}
}

void UYQZYHeroComponent::RemoveAdditionalInputConfig(const UYQZYInputConfig* InputConfig)
{
	//@TODO: Implement me!
}

bool UYQZYHeroComponent::IsReadyToBindInputs() const
{
	return bReadyToBindInputs;
}

void UYQZYHeroComponent::Input_AbilityInputTagPressed(FGameplayTag InputTag)
{
	if (const APawn* Pawn = GetPawn<APawn>())
	{
		if (const UYQZYPawnExtensionComponent* PawnExtComp = UYQZYPawnExtensionComponent::FindPawnExtensionComponent(Pawn))
		{
			if (UYQZYAbilitySystemComponent* YQZYASC = PawnExtComp->GetYQZYAbilitySystemComponent())
			{
				YQZYASC->AbilityInputTagPressed(InputTag);
			}
		}	
	}
}

void UYQZYHeroComponent::Input_AbilityInputTagReleased(FGameplayTag InputTag)
{
	const APawn* Pawn = GetPawn<APawn>();
	if (!Pawn)
	{
		return;
	}

	if (const UYQZYPawnExtensionComponent* PawnExtComp = UYQZYPawnExtensionComponent::FindPawnExtensionComponent(Pawn))
	{
		if (UYQZYAbilitySystemComponent* YQZYASC = PawnExtComp->GetYQZYAbilitySystemComponent())
		{
			YQZYASC->AbilityInputTagReleased(InputTag);
		}
	}
}

void UYQZYHeroComponent::Input_Move(const FInputActionValue& InputActionValue)
{
	APawn* Pawn = GetPawn<APawn>();
	AController* Controller = Pawn ? Pawn->GetController() : nullptr;

	// If the player has attempted to move again then cancel auto running
	if (AYQZYPlayerController* YQZYController = Cast<AYQZYPlayerController>(Controller))
	{
		YQZYController->SetIsAutoRunning(false);
	}
	
	if (Controller)
	{
		const FVector2D Value = InputActionValue.Get<FVector2D>();
		const FRotator MovementRotation(0.0f, Controller->GetControlRotation().Yaw, 0.0f);

		if (Value.X != 0.0f)
		{
			const FVector MovementDirection = MovementRotation.RotateVector(FVector::RightVector);
			Pawn->AddMovementInput(MovementDirection, Value.X);
		}

		if (Value.Y != 0.0f)
		{
			const FVector MovementDirection = MovementRotation.RotateVector(FVector::ForwardVector);
			Pawn->AddMovementInput(MovementDirection, Value.Y);
		}
	}
}

void UYQZYHeroComponent::Input_LookMouse(const FInputActionValue& InputActionValue)
{
	APawn* Pawn = GetPawn<APawn>();

	if (!Pawn)
	{
		return;
	}
	
	const FVector2D Value = InputActionValue.Get<FVector2D>();

	if (Value.X != 0.0f)
	{
		Pawn->AddControllerYawInput(Value.X);
	}

	if (Value.Y != 0.0f)
	{
		Pawn->AddControllerPitchInput(Value.Y);
	}
}

void UYQZYHeroComponent::Input_LookStick(const FInputActionValue& InputActionValue)
{
	APawn* Pawn = GetPawn<APawn>();

	if (!Pawn)
	{
		return;
	}
	
	const FVector2D Value = InputActionValue.Get<FVector2D>();

	const UWorld* World = GetWorld();
	check(World);

	if (Value.X != 0.0f)
	{
		Pawn->AddControllerYawInput(Value.X * YQZYHero::LookYawRate * World->GetDeltaSeconds());
	}

	if (Value.Y != 0.0f)
	{
		Pawn->AddControllerPitchInput(Value.Y * YQZYHero::LookPitchRate * World->GetDeltaSeconds());
	}
}

void UYQZYHeroComponent::Input_Crouch(const FInputActionValue& InputActionValue)
{
	if (AYQZYCharacter* Character = GetPawn<AYQZYCharacter>())
	{
		Character->ToggleCrouch();
	}
}

void UYQZYHeroComponent::Input_AutoRun(const FInputActionValue& InputActionValue)
{
	if (APawn* Pawn = GetPawn<APawn>())
	{
		if (AYQZYPlayerController* Controller = Cast<AYQZYPlayerController>(Pawn->GetController()))
		{
			// Toggle auto running
			Controller->SetIsAutoRunning(!Controller->GetIsAutoRunning());
		}	
	}
}

TSubclassOf<UYQZYCameraMode> UYQZYHeroComponent::DetermineCameraMode() const
{
	if (AbilityCameraMode)
	{
		return AbilityCameraMode;
	}

	const APawn* Pawn = GetPawn<APawn>();
	if (!Pawn)
	{
		return nullptr;
	}

	if (UYQZYPawnExtensionComponent* PawnExtComp = UYQZYPawnExtensionComponent::FindPawnExtensionComponent(Pawn))
	{
		if (const UYQZYPawnData* PawnData = PawnExtComp->GetPawnData<UYQZYPawnData>())
		{
			return PawnData->DefaultCameraMode;
		}
	}

	return nullptr;
}

void UYQZYHeroComponent::SetAbilityCameraMode(TSubclassOf<UYQZYCameraMode> CameraMode, const FGameplayAbilitySpecHandle& OwningSpecHandle)
{
	if (CameraMode)
	{
		AbilityCameraMode = CameraMode;
		AbilityCameraModeOwningSpecHandle = OwningSpecHandle;
	}
}

void UYQZYHeroComponent::ClearAbilityCameraMode(const FGameplayAbilitySpecHandle& OwningSpecHandle)
{
	if (AbilityCameraModeOwningSpecHandle == OwningSpecHandle)
	{
		AbilityCameraMode = nullptr;
		AbilityCameraModeOwningSpecHandle = FGameplayAbilitySpecHandle();
	}
}

