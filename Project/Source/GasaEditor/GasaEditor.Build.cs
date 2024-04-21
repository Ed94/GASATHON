using ModuleRules = UnrealBuildTool.ModuleRules;
using ReadOnlyTargetRules = UnrealBuildTool.ReadOnlyTargetRules;

public class GasaEditor : ModuleRules
{
    public GasaEditor(ReadOnlyTargetRules Target) : base(Target)
    {
   #region Engine
        PrivateIncludePathModuleNames.AddRange(new string[] {
            "Core",
            "CoreUObject",
            "Engine",
        });
        PrivateDependencyModuleNames.AddRange(new string[] {
            "Core", 
            "Engine",
            "CoreUObject",
            "PropertyEditor",
            "SlateCore",
            "Slate",
            "UMG",
            "UnrealEd",
        });
    #endregion Engine
    
		PublicIncludePaths.Add("GasaEditor");
		PrivateDependencyModuleNames.Add("Gasa");
    }
}
