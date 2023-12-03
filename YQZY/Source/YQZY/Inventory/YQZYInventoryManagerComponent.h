// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Components/ActorComponent.h"
#include "Net/Serialization/FastArraySerializer.h"

#include "YQZYInventoryManagerComponent.generated.h"

class UYQZYInventoryItemDefinition;
class UYQZYInventoryItemInstance;
class UYQZYInventoryManagerComponent;
class UObject;
struct FFrame;
struct FYQZYInventoryList;
struct FNetDeltaSerializeInfo;
struct FReplicationFlags;

/** A message when an item is added to the inventory */
USTRUCT(BlueprintType)
struct FYQZYInventoryChangeMessage
{
	GENERATED_BODY()

	//@TODO: Tag based names+owning actors for inventories instead of directly exposing the component?
	UPROPERTY(BlueprintReadOnly, Category=Inventory)
	TObjectPtr<UActorComponent> InventoryOwner = nullptr;

	UPROPERTY(BlueprintReadOnly, Category = Inventory)
	TObjectPtr<UYQZYInventoryItemInstance> Instance = nullptr;

	UPROPERTY(BlueprintReadOnly, Category=Inventory)
	int32 NewCount = 0;

	UPROPERTY(BlueprintReadOnly, Category=Inventory)
	int32 Delta = 0;
};

/** A single entry in an inventory */
USTRUCT(BlueprintType)
struct FYQZYInventoryEntry : public FFastArraySerializerItem
{
	GENERATED_BODY()

	FYQZYInventoryEntry()
	{}

	FString GetDebugString() const;

private:
	friend FYQZYInventoryList;
	friend UYQZYInventoryManagerComponent;

	UPROPERTY()
	TObjectPtr<UYQZYInventoryItemInstance> Instance = nullptr;

	UPROPERTY()
	int32 StackCount = 0;

	UPROPERTY(NotReplicated)
	int32 LastObservedCount = INDEX_NONE;
};

/** List of inventory items */
USTRUCT(BlueprintType)
struct FYQZYInventoryList : public FFastArraySerializer
{
	GENERATED_BODY()

	FYQZYInventoryList()
		: OwnerComponent(nullptr)
	{
	}

	FYQZYInventoryList(UActorComponent* InOwnerComponent)
		: OwnerComponent(InOwnerComponent)
	{
	}

	TArray<UYQZYInventoryItemInstance*> GetAllItems() const;

public:
	//~FFastArraySerializer contract
	void PreReplicatedRemove(const TArrayView<int32> RemovedIndices, int32 FinalSize);
	void PostReplicatedAdd(const TArrayView<int32> AddedIndices, int32 FinalSize);
	void PostReplicatedChange(const TArrayView<int32> ChangedIndices, int32 FinalSize);
	//~End of FFastArraySerializer contract

	bool NetDeltaSerialize(FNetDeltaSerializeInfo& DeltaParms)
	{
		return FFastArraySerializer::FastArrayDeltaSerialize<FYQZYInventoryEntry, FYQZYInventoryList>(Entries, DeltaParms, *this);
	}

	UYQZYInventoryItemInstance* AddEntry(TSubclassOf<UYQZYInventoryItemDefinition> ItemClass, int32 StackCount);
	void AddEntry(UYQZYInventoryItemInstance* Instance);

	void RemoveEntry(UYQZYInventoryItemInstance* Instance);

private:
	void BroadcastChangeMessage(FYQZYInventoryEntry& Entry, int32 OldCount, int32 NewCount);

private:
	friend UYQZYInventoryManagerComponent;

private:
	// Replicated list of items
	UPROPERTY()
	TArray<FYQZYInventoryEntry> Entries;

	UPROPERTY(NotReplicated)
	TObjectPtr<UActorComponent> OwnerComponent;
};

template<>
struct TStructOpsTypeTraits<FYQZYInventoryList> : public TStructOpsTypeTraitsBase2<FYQZYInventoryList>
{
	enum { WithNetDeltaSerializer = true };
};










/**
 * Manages an inventory
 */
UCLASS(BlueprintType)
class YQZY_API UYQZYInventoryManagerComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UYQZYInventoryManagerComponent(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category=Inventory)
	bool CanAddItemDefinition(TSubclassOf<UYQZYInventoryItemDefinition> ItemDef, int32 StackCount = 1);

	UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category=Inventory)
	UYQZYInventoryItemInstance* AddItemDefinition(TSubclassOf<UYQZYInventoryItemDefinition> ItemDef, int32 StackCount = 1);

	UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category=Inventory)
	void AddItemInstance(UYQZYInventoryItemInstance* ItemInstance);

	UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category=Inventory)
	void RemoveItemInstance(UYQZYInventoryItemInstance* ItemInstance);

	UFUNCTION(BlueprintCallable, Category=Inventory, BlueprintPure=false)
	TArray<UYQZYInventoryItemInstance*> GetAllItems() const;

	UFUNCTION(BlueprintCallable, Category=Inventory, BlueprintPure)
	UYQZYInventoryItemInstance* FindFirstItemStackByDefinition(TSubclassOf<UYQZYInventoryItemDefinition> ItemDef) const;

	int32 GetTotalItemCountByDefinition(TSubclassOf<UYQZYInventoryItemDefinition> ItemDef) const;
	bool ConsumeItemsByDefinition(TSubclassOf<UYQZYInventoryItemDefinition> ItemDef, int32 NumToConsume);

	//~UObject interface
	virtual bool ReplicateSubobjects(class UActorChannel* Channel, class FOutBunch* Bunch, FReplicationFlags* RepFlags) override;
	virtual void ReadyForReplication() override;
	//~End of UObject interface

private:
	UPROPERTY(Replicated)
	FYQZYInventoryList InventoryList;
};
