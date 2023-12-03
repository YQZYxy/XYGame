// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;

public class YQZY : ModuleRules
{
	public YQZY(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicIncludePaths.AddRange(
		new string[] {
                "YQZY"
		    }
        );

        PublicDependencyModuleNames.AddRange(
            new string[] {
                "Core",
                "CoreOnline",
                "CoreUObject",
                "ApplicationCore",
                "Engine",
                "PhysicsCore",
                "GameplayTags",
                "GameplayTasks",
                "GameplayAbilities",
                "AIModule",
                "ModularGameplay",
                "ModularGameplayActors",
                "DataRegistry",
                "ReplicationGraph",
                "GameFeatures",
                "SignificanceManager",
                "Hotfix",
                "CommonLoadingScreen",
                "Niagara",
                "AsyncMixin",
                "ControlFlows",
                "PropertyPath"
            }
        );

        PrivateDependencyModuleNames.AddRange(
            new string[] {
                "InputCore",
                "Slate",
                "SlateCore",
                "RenderCore",
                "DeveloperSettings",
                "EnhancedInput",
                "NetCore",
                "RHI",
                "Projects",
                "Gauntlet",
                "UMG",
                "CommonUI",
                "CommonInput",
                "GameSettings",
                "CommonGame",
                "CommonUser",
                "GameSubtitles",
                "GameplayMessageRuntime",
                "AudioMixer",
                "NetworkReplayStreaming",
                "UIExtension",
                "ClientPilot",
                "AudioModulation",
                "EngineSettings",
                "DTLSHandlerComponent",
            }
        );

        PublicDefinitions.Add("SHIPPING_DRAW_DEBUG_ERROR=1");

        SetupGameplayDebuggerSupport(Target);
        SetupIrisSupport(Target);
        // Uncomment if you are using Slate UI
        // PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

        // Uncomment if you are using online features
        // PrivateDependencyModuleNames.Add("OnlineSubsystem");

        // To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
    }
}
