// All rights Neebula Games

using UnrealBuildTool;
using System.Collections.Generic;

public class SpacePlaygroundTarget : TargetRules
{
	public SpacePlaygroundTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		ExtraModuleNames.Add("SpacePlayground");
	}
}
