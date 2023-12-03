#pragma once

#include "CoreMinimal.h"
#include "EventHandlerManager.generated.h"

class AYQZYCharacter;

#define EVENT_HANDLER UEventHandlerManager::GetEventHandlerManagerInstance()
UCLASS(Config = Game)
class YQZY_API UEventHandlerManager : public UObject
{
	GENERATED_BODY()
public:
	UEventHandlerManager();
    void Init();

public:

	UFUNCTION(BlueprintCallable, Category = "NewInstance")
	static UEventHandlerManager* GetEventHandlerManagerInstance();
	UFUNCTION(BlueprintCallable, Category = "DeleteInstance")
	static void DeleteUObject();
public:
    void OnTaskFinishEvent( AYQZYCharacter* role, int task_type, int task_module_type);
    void OnTaskSubFinishEvent( AYQZYCharacter* role, int task_type, int task_module_type);

private:

};
