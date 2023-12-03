// Copyright Epic Games, Inc. All Rights Reserved.

#include "YQZYGameData.h"
#include "YQZYAssetManager.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(YQZYGameData)

UYQZYGameData::UYQZYGameData()
{
}

const UYQZYGameData& UYQZYGameData::UYQZYGameData::Get()
{
	return UYQZYAssetManager::Get().GetGameData();
}
