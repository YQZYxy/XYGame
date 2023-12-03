// Copyright Epic Games, Inc. All Rights Reserved.

#include "YQZYPerfStatWidgetBase.h"

#include "Engine/GameInstance.h"
#include "Performance/YQZYPerformanceStatSubsystem.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(YQZYPerfStatWidgetBase)

//////////////////////////////////////////////////////////////////////
// UYQZYPerfStatWidgetBase

UYQZYPerfStatWidgetBase::UYQZYPerfStatWidgetBase(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

double UYQZYPerfStatWidgetBase::FetchStatValue()
{
	if (CachedStatSubsystem == nullptr)
	{
		if (UWorld* World = GetWorld())
		{
			if (UGameInstance* GameInstance = World->GetGameInstance())
			{
				CachedStatSubsystem = GameInstance->GetSubsystem<UYQZYPerformanceStatSubsystem>();
			}
		}
	}

	if (CachedStatSubsystem)
	{
		return CachedStatSubsystem->GetCachedStat(StatToDisplay);
	}
	else
	{
		return 0.0;
	}
}

