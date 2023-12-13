// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

[SupportedPlatforms(UnrealPlatformClass.Server)]
public class YQZYServerTarget : TargetRules
{
	public YQZYServerTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Server;

		ExtraModuleNames.AddRange(new string[] { "YQZY" });

		YQZYTarget.ApplySharedYQZYTargetSettings(this);

		bUseChecksInShipping = true;
	}
}
