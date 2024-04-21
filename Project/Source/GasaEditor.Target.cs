using System;
using System.Diagnostics;
using System.IO;
using System.Runtime;
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
        
        bUseUnityBuild = true;
        // bUseXGEController = false;
        
		ExtraModuleNames.Add("Gasa");
		ExtraModuleNames.Add("GasaEditor");
		
		DirectoryInfo di_uproject = new DirectoryInfo(Path.GetDirectoryName(ProjectFile.ToString())).Parent;
		string path_uproject    = di_uproject.FullName;
		string path_scripts     = Path.Combine(path_uproject, "scripts");
		string ps_gen_pass_gasa = Path.Combine(path_scripts, "gen_pass_gasa.ps1");
    }
}
