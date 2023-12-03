// Copyright Epic Games, Inc. All Rights Reserved.

#include "YQZYTeamPublicInfo.h"

#include "Net/UnrealNetwork.h"
#include "Teams/YQZYTeamInfoBase.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(YQZYTeamPublicInfo)

class FLifetimeProperty;

AYQZYTeamPublicInfo::AYQZYTeamPublicInfo(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

void AYQZYTeamPublicInfo::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION(ThisClass, TeamDisplayAsset, COND_InitialOnly);
}

void AYQZYTeamPublicInfo::SetTeamDisplayAsset(TObjectPtr<UYQZYTeamDisplayAsset> NewDisplayAsset)
{
	check(HasAuthority());
	check(TeamDisplayAsset == nullptr);

	TeamDisplayAsset = NewDisplayAsset;

	TryRegisterWithTeamSubsystem();
}

void AYQZYTeamPublicInfo::OnRep_TeamDisplayAsset()
{
	TryRegisterWithTeamSubsystem();
}

