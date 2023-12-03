// Copyright Epic Games, Inc. All Rights Reserved.

#include "YQZYInventoryManagerComponent.h"

#include "Engine/ActorChannel.h"
#include "Engine/World.h"
#include "GameFramework/GameplayMessageSubsystem.h"
#include "YQZYInventoryItemDefinition.h"
#include "YQZYInventoryItemInstance.h"
#include "NativeGameplayTags.h"
#include "Net/UnrealNetwork.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(YQZYInventoryManagerComponent)

class FLifetimeProperty;
struct FReplicationFlags;

UE_DEFINE_GAMEPLAY_TAG_STATIC(TAG_YQZY_Inventory_Message_StackChanged, "YQZY.Inventory.Message.StackChanged");

//////////////////////////////////////////////////////////////////////
// FYQZYInventoryEntry

FString FYQZYInventoryEntry::GetDebugString() const
{
	TSubclassOf<UYQZYInventoryItemDefinition> ItemDef;
	if (Instance != nullptr)
	{
		ItemDef = Instance->GetItemDef();
	}

	return FString::Printf(TEXT("%s (%d x %s)"), *GetNameSafe(Instance), StackCount, *GetNameSafe(ItemDef));
}

//////////////////////////////////////////////////////////////////////
// FYQZYInventoryList

void FYQZYInventoryList::PreReplicatedRemove(const TArrayView<int32> RemovedIndices, int32 FinalSize)
{
	for (int32 Index : RemovedIndices)
	{
		FYQZYInventoryEntry& Stack = Entries[Index];
		BroadcastChangeMessage(Stack, /*OldCount=*/ Stack.StackCount, /*NewCount=*/ 0);
		Stack.LastObservedCount = 0;
	}
}

void FYQZYInventoryList::PostReplicatedAdd(const TArrayView<int32> AddedIndices, int32 FinalSize)
{
	for (int32 Index : AddedIndices)
	{
		FYQZYInventoryEntry& Stack = Entries[Index];
		BroadcastChangeMessage(Stack, /*OldCount=*/ 0, /*NewCount=*/ Stack.StackCount);
		Stack.LastObservedCount = Stack.StackCount;
	}
}

void FYQZYInventoryList::PostReplicatedChange(const TArrayView<int32> ChangedIndices, int32 FinalSize)
{
	for (int32 Index : ChangedIndices)
	{
		FYQZYInventoryEntry& Stack = Entries[Index];
		check(Stack.LastObservedCount != INDEX_NONE);
		BroadcastChangeMessage(Stack, /*OldCount=*/ Stack.LastObservedCount, /*NewCount=*/ Stack.StackCount);
		Stack.LastObservedCount = Stack.StackCount;
	}
}

void FYQZYInventoryList::BroadcastChangeMessage(FYQZYInventoryEntry& Entry, int32 OldCount, int32 NewCount)
{
	FYQZYInventoryChangeMessage Message;
	Message.InventoryOwner = OwnerComponent;
	Message.Instance = Entry.Instance;
	Message.NewCount = NewCount;
	Message.Delta = NewCount - OldCount;

	UGameplayMessageSubsystem& MessageSystem = UGameplayMessageSubsystem::Get(OwnerComponent->GetWorld());
	MessageSystem.BroadcastMessage(TAG_YQZY_Inventory_Message_StackChanged, Message);
}

UYQZYInventoryItemInstance* FYQZYInventoryList::AddEntry(TSubclassOf<UYQZYInventoryItemDefinition> ItemDef, int32 StackCount)
{
	UYQZYInventoryItemInstance* Result = nullptr;

	check(ItemDef != nullptr);
 	check(OwnerComponent);

	AActor* OwningActor = OwnerComponent->GetOwner();
	check(OwningActor->HasAuthority());


	FYQZYInventoryEntry& NewEntry = Entries.AddDefaulted_GetRef();
	NewEntry.Instance = NewObject<UYQZYInventoryItemInstance>(OwnerComponent->GetOwner());  //@TODO: Using the actor instead of component as the outer due to UE-127172
	NewEntry.Instance->SetItemDef(ItemDef);
	for (UYQZYInventoryItemFragment* Fragment : GetDefault<UYQZYInventoryItemDefinition>(ItemDef)->Fragments)
	{
		if (Fragment != nullptr)
		{
			Fragment->OnInstanceCreated(NewEntry.Instance);
		}
	}
	NewEntry.StackCount = StackCount;
	Result = NewEntry.Instance;

	//const UYQZYInventoryItemDefinition* ItemCDO = GetDefault<UYQZYInventoryItemDefinition>(ItemDef);
	MarkItemDirty(NewEntry);

	return Result;
}

void FYQZYInventoryList::AddEntry(UYQZYInventoryItemInstance* Instance)
{
	unimplemented();
}

void FYQZYInventoryList::RemoveEntry(UYQZYInventoryItemInstance* Instance)
{
	for (auto EntryIt = Entries.CreateIterator(); EntryIt; ++EntryIt)
	{
		FYQZYInventoryEntry& Entry = *EntryIt;
		if (Entry.Instance == Instance)
		{
			EntryIt.RemoveCurrent();
			MarkArrayDirty();
		}
	}
}

TArray<UYQZYInventoryItemInstance*> FYQZYInventoryList::GetAllItems() const
{
	TArray<UYQZYInventoryItemInstance*> Results;
	Results.Reserve(Entries.Num());
	for (const FYQZYInventoryEntry& Entry : Entries)
	{
		if (Entry.Instance != nullptr) //@TODO: Would prefer to not deal with this here and hide it further?
		{
			Results.Add(Entry.Instance);
		}
	}
	return Results;
}

