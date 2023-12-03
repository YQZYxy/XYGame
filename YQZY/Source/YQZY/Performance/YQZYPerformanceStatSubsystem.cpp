// Copyright Epic Games, Inc. All Rights Reserved.

#include "YQZYPerformanceStatSubsystem.h"

#include "Engine/Engine.h"
#include "Engine/GameInstance.h"
#include "Engine/NetConnection.h"
#include "Engine/World.h"
#include "GameFramework/PlayerState.h"
#include "GameModes/YQZYGameState.h"
#include "Performance/YQZYPerformanceStatTypes.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(YQZYPerformanceStatSubsystem)

class FSubsystemCollectionBase;

//////////////////////////////////////////////////////////////////////
// FYQZYPerformanceStatCache

void FYQZYPerformanceStatCache::StartCharting()
{
}

void FYQZYPerformanceStatCache::ProcessFrame(const FFrameData& FrameData)
{
	CachedData = FrameData;
	CachedServerFPS = 0.0f;
	CachedPingMS = 0.0f;
	CachedPacketLossIncomingPercent = 0.0f;
	CachedPacketLossOutgoingPercent = 0.0f;
	CachedPacketRateIncoming = 0.0f;
	CachedPacketRateOutgoing = 0.0f;
	CachedPacketSizeIncoming = 0.0f;
	CachedPacketSizeOutgoing = 0.0f;

	if (UWorld* World = MySubsystem->GetGameInstance()->GetWorld())
	{
		if (const AYQZYGameState* GameState = World->GetGameState<AYQZYGameState>())
		{
			CachedServerFPS = GameState->GetServerFPS();
		}

		if (APlayerController* LocalPC = GEngine->GetFirstLocalPlayerController(World))
		{
			if (APlayerState* PS = LocalPC->GetPlayerState<APlayerState>())
			{
				CachedPingMS = PS->GetPingInMilliseconds();
			}

			if (UNetConnection* NetConnection = LocalPC->GetNetConnection())
			{
				const UNetConnection::FNetConnectionPacketLoss& InLoss = NetConnection->GetInLossPercentage();
				CachedPacketLossIncomingPercent = InLoss.GetAvgLossPercentage();
				const UNetConnection::FNetConnectionPacketLoss& OutLoss = NetConnection->GetOutLossPercentage();
				CachedPacketLossOutgoingPercent = OutLoss.GetAvgLossPercentage();

				CachedPacketRateIncoming = NetConnection->InPacketsPerSecond;
				CachedPacketRateOutgoing = NetConnection->OutPacketsPerSecond;

				CachedPacketSizeIncoming = (NetConnection->InPacketsPerSecond != 0) ? (NetConnection->InBytesPerSecond / (float)NetConnection->InPacketsPerSecond) : 0.0f;
				CachedPacketSizeOutgoing = (NetConnection->OutPacketsPerSecond != 0) ? (NetConnection->OutBytesPerSecond / (float)NetConnection->OutPacketsPerSecond) : 0.0f;
			}
		}
	}
}

void FYQZYPerformanceStatCache::StopCharting()
{
}

double FYQZYPerformanceStatCache::GetCachedStat(EYQZYDisplayablePerformanceStat Stat) const
{
	static_assert((int32)EYQZYDisplayablePerformanceStat::Count == 15, "Need to update this function to deal with new performance stats");
	switch (Stat)
	{
	case EYQZYDisplayablePerformanceStat::ClientFPS:
		return (CachedData.TrueDeltaSeconds != 0.0) ? (1.0 / CachedData.TrueDeltaSeconds) : 0.0;
	case EYQZYDisplayablePerformanceStat::ServerFPS:
		return CachedServerFPS;
	case EYQZYDisplayablePerformanceStat::IdleTime:
		return CachedData.IdleSeconds;
	case EYQZYDisplayablePerformanceStat::FrameTime:
		return CachedData.TrueDeltaSeconds;
	case EYQZYDisplayablePerformanceStat::FrameTime_GameThread:
		return CachedData.GameThreadTimeSeconds;
	case EYQZYDisplayablePerformanceStat::FrameTime_RenderThread:
		return CachedData.RenderThreadTimeSeconds;
	case EYQZYDisplayablePerformanceStat::FrameTime_RHIThread:
		return CachedData.RHIThreadTimeSeconds;
	case EYQZYDisplayablePerformanceStat::FrameTime_GPU:
		return CachedData.GPUTimeSeconds;
	case EYQZYDisplayablePerformanceStat::Ping:
		return CachedPingMS;
	case EYQZYDisplayablePerformanceStat::PacketLoss_Incoming:
		return CachedPacketLossIncomingPercent;
	case EYQZYDisplayablePerformanceStat::PacketLoss_Outgoing:
		return CachedPacketLossOutgoingPercent;
	case EYQZYDisplayablePerformanceStat::PacketRate_Incoming:
		return CachedPacketRateIncoming;
	case EYQZYDisplayablePerformanceStat::PacketRate_Outgoing:
		return CachedPacketRateOutgoing;
	case EYQZYDisplayablePerformanceStat::PacketSize_Incoming:
		return CachedPacketSizeIncoming;
	case EYQZYDisplayablePerformanceStat::PacketSize_Outgoing:
		return CachedPacketSizeOutgoing;
	}

	return 0.0f;
}

//////////////////////////////////////////////////////////////////////
// UYQZYPerformanceStatSubsystem

void UYQZYPerformanceStatSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Tracker = MakeShared<FYQZYPerformanceStatCache>(this);
	GEngine->AddPerformanceDataConsumer(Tracker);
}

void UYQZYPerformanceStatSubsystem::Deinitialize()
{
	GEngine->RemovePerformanceDataConsumer(Tracker);
	Tracker.Reset();
}

double UYQZYPerformanceStatSubsystem::GetCachedStat(EYQZYDisplayablePerformanceStat Stat) const
{
	return Tracker->GetCachedStat(Stat);
}

