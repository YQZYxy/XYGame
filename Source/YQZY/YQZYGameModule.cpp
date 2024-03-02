// Copyright Epic Games, Inc. All Rights Reserved.

#include "Modules/ModuleManager.h"
#include "proto/p_role.pb.h"

class FYQZYGameModule : public FDefaultGameModuleImpl
{
	virtual void StartupModule() override
	{
		P_RoleData root;
	}

	virtual void ShutdownModule() override
	{
	}
};

IMPLEMENT_PRIMARY_GAME_MODULE(FDefaultGameModuleImpl, YQZY, "YQZY");