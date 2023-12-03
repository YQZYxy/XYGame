// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponConfig.h"
#include "Game/Config/LogicConfigManager.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(WeaponConfig)

bool UWeaponConfig::Init(const FName& path, FString& err)
{
	item_pool.Reset();
	CONFIG_INIT_FILE(InitWeaponDataCfg);
	//InitWeaponDataCfg(path, err);

	return true;
}



bool UWeaponConfig::FindItemById(int item_id)
{
	auto it = item_pool.Contains(item_id);
	if (!it)
	{
		return false;
	}

	return true;
}



const FWeaponData UWeaponConfig::GetItemBaseData( int item_id)const
{
	FWeaponData temp;
	if (item_pool.IsEmpty())
	{
		return temp;
	}

	auto it = item_pool.Find(item_id);
	if (!it)
	{
		return temp;
	}

	return *it;
}

const FWeaponData* UWeaponConfig::GetItemBaseDataPtr(int item_id)const
{
	if (item_pool.IsEmpty())
	{
		return nullptr;
	}

	auto it = item_pool.Find(item_id);
	if (!it)
	{
		return nullptr;
	}

	return it;
}

bool UWeaponConfig::InitWeaponDataCfg(const FName& path, FString& err)
{
	GET_CONFIG_ROWNAMES("WeaponConfig1", ContextString, RowNames);

	for (auto& name : RowNames)
	{
		FWeaponData* pRow = DataTable->FindRow<FWeaponData>(name, ContextString);
		if (nullptr == pRow)
		{
			CONFIG_ERROR(name.ToString());
			return false;
		}

		//if (pRow->item_id <= 0 || pRow->item_id >= MAX_ITEM_ID || pRow->max_num <= 0)
		//{
		//	LogError("read by row name --- RowName:%s, ID:%d, max_num:%d  error", *(name.ToString()), pRow->item_id, pRow->max_num);
		//	return false;
		//}

		item_pool.Add(pRow->item_id, *pRow);
	}

	return true;
}
