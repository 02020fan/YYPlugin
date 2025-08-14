using UnrealBuildTool;

public class BPHTTP : ModuleRules
{
    public BPHTTP(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(
            new string[]
            {
                "Core",
            }
        );

        PrivateDependencyModuleNames.AddRange(
            new string[]
            {
                "CoreUObject",
                "Engine",
                "Slate",
                "SlateCore",
                "HeadMountedDisplay",
                "HTTP",
                "HttpServer",
            }
        );
    }
}