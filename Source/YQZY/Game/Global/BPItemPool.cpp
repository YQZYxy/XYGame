// Fill out your copyright notice in the Description page of Project Settings.


#include "BPItemPool.h"
#include "YQZYLog.h"

UBPItemPool::UBPItemPool()
{

}

bool UBPItemPool::ShouldCreateSubsystem(UObject* Outer) const
{
	Super::ShouldCreateSubsystem(Outer);
	return true;
}

void UBPItemPool::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	this->Init();
}

void UBPItemPool::Deinitialize()
{
	Super::Deinitialize();
}

UBPItemPool* UBPItemPool::GetBPItemPool(UWorld* world)
{
	UGameInstance* GameInstance = world ? world->GetGameInstance() : nullptr;
	return GameInstance ? GameInstance->GetSubsystem<UBPItemPool>() : nullptr;
}

bool UBPItemPool::OnReload()
{

	return true;
}

bool UBPItemPool::Init()
{
	m_item_pool.Reset();

	UDataTable* pDataTable = LoadObject<UDataTable>(NULL, TEXT("/Script/Engine.DataTable'/Game/DataTable/Item/ItemPoolData.ItemPoolData'")); ///Script/Engine.DataTable'
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
			YQZYError("read by row name --- RowName:%s, ID:%d, max_num:%d  error", *(name.ToString()), pRow->item_id, pRow->max_num);
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

