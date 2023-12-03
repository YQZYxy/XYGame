#include "TaskComponent.h"
#include "YQZYLog.h"
#include "Game/Config/TaskConfig/TaskConfig.h"
#include "Game/Config/LogicConfigManager.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(TaskComponent)

// Sets default values for this component's properties
UTaskComponent::UTaskComponent(): m_task_type(ETASKTYPE_MAX),m_module_task_type(ETASKMODULETYPE_MAX), m_task_id(0)
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void UTaskComponent::BeginPlay()
{
	Super::BeginPlay();

	if(ETASKTYPE_MAX == m_task_type)
	{
		LogError("%d m_task_type[%d] ",__LINE__, m_task_type);
		return;		
	}

	if(ETASKMODULETYPE_ZHI_YIN > m_module_task_type || ETASKMODULETYPE_MAX <= m_module_task_type)
	{
		LogError("%d m_module_task_type[%d] ",__LINE__, m_module_task_type);
		return;
	}

	if(0 >= m_task_id)
	{
		LogError("%d m_task_id[%d] ",__LINE__, m_task_id);
		return;
	}
	
}


// Called every frame
void UTaskComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

bool UTaskComponent::OnUnlock(const FRoleModuleParam& role_info)
{
	if(this->GetUnlock())
	{
		return false;
	}

	if(this->GetFinish())
	{
		return false;
	}

	bool ret = false;
	switch(m_task_type)
	{
	case ETASKTYPE_MAIN:
		ret = this->CheckMainTaskUnlock(role_info);
		break;

	case ETASKTYPE_MODULE:
		ret = this->CheckModuleTaskUnlock(role_info);
		break;

	case ETASKTYPE_MAX:
		{
			LogError("%d m_task_type[%d] ",__LINE__, m_task_type);
			return false;
		}
		
	default:
		ret = true;
		break;
	}

	if(!ret)
	{
		return false;
	}

	this->SetUnlock();
	this->OnUnlockBpEvent();
	return true;
}

bool UTaskComponent::CheckMainTaskUnlock(const FRoleModuleParam& role_info)
{
	if(role_info.role_task_info.mian_task_id < m_task_id)
	{
		return false;
	}

	return true;
}

bool UTaskComponent::CheckModuleTaskUnlock(const FRoleModuleParam& role_info)
{
	if(ETASKMODULETYPE_ZHI_YIN > m_module_task_type || ETASKMODULETYPE_MAX <= m_module_task_type)
	{
		return false;
	}

	UTaskConfig* config = LCMCFG->GetUTaskConfig();
	if(nullptr == config)
	{
		return false;
	}
	const FTaskData* cfg = config->GetModuleTaskCfg(m_task_id);
	if(nullptr == cfg)
	{
		return false;
	}

	int param = 0;
	switch(cfg->param1)
	{
	case ETASKCONDITIONSTYPE_NOT_VALID:
		param = 10;
		break;

	default:
		break;
	}
	if(cfg->param2 > param)
	{
		return false;
	}
	
	if(ETASKMODULETYPE_ZHI_YIN > cfg->pre_task || ETASKMODULETYPE_MAX <= cfg->pre_task)
	{
		return false;
	}

	if( !role_info.role_task_info.task_info[cfg->pre_task].finish)
	{
		return false;
	}

	return true;
}

bool UTaskComponent::OnTaskFinish()
{
	if(!this->GetUnlock())
	{
		return false;
	}

	if(this->GetFinish())
	{
		return false;
	}

	bool ret = false;
	switch(m_task_type)
	{
	case ETASKTYPE_MAIN_SUB:
	case ETASKTYPE_MODULE_SUB:
		ret = true;
		break;

	case ETASKTYPE_MAX:
		{
			LogError("%d m_task_type[%d] ",__LINE__, m_task_type);
			return false;
		}

	default:
		ret = this->CheckTaskByConfig(m_task_type);
		break;
	}

	if(!ret)
	{
		return false;
	}

	this->SetFinish();
	this->OnTaskFinishBpEvent();
	return true;
}

bool UTaskComponent::OnTaskSubFinish()
{
	if(!this->GetUnlock())
	{
		return false;
	}
	if(this->GetFinish())
	{
		return false;
	}

	m_task_info.stage += 1;

	this->OnTaskSubFinishBpEvent();
	return true;
}

bool UTaskComponent::CheckTaskByConfig( ETaskType type)
{
	if(!this->GetUnlock())
	{
		return false;
	}

	if(this->GetFinish())
	{
		return false;
	}

	if (ETASKTYPE_MAIN_SUB > type || ETASKTYPE_MAX <= type)
	{
		return false;
	}

	UTaskConfig* config =  LCMCFG->GetUTaskConfig();
	if(nullptr == config)
	{
		return false;
	}

	const FTaskData* cfg;
	cfg = nullptr;
	switch(type)
	{
		case ETASKTYPE_MAIN:
			cfg = config->GetMainTaskCfg(m_task_id);
		break;
		case ETASKTYPE_MODULE:
			cfg = config->GetModuleTaskCfg(m_task_id);
		break;
	}
	if(nullptr == cfg)
	{
		return false;
	}

	if(cfg->stage != m_task_info.stage)
	{
		return false;
	}

	return true;
}

