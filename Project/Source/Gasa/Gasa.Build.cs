using System;
using System.Collections.Generic;
using UnrealBuildTool;
using ModuleRules = UnrealBuildTool.ModuleRules;
using ReadOnlyTargetRules = UnrealBuildTool.ReadOnlyTargetRules;
using TargetRules = UnrealBuildTool.TargetRules;
using UnrealTargetConfiguration = UnrealBuildTool.UnrealTargetConfiguration;

public class Gasa : ModuleRules
{
    public Gasa(ReadOnlyTargetRules Target) : base(Target)
    {
	    bUseUnity           = false;
	    bMergeUnityFiles    = false;
	    IWYUSupport         = IWYUSupport.None;
	    PCHUsage            = PCHUsageMode.NoPCHs;
	    OptimizeCode        = CodeOptimization.Never;
	    MinCpuArchX64       = MinimumCpuArchitectureX64.AVX512;
	    IncludeOrderVersion = EngineIncludeOrderVersion.Latest;
	    
	    bCodeCoverage                      = false;
	    bDisableStaticAnalysis             = true;
	    bValidateCircularDependencies      = true;
	    bValidateFormatStrings             = false;
	    bValidateInternalApi               = false;
	    bEnableExceptions                  = false;
	    bEnableBufferSecurityChecks        = false;
	    bEnableNonInlinedGenCppWarnings    = false;
	    bEnableUndefinedIdentifierWarnings = false;
	    bIgnoreUnresolvedSymbols           = false;
	    
	    bEnableObjCAutomaticReferenceCounting = false;
	    bEnableObjCExceptions                 = false;
	    
	    var Kilobyte = 1024;
	    NumIncludedBytesPerUnityCPPOverride    = Kilobyte * 32;
	    MinFilesUsingPrecompiledHeaderOverride = 1;
	    
	    PrivatePCHHeaderFile = "GasaColdHeadersPCH.h";
	    
    #region Engine
        PrivateIncludePathModuleNames.AddRange(new string[] {
            "Core",
            "Engine",
            "EnhancedInput",
        });
        PrivateDependencyModuleNames.AddRange(new string[] {
            "Core",
            
            "AIModule",
            "CoreOnline",
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
            "OnlineSubsystem",
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
		        "CogAbility",
		        "CogAI",
		        "CogAll",
		        "CogDebug",
		        "CogDebugEditor",
		        "CogEngine",
		        "CogImgui",
		        "CogInput",
		        "CogWindow",
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
