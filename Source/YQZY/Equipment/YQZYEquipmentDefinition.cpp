// Copyright Epic Games, Inc. All Rights Reserved.

#include "YQZYEquipmentDefinition.h"
#include "YQZYEquipmentInstance.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(YQZYEquipmentDefinition)

UYQZYEquipmentDefinition::UYQZYEquipmentDefinition(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	InstanceType = UYQZYEquipmentInstance::StaticClass();
}

