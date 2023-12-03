// Copyright Epic Games, Inc. All Rights Reserved.

#include "YQZYCheatManager.h"
#include "GameFramework/Pawn.h"
#include "YQZYPlayerController.h"
#include "YQZYDebugCameraController.h"
#include "Engine/Engine.h"
#include "Engine/GameViewportClient.h"
#include "Engine/Console.h"
#include "GameFramework/HUD.h"
#include "System/YQZYAssetManager.h"
#include "System/YQZYGameData.h"
#include "YQZYGameplayTags.h"
#include "AbilitySystem/YQZYAbilitySystemComponent.h"
#include "AbilitySystemGlobals.h"
#include "Character/YQZYHealthComponent.h"
#include "Character/YQZYPawnExtensionComponent.h"
#include "System/YQZYSystemStatics.h"
#include "Development/YQZYDeveloperSettings.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(YQZYCheatManager)

DEFINE_LOG_CATEGORY(LogYQZYCheat);

namespace YQZYCheat
{
	static const FName NAME_Fixed = FName(TEXT("Fixed"));
	
	static bool bEnableDebugCameraCycling = false;
	static FAutoConsoleVariableRef CVarEnableDebugCameraCycling(
		TEXT("YQZYCheat.EnableDebugCameraCycling"),
		bEnableDebugCameraCycling,
		TEXT("If true then you can cycle the debug camera while running the game."),
		ECVF_Cheat);

	static bool bStartInGodMode = false;
	static FAutoConsoleVariableRef CVarStartInGodMode(
		TEXT("YQZYCheat.StartInGodMode"),
		bStartInGodMode,
		TEXT("If true then the God cheat will be applied on begin play"),
		ECVF_Cheat);
};


UYQZYCheatManager::UYQZYCheatManager()
{
	DebugCameraControllerClass = AYQZYDebugCameraController::StaticClass();
}

void UYQZYCheatManager::InitCheatManager()
{
	Super::InitCheatManager();

#if WITH_EDITOR
	if (GIsEditor)
	{
		APlayerController* PC = GetOuterAPlayerController();
		for (const FYQZYCheatToRun& CheatRow : GetDefault<UYQZYDeveloperSettings>()->CheatsToRun)
		{
			if (CheatRow.Phase == ECheatExecutionTime::OnCheatManagerCreated)
			{
				PC->ConsoleCommand(CheatRow.Cheat, /*bWriteToLog=*/ true);
			}
		}
	}
#endif

	if (YQZYCheat::bStartInGodMode)
	{
		God();	
	}
}

void UYQZYCheatManager::CheatOutputText(const FString& TextToOutput)
{
#if USING_CHEAT_MANAGER
	// Output to the console.
	if (GEngine && GEngine->GameViewport && GEngine->GameViewport->ViewportConsole)
	{
		GEngine->GameViewport->ViewportConsole->OutputText(TextToOutput);
	}

	// Output to log.
	UE_LOG(LogYQZYCheat, Display, TEXT("%s"), *TextToOutput);
#endif // USING_CHEAT_MANAGER
}

void UYQZYCheatManager::Cheat(const FString& Msg)
{
	if (AYQZYPlayerController* YQZYPC = Cast<AYQZYPlayerController>(GetOuterAPlayerController()))
	{
		YQZYPC->ServerCheat(Msg.Left(128));
	}
}

void UYQZYCheatManager::CheatAll(const FString& Msg)
{
	if (AYQZYPlayerController* YQZYPC = Cast<AYQZYPlayerController>(GetOuterAPlayerController()))
	{
		YQZYPC->ServerCheatAll(Msg.Left(128));
	}
}

void UYQZYCheatManager::PlayNextGame()
{
	UYQZYSystemStatics::PlayNextGame(this);
}

void UYQZYCheatManager::EnableDebugCamera()
{
	Super::EnableDebugCamera();
}

