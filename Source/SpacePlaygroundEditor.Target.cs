// All rights Neebula Games

using UnrealBuildTool;
using System.Collections.Generic;

public class SpacePlaygroundEditorTarget : TargetRules
{
	public SpacePlaygroundEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		ExtraModuleNames.Add("SpacePlayground");
	}
}
