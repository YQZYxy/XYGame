// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Config/LogicConfig.h"
#include "TaskConfig.generated.h"


USTRUCT(BlueprintType)
struct YQZY_API FTaskData: public FTableRowBase
{
	GENERATED_BODY()
public:
	FTaskData() :seq(0), id(0), pre_task(0), stage(0), param1(0), param2(0) {};

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 seq;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 id;				
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 pre_task;			
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 stage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 param1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 param2;
};

UCLASS()
class YQZY_API UTaskConfig : public ULogicConfig
{
	GENERATED_BODY()
public:
	virtual bool Init(const FName& path, FString& err)override;

	const FTaskData* GetMainTaskCfg(int id) const;
	const FTaskData* GetModuleTaskCfg(int id) const;

private:
	bool InitMainTaskDataCfg(const FName& path, FString& err);
	bool InitModuleTaskDataCfg(const FName& path, FString& err);

	TMap< int,FTaskData> m_main_task_map;
	TMap< int,FTaskData> m_module_task_map;
};
