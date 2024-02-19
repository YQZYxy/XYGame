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
    virtual bool ShouldCreateSubsystem(UObject* Outer) const;
	virtual void Initialize(FSubsystemCollectionBase& Collection);
	virtual void Deinitialize();

public:
    
public:
    void OnTaskFinishEvent( AYQZYCharacter* role, int task_type, int task_module_type);
    void OnTaskSubFinishEvent( AYQZYCharacter* role, int task_type, int task_module_type);

private:

};
