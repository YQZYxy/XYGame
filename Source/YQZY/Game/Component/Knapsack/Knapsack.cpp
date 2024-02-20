// Fill out your copyright notice in the Description page of Project Settings.

#include "Knapsack.h"
#include "Game/Global/BPItemPool.h"
#include "Game/Struct/ItemData.h"
#include <set>
#include "YQZYLog.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(Knapsack)

// Sets default values for this component's properties
UKnapsack::UKnapsack():knapsack_size(9), OwnerPawn(nullptr)
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

}


// Called when the game starts
void UKnapsack::BeginPlay()
{
	Super::BeginPlay();

	// ...
	this->Init();
}


// Called every frame
void UKnapsack::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UKnapsack::Init()
{
	UBPItemPool* item_pool = ITEMPOOL(GetWorld());

	if (item_pool && !item_pool->Init())
	{
		YQZYError("ITEMPOOL->Init()  error");
	}


	if (item_pool != nullptr)
	{
		for (int i = 1; i < 5; ++i)
		{
			auto it = item_pool->GetItemBaseData(i);
			if (it.IsValid())
			{
				YQZYWarning("id[%d] max_num[%d] ", it.item_id, it.max_num);
			}

		}
	}
}


void UKnapsack::OnAddItemList(TArray<FItemData> item_list, FString& reason)
{
	for (FItemData it: item_list)
	{
		this->OnAddItemData(it, reason);
	}
}

void UKnapsack::OnAddItemData(FItemData item, FString& reason)
{
	const FItemBaseData* item_base = ITEMPOOL(GetWorld()) ? ITEMPOOL(GetWorld())->GetItemBaseDataPtr(item.item_id): nullptr;
	if (nullptr == item_base )
	{
		reason += "没有这个物品: ";
		reason += FString::FromInt(item.item_id);
		reason += " ";
		return;
	}
	
	for (auto& it : m_knapsack)
	{
		if (it.item_id == item.item_id && item_base->IsOverlapping)
		{
			it.num += item.num;
		}
		else if(it.item_id != item.item_id || !item_base->IsOverlapping)
		{
			m_knapsack.Add(item);
		}
	}
}


int UKnapsack::OnAddItemId(int32 item_id, int64 item_num, FString& reason)
{
	const FItemBaseData* item_base = ITEMPOOL(GetWorld()) ? ITEMPOOL(GetWorld())->GetItemBaseDataPtr(item_id) : nullptr;
	if (nullptr == item_base)
	{
		reason += "没有这个物品: ";
		reason += FString::FromInt(item_id);
		reason += " ";
		return -__LINE__;
	}

	int ret = -__LINE__;
	for (auto& it : m_knapsack)
	{
		if (item_id == it.item_id && item_base->IsOverlapping)
		{
			ret = 0;

			it.num += item_num;
		}
	}

	return ret;
}

void UKnapsack::OnConsumeItemList(TArray<FItemData>& item_list, FString& reason)
{
	int ret = 0;

	std::set<int32> delete_item_list_index;
	bool is_remove = false;
	int32 index = 0;
	for (auto& it : item_list) 
	{
		this->OnConsumeItemData(it, reason);
		if (!reason.IsEmpty())
		{
			ret = it.item_id;
			reason.Empty();
			reason += FString::FromInt(it.item_id);
			break;
		}

		delete_item_list_index.insert(index++);
	}

	if (0 != ret)
	{
		for (auto it : delete_item_list_index)
		{
			item_list.RemoveAt(it);
		}
	}
	else
	{
		item_list.Empty();
	}

}

void UKnapsack::OnConsumeItemData(FItemData item, FString& reason)
{
	this->OnConsumeItemId(item.item_id, item.num, reason);
}

int UKnapsack::OnConsumeItemId(int32 item_id, int64 item_num, FString& reason)
{
	if (ITEMPOOL(GetWorld()) && !ITEMPOOL(GetWorld())->FindItemById(item_id))
	{
		reason += "没有这个物品: ";
		reason += FString::FromInt(item_id);
		reason += " ";
		return -__LINE__;
	}

	int32 ret = -__LINE__;

	
	std::set<int32> delete_item_list_index;
	bool is_remove = false;

	int32 consume_index = -1;
	int32 consume_num = 0;

	TArray<FItemData> temp_knapsack = m_knapsack;
	int32 index = 0;
	for (auto & it : temp_knapsack)
	{
		if (item_id != it.item_id)
		{
			++index;
			continue;
		}

		if (item_num < it.num)
		{
			ret = 0;
			it.num -= item_num;

			//只消耗 不删除
			consume_index = index;
			consume_num = item_num;

			item_num = 0;
			break;
		}
		else
		{	
			//数量消耗完待删除
			is_remove = true;

			item_num -= it.num;
			delete_item_list_index.insert(index);
		}

		++index;
	}

	if (0 != ret)
	{
		return ret;
	}

	if (0 <= consume_index && m_knapsack.Num() > consume_index)
	{
		m_knapsack[consume_index].num -= consume_num;
	}

	if (is_remove)
	{
		for (auto it: delete_item_list_index)
		{
			m_knapsack.RemoveAt(it);
		}
	}

	return 0;
}




void UKnapsack::OnDestroyedItemByIdOrIndex(const int32 id, const int32 index /*= -1*/ )
{
	if (-1 != index && m_knapsack.IsValidIndex(index))
	{
		m_knapsack.RemoveAt(index);
		return;
	}

	for (int i = 0; i< m_knapsack.Num();++i)
	{
		if (m_knapsack[i].item_id == id)
		{
			m_knapsack.RemoveAt(i);
		}
	}
}

void UKnapsack::OnSwapItem(const int32 index_A, const int32 index_B)
{
	if (m_knapsack.IsValidIndex(index_A) && m_knapsack.IsValidIndex(index_B))
	{
		return;
	}
	m_knapsack.Swap(index_A, index_B);
}

