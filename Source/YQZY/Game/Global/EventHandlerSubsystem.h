#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "UEventHandlerSubsystem.generated.h"

class AYQZYCharacter;

UCLASS(Config = Game)
class YQZY_API UEventHandlerSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
public:
	UEventHandlerSubsystem();
    void Init();

public:

public:
    void OnTaskFinishEvent( AYQZYCharacter* role, int task_type, int task_module_type);
    void OnTaskSubFinishEvent( AYQZYCharacter* role, int task_type, int task_module_type);

private:

};
