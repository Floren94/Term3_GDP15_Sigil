using UnrealBuildTool;

public class Sigil_Lessons : ModuleRules
{
    public Sigil_Lessons(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(
            new string[]
            {
                "Core",
                "CoreUObject",
                "Engine",
                "InputCore",
                "EnhancedInput",
                "GameplayAbilities",
                "GameplayTags",
                "GameplayTasks",
                "UMG"
            }
        );
    }
}