void UYQZYCheatManager::DisableDebugCamera()
{
	FVector DebugCameraLocation;
	FRotator DebugCameraRotation;

	ADebugCameraController* DebugCC = Cast<ADebugCameraController>(GetOuter());
	APlayerController* OriginalPC = nullptr;

	if (DebugCC)
	{
		OriginalPC = DebugCC->OriginalControllerRef;
		DebugCC->GetPlayerViewPoint(DebugCameraLocation, DebugCameraRotation);
	}

	Super::DisableDebugCamera();

	if (OriginalPC && OriginalPC->PlayerCameraManager && (OriginalPC->PlayerCameraManager->CameraStyle == YQZYCheat::NAME_Fixed))
	{
		OriginalPC->SetInitialLocationAndRotation(DebugCameraLocation, DebugCameraRotation);

		OriginalPC->PlayerCameraManager->ViewTarget.POV.Location = DebugCameraLocation;
		OriginalPC->PlayerCameraManager->ViewTarget.POV.Rotation = DebugCameraRotation;
		OriginalPC->PlayerCameraManager->PendingViewTarget.POV.Location = DebugCameraLocation;
		OriginalPC->PlayerCameraManager->PendingViewTarget.POV.Rotation = DebugCameraRotation;
	}
}

bool UYQZYCheatManager::InDebugCamera() const
{
	return (Cast<ADebugCameraController>(GetOuter()) ? true : false);
}

void UYQZYCheatManager::EnableFixedCamera()
{
	const ADebugCameraController* DebugCC = Cast<ADebugCameraController>(GetOuter());
	APlayerController* PC = (DebugCC ? ToRawPtr(DebugCC->OriginalControllerRef) : GetOuterAPlayerController());

	if (PC && PC->PlayerCameraManager)
	{
		PC->SetCameraMode(YQZYCheat::NAME_Fixed);
	}
}

void UYQZYCheatManager::DisableFixedCamera()
{
	const ADebugCameraController* DebugCC = Cast<ADebugCameraController>(GetOuter());
	APlayerController* PC = (DebugCC ? ToRawPtr(DebugCC->OriginalControllerRef) : GetOuterAPlayerController());

	if (PC && PC->PlayerCameraManager)
	{
		PC->SetCameraMode(NAME_Default);
	}
}

bool UYQZYCheatManager::InFixedCamera() const
{
	const ADebugCameraController* DebugCC = Cast<ADebugCameraController>(GetOuter());
	const APlayerController* PC = (DebugCC ? ToRawPtr(DebugCC->OriginalControllerRef) : GetOuterAPlayerController());

	if (PC && PC->PlayerCameraManager)
	{
		return (PC->PlayerCameraManager->CameraStyle == YQZYCheat::NAME_Fixed);
	}

	return false;
}

void UYQZYCheatManager::ToggleFixedCamera()
{
	if (InFixedCamera())
	{
		DisableFixedCamera();
	}
	else
	{
		EnableFixedCamera();
	}
}

void UYQZYCheatManager::CycleDebugCameras()
{
	if (!YQZYCheat::bEnableDebugCameraCycling)
	{
		return;
	}
	
	if (InDebugCamera())
	{
		EnableFixedCamera();
		DisableDebugCamera();
	}
	else if (InFixedCamera())
	{
		DisableFixedCamera();
		DisableDebugCamera();
	}
	else
	{
		EnableDebugCamera();
		DisableFixedCamera();
	}
}

void UYQZYCheatManager::CycleAbilitySystemDebug()
{
	APlayerController* PC = Cast<APlayerController>(GetOuterAPlayerController());

	if (PC && PC->MyHUD)
	{
		if (!PC->MyHUD->bShowDebugInfo || !PC->MyHUD->DebugDisplay.Contains(TEXT("AbilitySystem")))
		{
			PC->MyHUD->ShowDebug(TEXT("AbilitySystem"));
		}

		PC->ConsoleCommand(TEXT("AbilitySystem.Debug.NextCategory"));
	}
}

