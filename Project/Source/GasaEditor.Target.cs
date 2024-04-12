using BuildSettingsVersion = UnrealBuildTool.BuildSettingsVersion;
using TargetInfo = UnrealBuildTool.TargetInfo;
using TargetRules = UnrealBuildTool.TargetRules;
using TargetType  = UnrealBuildTool.TargetType;

public class GasaEditorTarget : TargetRules
{
    public GasaEditorTarget(TargetInfo Target) : base(Target)
    {
        Type = TargetType.Editor;
        
        DefaultBuildSettings = BuildSettingsVersion.Latest;
        
		ExtraModuleNames.Add("Gasa");
		ExtraModuleNames.Add("GasaEditor");
    }
}
