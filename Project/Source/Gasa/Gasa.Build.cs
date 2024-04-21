using System;
using System.Collections.Generic;

using ModuleRules = UnrealBuildTool.ModuleRules;
using ReadOnlyTargetRules = UnrealBuildTool.ReadOnlyTargetRules;
using TargetRules = UnrealBuildTool.TargetRules;
using UnrealTargetConfiguration = UnrealBuildTool.UnrealTargetConfiguration;

public class Gasa : ModuleRules
{
    public Gasa(ReadOnlyTargetRules Target) : base(Target)
    {
	    bUseUnity = false;
	    
    #region Engine
        PrivateIncludePathModuleNames.AddRange(new string[] {
            "Core",
            "Engine",
            "EnhancedInput",
        });
        PrivateDependencyModuleNames.AddRange(new string[] {
            "Core",
            
            "AIModule",
            "CoreUObject", 
            "DeveloperSettings",
            "Engine", 
            "EnhancedInput",
            "GameplayAbilities",
            "GameplayTags",
            "GameplayTasks",
            "InputCore", 
            "NetCore",
            "Niagara",
            "SlateCore",
            "UMG", 
        });
        
        if (Target.bBuildEditor)
        {
	        PrivateDependencyModuleNames.AddRange( new string[] {
		        "UnrealEd",
				"UMGEditor",
			});
        }
	#endregion Engine
    
    #region Plugins
		if (Target.Configuration != UnrealTargetConfiguration.Shipping && Target.Type != TargetRules.TargetType.Server)
        {
	        PrivateDefinitions.AddRange(new string[]
	        {
		        "ENABLE_COG=true",
	        });
	       
	        PrivateIncludePathModuleNames.AddRange( new string[]
	        {
		        "CogCommon",
	        });
            PrivateDependencyModuleNames.AddRange(new string[]
            {
	            // "UE_ImGui",
	            "CogCommon",
                "CogAbility",
                "CogAI",
                "CogAll",
                "CogDebug",
                "CogEngine",
                "CogImgui",
                "CogInput",
                "CogWindow",
            });
        }
    #endregion Plugins
    
		PublicIncludePaths.Add("Gasa");
		PublicIncludePathModuleNames.Add("Gasa");
    }
}
