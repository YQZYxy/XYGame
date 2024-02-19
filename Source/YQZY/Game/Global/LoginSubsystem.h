#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "LoginSubsystem.generated.h"

class S2CRoleList;

UCLASS()
class YQZY_API ULoginSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
public:	
    virtual bool ShouldCreateSubsystem(UObject* Outer) const;
	virtual void Initialize(FSubsystemCollectionBase& Collection);
	virtual void Deinitialize();

	void Login(FString Name,FString PassWord,bool QuickLogin);

};