// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Game/Struct/RoleModuleData.h"
#include "Game/Struct/TaskData.h"
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TaskComponent.generated.h"



UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class YQZY_API UTaskComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTaskComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable, Category = "AYQZY_TaskComp")
	bool OnUnlock(const FRoleModuleParam& role_info);
	UFUNCTION(BlueprintImplementableEvent, Category = "AYQZY_TaskComp")
	void OnUnlockBpEvent();

	UFUNCTION(BlueprintCallable, Category = "AYQZY_TaskComp")
	bool OnTaskFinish();
	UFUNCTION(BlueprintImplementableEvent, Category = "AYQZY_TaskComp")
	void OnTaskFinishBpEvent();

	UFUNCTION(BlueprintCallable, Category = "AYQZY_TaskComp")
	bool OnTaskSubFinish();
	UFUNCTION(BlueprintImplementableEvent, Category = "AYQZY_TaskComp")
	void OnTaskSubFinishBpEvent();



	bool CheckTaskByConfig(ETaskType type);
	


private:
	inline void SetUnlock() { m_task_info.unlock = true; }
	inline bool GetUnlock() {return m_task_info.unlock; }

	inline void SetFinish() { m_task_info.finish = true; }
	inline bool GetFinish() { return m_task_info.finish; }

	inline short GetStage() { return m_task_info.stage; }
	inline int GetParam1() { return m_task_info.param1; }
	inline short GetParam2() { return m_task_info.param2; }
	inline short GetParam3() { return m_task_info.param3; }

	bool CheckMainTaskUnlock(const FRoleModuleParam& role_info);
	bool CheckModuleTaskUnlock(const FRoleModuleParam& role_info);
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AYQZY_TaskComp")
	TEnumAsByte<ETaskType> m_task_type;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AYQZY_TaskComp")
	TEnumAsByte<ETaskModuleType> m_module_task_type;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AYQZY_TaskComp")
	int32 m_task_id;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AYQZY_TaskComp")
	FTaskInfo m_task_info;
};
