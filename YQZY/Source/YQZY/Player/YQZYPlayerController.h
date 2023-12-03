// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Camera/YQZYCameraAssistInterface.h"
#include "CommonPlayerController.h"
#include "Teams/YQZYTeamAgentInterface.h"

#include "YQZYPlayerController.generated.h"

struct FGenericTeamId;

class AYQZYHUD;
class AYQZYPlayerState;
class APawn;
class APlayerState;
class FPrimitiveComponentId;
class IInputInterface;
class UYQZYAbilitySystemComponent;
class UYQZYSettingsShared;
class UObject;
class UPlayer;
struct FFrame;

/**
 * AYQZYPlayerController
 *
 *	The base player controller class used by this project.
 */
UCLASS(Config = Game, Meta = (ShortTooltip = "The base player controller class used by this project."))
class YQZY_API AYQZYPlayerController : public ACommonPlayerController, public IYQZYCameraAssistInterface, public IYQZYTeamAgentInterface
{
	GENERATED_BODY()

public:

	AYQZYPlayerController(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	UFUNCTION(BlueprintCallable, Category = "YQZY|PlayerController")
	AYQZYPlayerState* GetYQZYPlayerState() const;

	UFUNCTION(BlueprintCallable, Category = "YQZY|PlayerController")
	UYQZYAbilitySystemComponent* GetYQZYAbilitySystemComponent() const;

	UFUNCTION(BlueprintCallable, Category = "YQZY|PlayerController")
	AYQZYHUD* GetYQZYHUD() const;

	// Run a cheat command on the server.
	UFUNCTION(Reliable, Server, WithValidation)
	void ServerCheat(const FString& Msg);

	// Run a cheat command on the server for all players.
	UFUNCTION(Reliable, Server, WithValidation)
	void ServerCheatAll(const FString& Msg);

	//~AActor interface
	virtual void PreInitializeComponents() override;
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	//~End of AActor interface

	//~AController interface
	virtual void OnUnPossess() override;
	//~End of AController interface

	//~APlayerController interface
	virtual void ReceivedPlayer() override;
	virtual void PlayerTick(float DeltaTime) override;
	//~End of APlayerController interface

	//~IYQZYCameraAssistInterface interface
	virtual void OnCameraPenetratingTarget() override;
	//~End of IYQZYCameraAssistInterface interface

	//~ACommonPlayerController interface
	virtual void OnPossess(APawn* InPawn) override;
	//~End of ACommonPlayerController interface
	
	//~IYQZYTeamAgentInterface interface
	virtual void SetGenericTeamId(const FGenericTeamId& NewTeamID) override;
	virtual FGenericTeamId GetGenericTeamId() const override;
	virtual FOnYQZYTeamIndexChangedDelegate* GetOnTeamIndexChangedDelegate() override;
	//~End of IYQZYTeamAgentInterface interface

	UFUNCTION(BlueprintCallable, Category = "YQZY|Character")
	void SetIsAutoRunning(const bool bEnabled);

	UFUNCTION(BlueprintCallable, Category = "YQZY|Character")
	bool GetIsAutoRunning() const;

private:
	UPROPERTY()
	FOnYQZYTeamIndexChangedDelegate OnTeamChangedDelegate;

	UPROPERTY()
	TObjectPtr<APlayerState> LastSeenPlayerState;

private:
	UFUNCTION()
	void OnPlayerStateChangedTeam(UObject* TeamAgent, int32 OldTeam, int32 NewTeam);

protected:
	// Called when the player state is set or cleared
	virtual void OnPlayerStateChanged();

private:
	void BroadcastOnPlayerStateChanged();

protected:
	//~AController interface
	virtual void InitPlayerState() override;
	virtual void CleanupPlayerState() override;
	virtual void OnRep_PlayerState() override;
	//~End of AController interface

	//~APlayerController interface
	virtual void SetPlayer(UPlayer* InPlayer) override;
	virtual void AddCheats(bool bForce) override;

	virtual void UpdateForceFeedback(IInputInterface* InputInterface, const int32 ControllerId) override;
	virtual void UpdateHiddenComponents(const FVector& ViewLocation, TSet<FPrimitiveComponentId>& OutHiddenComponents) override;

	virtual void PreProcessInput(const float DeltaTime, const bool bGamePaused) override;
	virtual void PostProcessInput(const float DeltaTime, const bool bGamePaused) override;
	//~End of APlayerController interface

	void OnSettingsChanged(UYQZYSettingsShared* Settings);
	
	void OnStartAutoRun();
	void OnEndAutoRun();

	UFUNCTION(BlueprintImplementableEvent, meta=(DisplayName="OnStartAutoRun"))
	void K2_OnStartAutoRun();

	UFUNCTION(BlueprintImplementableEvent, meta=(DisplayName="OnEndAutoRun"))
	void K2_OnEndAutoRun();

	bool bHideViewTargetPawnNextFrame = false;
};


// A player controller used for replay capture and playback
UCLASS()
class AYQZYReplayPlayerController : public AYQZYPlayerController
{
	GENERATED_BODY()

	virtual void SetPlayer(UPlayer* InPlayer) override;
};