void UYQZYCheatManager::CancelActivatedAbilities()
{
	if (UYQZYAbilitySystemComponent* YQZYASC = GetPlayerAbilitySystemComponent())
	{
		const bool bReplicateCancelAbility = true;
		YQZYASC->CancelInputActivatedAbilities(bReplicateCancelAbility);
	}
}

void UYQZYCheatManager::AddTagToSelf(FString TagName)
{
	FGameplayTag Tag = YQZYGameplayTags::FindTagByString(TagName, true);
	if (Tag.IsValid())
	{
		if (UYQZYAbilitySystemComponent* YQZYASC = GetPlayerAbilitySystemComponent())
		{
			YQZYASC->AddDynamicTagGameplayEffect(Tag);
		}
	}
	else
	{
		UE_LOG(LogYQZYCheat, Display, TEXT("AddTagToSelf: Could not find any tag matching [%s]."), *TagName);
	}
}

void UYQZYCheatManager::RemoveTagFromSelf(FString TagName)
{
	FGameplayTag Tag = YQZYGameplayTags::FindTagByString(TagName, true);
	if (Tag.IsValid())
	{
		if (UYQZYAbilitySystemComponent* YQZYASC = GetPlayerAbilitySystemComponent())
		{
			YQZYASC->RemoveDynamicTagGameplayEffect(Tag);
		}
	}
	else
	{
		UE_LOG(LogYQZYCheat, Display, TEXT("RemoveTagFromSelf: Could not find any tag matching [%s]."), *TagName);
	}
}

void UYQZYCheatManager::DamageSelf(float DamageAmount)
{
	if (UYQZYAbilitySystemComponent* YQZYASC = GetPlayerAbilitySystemComponent())
	{
		ApplySetByCallerDamage(YQZYASC, DamageAmount);
	}
}

void UYQZYCheatManager::DamageTarget(float DamageAmount)
{
	if (AYQZYPlayerController* YQZYPC = Cast<AYQZYPlayerController>(GetOuterAPlayerController()))
	{
		if (YQZYPC->GetNetMode() == NM_Client)
		{
			// Automatically send cheat to server for convenience.
			YQZYPC->ServerCheat(FString::Printf(TEXT("DamageTarget %.2f"), DamageAmount));
			return;
		}

		FHitResult TargetHitResult;
		AActor* TargetActor = GetTarget(YQZYPC, TargetHitResult);

		if (UYQZYAbilitySystemComponent* YQZYTargetASC = Cast<UYQZYAbilitySystemComponent>(UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(TargetActor)))
		{
			ApplySetByCallerDamage(YQZYTargetASC, DamageAmount);
		}
	}
}

void UYQZYCheatManager::ApplySetByCallerDamage(UYQZYAbilitySystemComponent* YQZYASC, float DamageAmount)
{
	check(YQZYASC);

	TSubclassOf<UGameplayEffect> DamageGE = UYQZYAssetManager::GetSubclass(UYQZYGameData::Get().DamageGameplayEffect_SetByCaller);
	FGameplayEffectSpecHandle SpecHandle = YQZYASC->MakeOutgoingSpec(DamageGE, 1.0f, YQZYASC->MakeEffectContext());

	if (SpecHandle.IsValid())
	{
		SpecHandle.Data->SetSetByCallerMagnitude(YQZYGameplayTags::SetByCaller_Damage, DamageAmount);
		YQZYASC->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
	}
}

void UYQZYCheatManager::HealSelf(float HealAmount)
{
	if (UYQZYAbilitySystemComponent* YQZYASC = GetPlayerAbilitySystemComponent())
	{
		ApplySetByCallerHeal(YQZYASC, HealAmount);
	}
}

