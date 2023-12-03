// Fill out your copyright notice in the Description page of Project Settings.


#include "BPItemPool.h"
#include "YQZYLog.h"

UBPItemPool::UBPItemPool()
{

}

static UBPItemPool* ItemPool_ptr = nullptr;
UBPItemPool* UBPItemPool::Instance()
{
	if (nullptr == ItemPool_ptr)
	{
		ItemPool_ptr = NewObject<UBPItemPool>();
		if (!ItemPool_ptr->Init())
		{
			LogError("%s OnReload %d ", __FUNCTION__, __LINE__);
			ItemPool_ptr->MarkAsGarbage();
			return nullptr;
		}
		ItemPool_ptr->AddToRoot();
	}

	return ItemPool_ptr;
}


void UBPItemPool::DeleteUObject()
{
	if (nullptr != ItemPool_ptr)
	{
		ItemPool_ptr->m_item_pool.Empty();
		ItemPool_ptr->RemoveFromRoot();
		ItemPool_ptr = nullptr;
	}
}

bool UBPItemPool::OnReload()
{
	if (!ItemPool_ptr)
	{
		return false;
	}

	if (!ItemPool_ptr->Init())
	{
		return false;
	}

	return true;
}

bool UBPItemPool::Init()
{
	m_item_pool.Reset();

	UDataTable* pDataTable = LoadObject<UDataTable>(NULL, TEXT("/Game/DataTable/Item/ItemPool.ItemPool")); ///Script/Engine.DataTable'
	if (!pDataTable)
	{
		return false;
	}
	FString ContextString;
	TArray<FName> RowNames;
	RowNames = pDataTable->GetRowNames();
	for (auto& name : RowNames)
	{
		FItemBaseData* pRow = pDataTable->FindRow<FItemBaseData>(name, ContextString);
		if (nullptr == pRow)
		{
			return false;
		}

		if (pRow->item_id <= 0 || pRow->item_id >= MAX_ITEM_ID || pRow->max_num <= 0)
		{
			LogError("read by row name --- RowName:%s, ID:%d, max_num:%d  error", *(name.ToString()), pRow->item_id, pRow->max_num);
			return false;
		}

		m_item_pool.Add(pRow->item_id, *pRow);
	}
	//for (auto it : pDataTable->GetRowMap())
	//{
	//	// it.Key has the key from first column of the CSV file
	//	// it.Value has a pointer to a struct of data. You can safely cast it to your actual type, e.g FMyStruct* data = (FMyStruct*)(it.Value);
	//	FString rowName = (it.Key).ToString();
	//	FItemBaseData* pRow = (FItemBaseData*)it.Value;
	//	LogDebug("read by traversal --- RowName:%s, ID:%d, max_num:%d", *rowName, pRow->item_id,pRow->max_num);
	//}

	return true;
}

bool UBPItemPool::FindItemById(int item_id)
{
	auto it = m_item_pool.Find(item_id);
	if (!it)
	{
		return false;
	}

	return true;
}

const FItemBaseData* UBPItemPool::GetItemBaseDataPtr(int item_id)const
{
	if (m_item_pool.IsEmpty())
	{
		return nullptr;
	}

	auto it = m_item_pool.Find(item_id);
	if (!it)
	{
		return nullptr;
	}

	return it;
}

const FItemBaseData UBPItemPool::GetItemBaseData(int item_id) const
{
	FItemBaseData temp;
	if (m_item_pool.IsEmpty())
	{
		return temp;
	}

	auto it = m_item_pool.Find(item_id);
	if (!it)
	{
		return temp;
	}

	return *it;
}

