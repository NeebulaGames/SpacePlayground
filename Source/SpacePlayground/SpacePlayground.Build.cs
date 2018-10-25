// All rights Neebula Games

using UnrealBuildTool;

public class SpacePlayground : ModuleRules
{
	public SpacePlayground(ReadOnlyTargetRules ROTargetRules) : base(ROTargetRules)
	{
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore" });

		PrivateDependencyModuleNames.AddRange(new string[] {  });
	}
}
