// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include "TaskData.generated.h"

UENUM(BlueprintType)
enum ETaskConditionsType:int
{
	ETASKCONDITIONSTYPE_NOT_VALID,
	
	ETASKCONDITIONSTYPE_MAX,
};

UENUM(BlueprintType)
enum ETaskType : int
{
	ETASKTYPE_MAIN_SUB,			//主支
	ETASKTYPE_MAIN,				//主
	ETASKTYPE_MODULE_SUB,		//
	ETASKTYPE_MODULE,
	
	ETASKTYPE_MAX,
};

UENUM(BlueprintType)
enum ETaskModuleType : int
{
	ETASKMODULETYPE_ZHI_YIN UMETA(DisplayName="ZhiYin"),

	ETASKMODULETYPE_MAX,
};
static const int  TASK_MODULE_TYPE_MAX = 256;

USTRUCT(BlueprintType)
struct YQZY_API FTaskInfo
{
	GENERATED_BODY()
public:
	FTaskInfo() { this->Reset(); }// :type(0), item_id(0), num(0), overlap(1)
	void Reset() 
	{
		finish = false;
		unlock = false;
		stage = 0;
		param1 = 0;
		param2 = 0;
		param3 = 0;
	}

	bool finish;
	bool unlock;
	short stage;
	
	int param1;
	short param2;
	short param3;
};

static const int32 MAIN_TASK_MAX = 128;
USTRUCT(BlueprintType)
struct YQZY_API FRoleTaskInfoParam
{
	GENERATED_BODY()
public:
	FRoleTaskInfoParam() { this->Reset(); }

	void Reset() 
	{
		mian_task_id = 0;
		mian_task_info.Reset();
		for (auto& it: task_info)
		{
			it.Reset();
		}
	}

	 bool SetMianTaskFinish(const int id, int next_id)
	{
		if(id != mian_task_id) return false;
		mian_task_id = next_id;
		mian_task_info.Reset();
		return true;
	}

	 bool SetMianTaskSubFinish(const int id)
	{
		if(id != mian_task_id) return false;
		mian_task_info.stage += 1;
		return true;
	}	

	 int GetMianTaskSubStage() { return mian_task_info.stage;}	

	int32_t mian_task_id; 
	FTaskInfo mian_task_info;
	FTaskInfo task_info[TASK_MODULE_TYPE_MAX];
};
