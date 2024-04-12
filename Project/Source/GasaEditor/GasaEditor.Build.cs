using ModuleRules = UnrealBuildTool.ModuleRules;
using ReadOnlyTargetRules = UnrealBuildTool.ReadOnlyTargetRules;

public class GasaEditor : ModuleRules
{
    public GasaEditor(ReadOnlyTargetRules Target) : base(Target)
    {
   #region Engine
        PrivateIncludePathModuleNames.AddRange(new string[] {
            "Core",
        });
        PrivateDependencyModuleNames.AddRange(new string[] {
            "Core",
        });
    #endregion Engine
    
		PublicIncludePathModuleNames.Add("Gasa");
    }
}
