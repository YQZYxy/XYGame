// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "GameplayTagContainer.h"
#include "YQZYVerbMessage.h"
#include "Net/Serialization/FastArraySerializer.h"

#include "YQZYVerbMessageReplication.generated.h"

class UObject;
struct FYQZYVerbMessageReplication;
struct FNetDeltaSerializeInfo;

/**
 * Represents one verb message
 */
USTRUCT(BlueprintType)
struct FYQZYVerbMessageReplicationEntry : public FFastArraySerializerItem
{
	GENERATED_BODY()

	FYQZYVerbMessageReplicationEntry()
	{}

	FYQZYVerbMessageReplicationEntry(const FYQZYVerbMessage& InMessage)
		: Message(InMessage)
	{
	}

	FString GetDebugString() const;

private:
	friend FYQZYVerbMessageReplication;

	UPROPERTY()
	FYQZYVerbMessage Message;
};

/** Container of verb messages to replicate */
USTRUCT(BlueprintType)
struct FYQZYVerbMessageReplication : public FFastArraySerializer
{
	GENERATED_BODY()

	FYQZYVerbMessageReplication()
	{
	}

public:
	void SetOwner(UObject* InOwner) { Owner = InOwner; }

	// Broadcasts a message from server to clients
	void AddMessage(const FYQZYVerbMessage& Message);

	//~FFastArraySerializer contract
	void PreReplicatedRemove(const TArrayView<int32> RemovedIndices, int32 FinalSize);
	void PostReplicatedAdd(const TArrayView<int32> AddedIndices, int32 FinalSize);
	void PostReplicatedChange(const TArrayView<int32> ChangedIndices, int32 FinalSize);
	//~End of FFastArraySerializer contract

	bool NetDeltaSerialize(FNetDeltaSerializeInfo& DeltaParms)
	{
		return FFastArraySerializer::FastArrayDeltaSerialize<FYQZYVerbMessageReplicationEntry, FYQZYVerbMessageReplication>(CurrentMessages, DeltaParms, *this);
	}

private:
	void RebroadcastMessage(const FYQZYVerbMessage& Message);

private:
	// Replicated list of gameplay tag stacks
	UPROPERTY()
	TArray<FYQZYVerbMessageReplicationEntry> CurrentMessages;
	
	// Owner (for a route to a world)
	UPROPERTY()
	TObjectPtr<UObject> Owner = nullptr;
};

template<>
struct TStructOpsTypeTraits<FYQZYVerbMessageReplication> : public TStructOpsTypeTraitsBase2<FYQZYVerbMessageReplication>
{
	enum
	{
		WithNetDeltaSerializer = true,
	};
};
