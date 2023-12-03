// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "YQZYTeamInfoBase.h"

#include "YQZYTeamPublicInfo.generated.h"

class UYQZYTeamCreationComponent;
class UYQZYTeamDisplayAsset;
class UObject;
struct FFrame;

UCLASS()
class AYQZYTeamPublicInfo : public AYQZYTeamInfoBase
{
	GENERATED_BODY()

	friend UYQZYTeamCreationComponent;

public:
	AYQZYTeamPublicInfo(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	UYQZYTeamDisplayAsset* GetTeamDisplayAsset() const { return TeamDisplayAsset; }

private:
	UFUNCTION()
	void OnRep_TeamDisplayAsset();

	void SetTeamDisplayAsset(TObjectPtr<UYQZYTeamDisplayAsset> NewDisplayAsset);

private:
	UPROPERTY(ReplicatedUsing=OnRep_TeamDisplayAsset)
	TObjectPtr<UYQZYTeamDisplayAsset> TeamDisplayAsset;
};
