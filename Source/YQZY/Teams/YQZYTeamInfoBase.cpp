// Copyright Epic Games, Inc. All Rights Reserved.

#include "YQZYTeamInfoBase.h"

#include "Engine/World.h"
#include "Net/UnrealNetwork.h"
#include "Teams/YQZYTeamSubsystem.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(YQZYTeamInfoBase)

class FLifetimeProperty;

AYQZYTeamInfoBase::AYQZYTeamInfoBase(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
	, TeamId(INDEX_NONE)
{
	bReplicates = true;
	bAlwaysRelevant = true;
	NetPriority = 3.0f;
	SetReplicatingMovement(false);
}

void AYQZYTeamInfoBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ThisClass, TeamTags);
	DOREPLIFETIME_CONDITION(ThisClass, TeamId, COND_InitialOnly);
}

void AYQZYTeamInfoBase::BeginPlay()
{
	Super::BeginPlay();

	TryRegisterWithTeamSubsystem();
}

void AYQZYTeamInfoBase::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	if (TeamId != INDEX_NONE)
	{
		UYQZYTeamSubsystem* TeamSubsystem = GetWorld()->GetSubsystem<UYQZYTeamSubsystem>();
		if (TeamSubsystem)
		{
			// EndPlay can happen at weird times where the subsystem has already been destroyed
			TeamSubsystem->UnregisterTeamInfo(this);
		}
	}

	Super::EndPlay(EndPlayReason);
}

void AYQZYTeamInfoBase::RegisterWithTeamSubsystem(UYQZYTeamSubsystem* Subsystem)
{
	Subsystem->RegisterTeamInfo(this);
}

void AYQZYTeamInfoBase::TryRegisterWithTeamSubsystem()
{
	if (TeamId != INDEX_NONE)
	{
		UYQZYTeamSubsystem* TeamSubsystem = GetWorld()->GetSubsystem<UYQZYTeamSubsystem>();
		if (ensure(TeamSubsystem))
		{
			RegisterWithTeamSubsystem(TeamSubsystem);
		}
	}
}

void AYQZYTeamInfoBase::SetTeamId(int32 NewTeamId)
{
	check(HasAuthority());
	check(TeamId == INDEX_NONE);
	check(NewTeamId != INDEX_NONE);

	TeamId = NewTeamId;

	TryRegisterWithTeamSubsystem();
}

void AYQZYTeamInfoBase::OnRep_TeamId()
{
	TryRegisterWithTeamSubsystem();
}

