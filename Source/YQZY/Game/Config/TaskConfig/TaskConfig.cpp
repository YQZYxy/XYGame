// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/Config/TaskConfig/TaskConfig.h"
#include "YQZYLog.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(TaskConfig)

bool UTaskConfig::Init(const FName& path, FString& err)
{
	m_main_task_map.Reset();
	m_module_task_map.Reset();

	CONFIG_INIT_FILE(InitMainTaskDataCfg);
	CONFIG_INIT_FILE(InitModuleTaskDataCfg);

	return true;
}

const FTaskData* UTaskConfig::GetMainTaskCfg(int id) const
{
	auto it = m_main_task_map.Find(id);
	if (!it)
	{
		return nullptr;
	}

	return it;
}

const FTaskData* UTaskConfig::GetModuleTaskCfg(int id) const
{
	auto it = m_module_task_map.Find(id);
	if (!it)
	{
		return nullptr;
	}

	return it;
}

bool UTaskConfig::InitMainTaskDataCfg(const FName& path, FString& err)
{
	GET_CONFIG_ROWNAMES("MainTaskConfig", ContextString, RowNames);
	for (auto& name : RowNames)
	{
		FTaskData* pRow = DataTable->FindRow<FTaskData>(name, ContextString);
		if (nullptr == pRow)
		{
			CONFIG_ERROR(name.ToString());
			return false;
		}

		if (pRow->id < 0 || pRow->pre_task < 0 || pRow->stage < 0)
		{
			LogError(" %s --- RowName:%s, ID:%d, pre_task:%d stage:%d", __FUNCTION__, *(name.ToString()), pRow->id, pRow->pre_task,pRow->stage);
			return false;
		}

		if(m_main_task_map.Find(pRow->id)) continue;
		m_main_task_map.Add(pRow->id, *pRow);
	}

	return true;
}


bool UTaskConfig::InitModuleTaskDataCfg(const FName& path, FString& err)
{
	GET_CONFIG_ROWNAMES("TaskConfig", ContextString, RowNames);

	for (auto& name : RowNames)
	{
		FTaskData* pRow = DataTable->FindRow<FTaskData>(name, ContextString);
		if (nullptr == pRow)
		{
			CONFIG_ERROR(name.ToString());
			return false;
		}

		if (pRow->id < 0 || pRow->pre_task < 0 || pRow->stage < 0)
		{
			LogError(" %s --- RowName:%s, ID:%d, pre_task:%d stage:%d", __FUNCTION__, *(name.ToString()), pRow->id, pRow->pre_task,pRow->stage);
			return false;
		}

		if(m_module_task_map.Find(pRow->id)) continue;

		m_module_task_map.Add(pRow->id, *pRow);
	}

	return true;
}