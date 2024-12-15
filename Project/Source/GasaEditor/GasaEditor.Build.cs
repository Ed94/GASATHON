using UnrealBuildTool;
using ModuleRules         = UnrealBuildTool.ModuleRules;
using ReadOnlyTargetRules = UnrealBuildTool.ReadOnlyTargetRules;

public class GasaEditor : ModuleRules
{
	public GasaEditor(ReadOnlyTargetRules Target) : base(Target)
	{
		#region Engine
		
		PrivateIncludePathModuleNames.AddRange(new string[]
		{
			"Core",
			"CoreUObject",
			"Engine",
		});
		PrivateDependencyModuleNames.AddRange(new string[]
		{
			"Core",
			"Engine",
			"CoreUObject",
			"EditorStyle",
			"PropertyEditor",
			"SlateCore",
			"Slate",
			"UMG",
			"UnrealEd",
		});
		
		#endregion Engine
		
		PublicIncludePaths.Add("GasaEditor");
		PrivateDependencyModuleNames.Add("Gasa");
		
		bWarningsAsErrors               = false;
		ShadowVariableWarningLevel      = UnrealBuildTool.WarningLevel.Off;
		UndefinedIdentifierWarningLevel = UnrealBuildTool.WarningLevel.Off;
		
		// gencpp related defines
		PublicDefinitions.Add("GEN_TIME=1");
		PublicDefinitions.Add("GEN_EXECUTION_EXPRESSION_SUPPORT=0");
		PublicDefinitions.Add("GEN_EXPOSE_BACKEND=1");
		PublicDefinitions.Add("GEN_PARSER_DISABLE_MACRO_TYPEDEF=0");
		PublicDefinitions.Add("GEN_DONT_USE_NAMESPACE=0");
		PublicDefinitions.Add("GEN_BUILD_DEBUG=1");
		PublicDefinitions.Add("GEN_SUPPORT_CPP_REFERENCES=1");
		
		OptimizeCode = CodeOptimization.Never;
	}
}
