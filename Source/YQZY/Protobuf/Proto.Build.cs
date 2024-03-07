using UnrealBuildTool;
using System.IO;

public class Proto : ModuleRules
{
	public Proto(ReadOnlyTargetRules Target) : base(Target)
	{
		Type = ModuleType.External;

        if (Target.Platform == UnrealTargetPlatform.Win64)
        {
            PublicIncludePaths.Add(Path.Combine(ModuleDirectory, "include"));
            PublicSystemLibraryPaths.Add(Path.Combine(ModuleDirectory, "lib"));
            PublicSystemLibraries.Add(Path.Combine(ModuleDirectory, "lib", "libprotobuf.lib"));
            //PublicSystemLibraries.Add(Path.Combine(ModuleDirectory, "lib", "libprotoc.lib"));


        }

        //RuntimeDependencies.Add(Path.Combine(ModuleDirectory, "lib", "libprotobuf.dll"));
        //RuntimeDependencies.Add(Path.Combine(ModuleDirectory, "lib", "libprotoc.dll"));


        //bEnableShadowVariableWarnings = false;
        ShadowVariableWarningLevel = WarningLevel.Off;
        bEnableUndefinedIdentifierWarnings = false;
        bEnableExceptions = true;

        PublicDefinitions.Add("_CRT_SECURE_NO_WARNINGS");
        PublicDefinitions.Add("GOOGLE_PROTOBUF_NO_RTTI=1");
        PublicDefinitions.Add("GOOGLE_PROTOBUF_CMAKE_BUILD");


    }

}