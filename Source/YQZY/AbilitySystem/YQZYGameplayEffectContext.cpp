// Copyright Epic Games, Inc. All Rights Reserved.

#include "YQZYGameplayEffectContext.h"

#include "AbilitySystem/YQZYAbilitySourceInterface.h"
#include "Engine/HitResult.h"
#include "PhysicalMaterials/PhysicalMaterial.h"

#if UE_WITH_IRIS
#include "Iris/ReplicationState/PropertyNetSerializerInfoRegistry.h"
#include "Serialization/GameplayEffectContextNetSerializer.h"
#endif

#include UE_INLINE_GENERATED_CPP_BY_NAME(YQZYGameplayEffectContext)

class FArchive;

FYQZYGameplayEffectContext* FYQZYGameplayEffectContext::ExtractEffectContext(struct FGameplayEffectContextHandle Handle)
{
	FGameplayEffectContext* BaseEffectContext = Handle.Get();
	if ((BaseEffectContext != nullptr) && BaseEffectContext->GetScriptStruct()->IsChildOf(FYQZYGameplayEffectContext::StaticStruct()))
	{
		return (FYQZYGameplayEffectContext*)BaseEffectContext;
	}

	return nullptr;
}

bool FYQZYGameplayEffectContext::NetSerialize(FArchive& Ar, class UPackageMap* Map, bool& bOutSuccess)
{
	FGameplayEffectContext::NetSerialize(Ar, Map, bOutSuccess);

	// Not serialized for post-activation use:
	// CartridgeID

	return true;
}

#if UE_WITH_IRIS
namespace UE::Net
{
	// Forward to FGameplayEffectContextNetSerializer
	// Note: If FYQZYGameplayEffectContext::NetSerialize() is modified, a custom NetSerializesr must be implemented as the current fallback will no longer be sufficient.
	UE_NET_IMPLEMENT_FORWARDING_NETSERIALIZER_AND_REGISTRY_DELEGATES(YQZYGameplayEffectContext, FGameplayEffectContextNetSerializer);
}
#endif

void FYQZYGameplayEffectContext::SetAbilitySource(const IYQZYAbilitySourceInterface* InObject, float InSourceLevel)
{
	AbilitySourceObject = MakeWeakObjectPtr(Cast<const UObject>(InObject));
	//SourceLevel = InSourceLevel;
}

const IYQZYAbilitySourceInterface* FYQZYGameplayEffectContext::GetAbilitySource() const
{
	return Cast<IYQZYAbilitySourceInterface>(AbilitySourceObject.Get());
}

const UPhysicalMaterial* FYQZYGameplayEffectContext::GetPhysicalMaterial() const
{
	if (const FHitResult* HitResultPtr = GetHitResult())
	{
		return HitResultPtr->PhysMaterial.Get();
	}
	return nullptr;
}

