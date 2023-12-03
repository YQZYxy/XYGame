#pragma once

#include "TaskData.h"
#include "CoreMinimal.h"
#include "RoleModuleData.generated.h"


USTRUCT(BlueprintType)
struct YQZY_API FRoleInfo
{
	GENERATED_BODY()
public:
	FRoleInfo() { this->Reset(); }
	void Reset() 
	{

	}
	char name[256] ;
};

USTRUCT(BlueprintType)
struct YQZY_API FRoleModuleParam
{
	GENERATED_BODY()
public:
	FRoleModuleParam() { this->Reset(); }

	void Reset() 
	{
		role_info.Reset();
		role_task_info.Reset();
	}
	FRoleInfo role_info;
	FRoleTaskInfoParam role_task_info;
};