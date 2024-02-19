#include "UEventHandlerSubsystem.h"
#include "YQZYLog.h"
#include "Character/YQZYCharacter.h"
#include "Game/Struct/TaskData.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(EventHandlerSubsystem)

UEventHandlerSubsystem::UEventHandlerSubsystem()
{

}

void UEventHandlerSubsystem::Init()
{

}

void UEventHandlerSubsystem::OnTaskFinishEvent( AYQZYCharacter* role, int task_type, int task_module_type)
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

void UEventHandlerSubsystem::OnTaskSubFinishEvent( AYQZYCharacter* role, int task_type, int task_module_type)
{

}