//////////////////////////////////////////////////////////////////////
// UYQZYInventoryManagerComponent

UYQZYInventoryManagerComponent::UYQZYInventoryManagerComponent(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
	, InventoryList(this)
{
	SetIsReplicatedByDefault(true);
}

void UYQZYInventoryManagerComponent::GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ThisClass, InventoryList);
}

bool UYQZYInventoryManagerComponent::CanAddItemDefinition(TSubclassOf<UYQZYInventoryItemDefinition> ItemDef, int32 StackCount)
{
	//@TODO: Add support for stack limit / uniqueness checks / etc...
	return true;
}

UYQZYInventoryItemInstance* UYQZYInventoryManagerComponent::AddItemDefinition(TSubclassOf<UYQZYInventoryItemDefinition> ItemDef, int32 StackCount)
{
	UYQZYInventoryItemInstance* Result = nullptr;
	if (ItemDef != nullptr)
	{
		Result = InventoryList.AddEntry(ItemDef, StackCount);
		
		if (IsUsingRegisteredSubObjectList() && IsReadyForReplication() && Result)
		{
			AddReplicatedSubObject(Result);
		}
	}
	return Result;
}

void UYQZYInventoryManagerComponent::AddItemInstance(UYQZYInventoryItemInstance* ItemInstance)
{
	InventoryList.AddEntry(ItemInstance);
	if (IsUsingRegisteredSubObjectList() && IsReadyForReplication() && ItemInstance)
	{
		AddReplicatedSubObject(ItemInstance);
	}
}

void UYQZYInventoryManagerComponent::RemoveItemInstance(UYQZYInventoryItemInstance* ItemInstance)
{
	InventoryList.RemoveEntry(ItemInstance);

	if (ItemInstance && IsUsingRegisteredSubObjectList())
	{
		RemoveReplicatedSubObject(ItemInstance);
	}
}

TArray<UYQZYInventoryItemInstance*> UYQZYInventoryManagerComponent::GetAllItems() const
{
	return InventoryList.GetAllItems();
}

UYQZYInventoryItemInstance* UYQZYInventoryManagerComponent::FindFirstItemStackByDefinition(TSubclassOf<UYQZYInventoryItemDefinition> ItemDef) const
{
	for (const FYQZYInventoryEntry& Entry : InventoryList.Entries)
	{
		UYQZYInventoryItemInstance* Instance = Entry.Instance;

		if (IsValid(Instance))
		{
			if (Instance->GetItemDef() == ItemDef)
			{
				return Instance;
			}
		}
	}

	return nullptr;
}

int32 UYQZYInventoryManagerComponent::GetTotalItemCountByDefinition(TSubclassOf<UYQZYInventoryItemDefinition> ItemDef) const
{
	int32 TotalCount = 0;
	for (const FYQZYInventoryEntry& Entry : InventoryList.Entries)
	{
		UYQZYInventoryItemInstance* Instance = Entry.Instance;

		if (IsValid(Instance))
		{
			if (Instance->GetItemDef() == ItemDef)
			{
				++TotalCount;
			}
		}
	}

	return TotalCount;
}

bool UYQZYInventoryManagerComponent::ConsumeItemsByDefinition(TSubclassOf<UYQZYInventoryItemDefinition> ItemDef, int32 NumToConsume)
{
	AActor* OwningActor = GetOwner();
	if (!OwningActor || !OwningActor->HasAuthority())
	{
		return false;
	}

	//@TODO: N squared right now as there's no acceleration structure
	int32 TotalConsumed = 0;
	while (TotalConsumed < NumToConsume)
	{
		if (UYQZYInventoryItemInstance* Instance = UYQZYInventoryManagerComponent::FindFirstItemStackByDefinition(ItemDef))
		{
			InventoryList.RemoveEntry(Instance);
			++TotalConsumed;
		}
		else
		{
			return false;
		}
	}

	return TotalConsumed == NumToConsume;
}

void UYQZYInventoryManagerComponent::ReadyForReplication()
{
	Super::ReadyForReplication();

	// Register existing UYQZYInventoryItemInstance
	if (IsUsingRegisteredSubObjectList())
	{
		for (const FYQZYInventoryEntry& Entry : InventoryList.Entries)
		{
			UYQZYInventoryItemInstance* Instance = Entry.Instance;

			if (IsValid(Instance))
			{
				AddReplicatedSubObject(Instance);
			}
		}
	}
}

bool UYQZYInventoryManagerComponent::ReplicateSubobjects(UActorChannel* Channel, class FOutBunch* Bunch, FReplicationFlags* RepFlags)
{
	bool WroteSomething = Super::ReplicateSubobjects(Channel, Bunch, RepFlags);

	for (FYQZYInventoryEntry& Entry : InventoryList.Entries)
	{
		UYQZYInventoryItemInstance* Instance = Entry.Instance;

		if (Instance && IsValid(Instance))
		{
			WroteSomething |= Channel->ReplicateSubobject(Instance, *Bunch, *RepFlags);
		}
	}

	return WroteSomething;
}

//////////////////////////////////////////////////////////////////////
//

// UCLASS(Abstract)
// class UYQZYInventoryFilter : public UObject
// {
// public:
// 	virtual bool PassesFilter(UYQZYInventoryItemInstance* Instance) const { return true; }
// };

// UCLASS()
// class UYQZYInventoryFilter_HasTag : public UYQZYInventoryFilter
// {
// public:
// 	virtual bool PassesFilter(UYQZYInventoryItemInstance* Instance) const { return true; }
// };


