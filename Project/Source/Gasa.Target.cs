using BuildSettingsVersion = UnrealBuildTool.BuildSettingsVersion;
using TargetInfo = UnrealBuildTool.TargetInfo;
using TargetRules = UnrealBuildTool.TargetRules;
using TargetType = UnrealBuildTool.TargetType;

public class GasaTarget : TargetRules
{
    public GasaTarget(TargetInfo Target) : base(Target)
    {
        Type = TargetType.Game;
        DefaultBuildSettings = BuildSettingsVersion.Latest;

        ExtraModuleNames.Add("Gasa");
    }
}