void UYQZYCheatManager::HealTarget(float HealAmount)
{
	if (AYQZYPlayerController* YQZYPC = Cast<AYQZYPlayerController>(GetOuterAPlayerController()))
	{
		FHitResult TargetHitResult;
		AActor* TargetActor = GetTarget(YQZYPC, TargetHitResult);

		if (UYQZYAbilitySystemComponent* YQZYTargetASC = Cast<UYQZYAbilitySystemComponent>(UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(TargetActor)))
		{
			ApplySetByCallerHeal(YQZYTargetASC, HealAmount);
		}
	}
}

void UYQZYCheatManager::ApplySetByCallerHeal(UYQZYAbilitySystemComponent* YQZYASC, float HealAmount)
{
	check(YQZYASC);

	TSubclassOf<UGameplayEffect> HealGE = UYQZYAssetManager::GetSubclass(UYQZYGameData::Get().HealGameplayEffect_SetByCaller);
	FGameplayEffectSpecHandle SpecHandle = YQZYASC->MakeOutgoingSpec(HealGE, 1.0f, YQZYASC->MakeEffectContext());

	if (SpecHandle.IsValid())
	{
		SpecHandle.Data->SetSetByCallerMagnitude(YQZYGameplayTags::SetByCaller_Heal, HealAmount);
		YQZYASC->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
	}
}

UYQZYAbilitySystemComponent* UYQZYCheatManager::GetPlayerAbilitySystemComponent() const
{
	if (AYQZYPlayerController* YQZYPC = Cast<AYQZYPlayerController>(GetOuterAPlayerController()))
	{
		return YQZYPC->GetYQZYAbilitySystemComponent();
	}
	return nullptr;
}

void UYQZYCheatManager::DamageSelfDestruct()
{
	if (AYQZYPlayerController* YQZYPC = Cast<AYQZYPlayerController>(GetOuterAPlayerController()))
	{
 		if (const UYQZYPawnExtensionComponent* PawnExtComp = UYQZYPawnExtensionComponent::FindPawnExtensionComponent(YQZYPC->GetPawn()))
		{
			if (PawnExtComp->HasReachedInitState(YQZYGameplayTags::InitState_GameplayReady))
			{
				if (UYQZYHealthComponent* HealthComponent = UYQZYHealthComponent::FindHealthComponent(YQZYPC->GetPawn()))
				{
					HealthComponent->DamageSelfDestruct();
				}
			}
		}
	}
}

void UYQZYCheatManager::God()
{
	if (AYQZYPlayerController* YQZYPC = Cast<AYQZYPlayerController>(GetOuterAPlayerController()))
	{
		if (YQZYPC->GetNetMode() == NM_Client)
		{
			// Automatically send cheat to server for convenience.
			YQZYPC->ServerCheat(FString::Printf(TEXT("God")));
			return;
		}

		if (UYQZYAbilitySystemComponent* YQZYASC = YQZYPC->GetYQZYAbilitySystemComponent())
		{
			const FGameplayTag Tag = YQZYGameplayTags::Cheat_GodMode;
			const bool bHasTag = YQZYASC->HasMatchingGameplayTag(Tag);

			if (bHasTag)
			{
				YQZYASC->RemoveDynamicTagGameplayEffect(Tag);
			}
			else
			{
				YQZYASC->AddDynamicTagGameplayEffect(Tag);
			}
		}
	}
}

void UYQZYCheatManager::UnlimitedHealth(int32 Enabled)
{
	if (UYQZYAbilitySystemComponent* YQZYASC = GetPlayerAbilitySystemComponent())
	{
		const FGameplayTag Tag = YQZYGameplayTags::Cheat_UnlimitedHealth;
		const bool bHasTag = YQZYASC->HasMatchingGameplayTag(Tag);

		if ((Enabled == -1) || ((Enabled > 0) && !bHasTag) || ((Enabled == 0) && bHasTag))
		{
			if (bHasTag)
			{
				YQZYASC->RemoveDynamicTagGameplayEffect(Tag);
			}
			else
			{
				YQZYASC->AddDynamicTagGameplayEffect(Tag);
			}
		}
	}
}

