#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "TcpSocketSubsystem.generated.h"

class AYQZYCharacter;

UCLASS(Config = Game)
class YQZY_API UTcpSocketSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
public:
    virtual bool ShouldCreateSubsystem(UObject* Outer) const;
	virtual void Initialize(FSubsystemCollectionBase& Collection);
	virtual void Deinitialize();

public:
    void OnTest();




public:

private:

};
