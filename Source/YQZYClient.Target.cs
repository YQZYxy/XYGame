// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class YQZYClientTarget : TargetRules
{
	public YQZYClientTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Client;

		ExtraModuleNames.AddRange(new string[] { "YQZY" });

		YQZYTarget.ApplySharedYQZYTargetSettings(this);
	}
}
