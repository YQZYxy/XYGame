// Copyright Epic Games, Inc. All Rights Reserved.

#include "YQZYReplicationGraphSettings.h"
#include "Misc/App.h"
#include "System/YQZYReplicationGraph.h"

UYQZYReplicationGraphSettings::UYQZYReplicationGraphSettings()
{
	CategoryName = TEXT("Game");
	DefaultReplicationGraphClass = UYQZYReplicationGraph::StaticClass();
}