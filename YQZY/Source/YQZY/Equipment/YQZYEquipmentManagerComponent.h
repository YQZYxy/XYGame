// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "AbilitySystem/YQZYAbilitySet.h"
#include "Components/PawnComponent.h"
#include "Net/Serialization/FastArraySerializer.h"

#include "YQZYEquipmentManagerComponent.generated.h"

class UActorComponent;
class UYQZYAbilitySystemComponent;
class UYQZYEquipmentDefinition;
class UYQZYEquipmentInstance;
class UYQZYEquipmentManagerComponent;
class UObject;
struct FFrame;
struct FYQZYEquipmentList;
struct FNetDeltaSerializeInfo;
struct FReplicationFlags;

/** A single piece of applied equipment */
USTRUCT(BlueprintType)
struct FYQZYAppliedEquipmentEntry : public FFastArraySerializerItem
{
	GENERATED_BODY()

	FYQZYAppliedEquipmentEntry()
	{}

	FString GetDebugString() const;

private:
	friend FYQZYEquipmentList;
	friend UYQZYEquipmentManagerComponent;

	// The equipment class that got equipped
	UPROPERTY()
	TSubclassOf<UYQZYEquipmentDefinition> EquipmentDefinition;

	UPROPERTY()
	TObjectPtr<UYQZYEquipmentInstance> Instance = nullptr;

	// Authority-only list of granted handles
	UPROPERTY(NotReplicated)
	FYQZYAbilitySet_GrantedHandles GrantedHandles;
};

/** List of applied equipment */
USTRUCT(BlueprintType)
struct FYQZYEquipmentList : public FFastArraySerializer
{
	GENERATED_BODY()

	FYQZYEquipmentList()
		: OwnerComponent(nullptr)
	{
	}

	FYQZYEquipmentList(UActorComponent* InOwnerComponent)
		: OwnerComponent(InOwnerComponent)
	{
	}

public:
	//~FFastArraySerializer contract
	void PreReplicatedRemove(const TArrayView<int32> RemovedIndices, int32 FinalSize);
	void PostReplicatedAdd(const TArrayView<int32> AddedIndices, int32 FinalSize);
	void PostReplicatedChange(const TArrayView<int32> ChangedIndices, int32 FinalSize);
	//~End of FFastArraySerializer contract

	bool NetDeltaSerialize(FNetDeltaSerializeInfo& DeltaParms)
	{
		return FFastArraySerializer::FastArrayDeltaSerialize<FYQZYAppliedEquipmentEntry, FYQZYEquipmentList>(Entries, DeltaParms, *this);
	}

	UYQZYEquipmentInstance* AddEntry(TSubclassOf<UYQZYEquipmentDefinition> EquipmentDefinition);
	void RemoveEntry(UYQZYEquipmentInstance* Instance);

private:
	UYQZYAbilitySystemComponent* GetAbilitySystemComponent() const;

	friend UYQZYEquipmentManagerComponent;

private:
	// Replicated list of equipment entries
	UPROPERTY()
	TArray<FYQZYAppliedEquipmentEntry> Entries;

	UPROPERTY(NotReplicated)
	TObjectPtr<UActorComponent> OwnerComponent;
};

template<>
struct TStructOpsTypeTraits<FYQZYEquipmentList> : public TStructOpsTypeTraitsBase2<FYQZYEquipmentList>
{
	enum { WithNetDeltaSerializer = true };
};










/**
 * Manages equipment applied to a pawn
 */
UCLASS(BlueprintType, Const)
class UYQZYEquipmentManagerComponent : public UPawnComponent
{
	GENERATED_BODY()

public:
	UYQZYEquipmentManagerComponent(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly)
	UYQZYEquipmentInstance* EquipItem(TSubclassOf<UYQZYEquipmentDefinition> EquipmentDefinition);

	UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly)
	void UnequipItem(UYQZYEquipmentInstance* ItemInstance);

	//~UObject interface
	virtual bool ReplicateSubobjects(class UActorChannel* Channel, class FOutBunch* Bunch, FReplicationFlags* RepFlags) override;
	//~End of UObject interface

	//~UActorComponent interface
	//virtual void EndPlay() override;
	virtual void InitializeComponent() override;
	virtual void UninitializeComponent() override;
	virtual void ReadyForReplication() override;
	//~End of UActorComponent interface

	/** Returns the first equipped instance of a given type, or nullptr if none are found */
	UFUNCTION(BlueprintCallable, BlueprintPure)
	UYQZYEquipmentInstance* GetFirstInstanceOfType(TSubclassOf<UYQZYEquipmentInstance> InstanceType);

 	/** Returns all equipped instances of a given type, or an empty array if none are found */
 	UFUNCTION(BlueprintCallable, BlueprintPure)
	TArray<UYQZYEquipmentInstance*> GetEquipmentInstancesOfType(TSubclassOf<UYQZYEquipmentInstance> InstanceType) const;

	template <typename T>
	T* GetFirstInstanceOfType()
	{
		return (T*)GetFirstInstanceOfType(T::StaticClass());
	}

private:
	UPROPERTY(Replicated)
	FYQZYEquipmentList EquipmentList;
};
