using UnrealBuildTool;
using System.Collections.Generic;

public class ThanatosEditorTarget : TargetRules
{
	public ThanatosEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V6;

		ExtraModuleNames.AddRange(["Thanatos"]);
	}
}
