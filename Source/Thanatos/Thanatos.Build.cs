using UnrealBuildTool;

public class Thanatos : ModuleRules
{
	public Thanatos(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange([
			"Core", 
			"CoreUObject", 
			"Engine", 
			"InputCore"
		]);
		
		PrivateDependencyModuleNames.AddRange([
			"GameplayTags",
			"GameplayAbilities"
		]);
	}
}
