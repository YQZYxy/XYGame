#include "EventHandlerManager.h"
#include "YQZYLog.h"
#include "Character/YQZYCharacter.h"
#include "Struct/TaskData.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(EventHandlerManager)

UEventHandlerManager::UEventHandlerManager()
{

}

void UEventHandlerManager::Init()
{

}

static UEventHandlerManager* ptr = nullptr;
UEventHandlerManager* UEventHandlerManager::GetEventHandlerManagerInstance()
{
	if (!ptr)
	{
		ptr = NewObject<UEventHandlerManager>();
		ptr->Init();
	}

	return ptr;
}

void UEventHandlerManager::DeleteUObject()
{
	if (ptr)
	{
		ptr = nullptr;
	}
}

void UEventHandlerManager::OnTaskFinishEvent( AYQZYCharacter* role, int task_type, int task_module_type)
{
    if( nullptr == role) return;

    {
        if( ETASKTYPE_MAIN == task_type)
        {
            //role->role_data;
            return;
        }
    }
   
    

    if(ETASKMODULETYPE_ZHI_YIN > task_module_type || ETASKMODULETYPE_MAX <= task_module_type)
	{
		return ;
	}


}

void UEventHandlerManager::OnTaskSubFinishEvent( AYQZYCharacter* role, int task_type, int task_module_type)
{

}