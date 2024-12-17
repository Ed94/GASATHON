#include "GasaGen.h"
#include "GasaGen_Common.h"
#include "AttributeSets.h"
#include "ChangeBPActionMenu.h"
#include "DevOptionsCache.h"

// Editor Module
#include "ChangeEditorContentList.h"
#include "GasaEditorCommon.h"

#define LOCTEXT_NAMESPACE "GasaEditor"

global Str Project_Path;
global Str Root_Path;

global Code UHT_GENERATED_BODY;
global Code UHT_UCLASS;
global Code UHT_UPROPERTY;
global Code UHT_USTRUCT;
global Code UModule_GASA_API;

global Context gen_ctx = {};

void Execute_GasaModule_Codegen()
{
	FScopedSlowTask SlowTask(100.0f, LOCTEXT("RunningGasaGen", "Running GasaGen..."));
	SlowTask.MakeDialog(false, true);  // Shows a progress dialog

	AsyncTask(ENamedThreads::AnyBackgroundHiPriTask, [&SlowTask]()
	{
		Gasa::LogEditor("Executing: Gasa Module code generation.");

		gen::init( & gen_ctx);
		FString     ue_project_path = FPaths::ConvertRelativePathToFull(FPaths::ProjectDir());
		FPaths::NormalizeDirectoryName(ue_project_path);
		char const* ue_ansi_project_path = TCHAR_TO_ANSI(*ue_project_path);

		FString     ue_root_path = FPaths::GetPath(ue_project_path);
		FPaths::NormalizeDirectoryName(ue_root_path);
		char const* ue_ansi_rooot_path = TCHAR_TO_ANSI(*ue_project_path);

		Project_Path = StrBuilder::make_length(gen_ctx.Allocator_Temp, ue_ansi_project_path, ue_project_path.Len());
		Root_Path    = StrBuilder::make_length(gen_ctx.Allocator_Temp, ue_ansi_rooot_path, ue_root_path.Len());

		// Initialize Globals
		{
		#pragma push_macro("UCLASS")
		#pragma push_macro("UPROPERTY")
		#pragma push_macro("USTRUCT")
		#pragma push_macro("GENERATED_BODY")
		#pragma push_macro("GASA_API")
		#undef UCLASS
		#undef UPROPERTY
		#undef USTRUCT
		#undef GENERATED_BODY
		#undef GASA_API
			UHT_UCLASS         = code_str(UCLASS());
			UHT_UPROPERTY      = code_str(UPROPERTY());
			UHT_USTRUCT        = code_str(USTRUCT());
			UHT_GENERATED_BODY = code_str(GENERATED_BODY()\n);
			UModule_GASA_API   = code_str(GASA_API);
		#pragma pop_macro("UCLASS")
		#pragma pop_macro("UPROPERTY")
		#pragma pop_macro("USTRUCT")
		#pragma pop_macro("GENERATED_BODY")
		#pragma pop_macro("GASA_API")
		}

		// Populate Defines
		register_macros( args(
			(Macro { str_DECLARE_CLASS,                                         MT_Statement,  MF_Functional }),
			(Macro { str_DECLARE_DELEGATE_RetVal_OneParam,                      MT_Statement,  MF_Functional }),
			(Macro { str_DECLARE_DELEGATE_RetVal_ThreeParams,                   MT_Statement,  MF_Functional }),
			(Macro { str_DECLARE_DELEGATE_SixParams,                            MT_Statement,  MF_Functional }),
			(Macro { str_DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam,           MT_Statement,  MF_Functional }),
			(Macro { str_DECLARE_DYNAMIC_MULTICAST_SPARSE_DELEGATE_FiveParams,  MT_Statement,  MF_Functional }),
			(Macro { str_DECLARE_DYNAMIC_MULTICAST_SPARSE_DELEGATE_FourParams,  MT_Statement,  MF_Functional }),
			(Macro { str_DECLARE_DYNAMIC_MULTICAST_SPARSE_DELEGATE_NineParams,  MT_Statement,  MF_Functional }),
			(Macro { str_DECLARE_DYNAMIC_MULTICAST_SPARSE_DELEGATE_OneParam,    MT_Statement,  MF_Functional }),
			(Macro { str_DECLARE_DYNAMIC_MULTICAST_SPARSE_DELEGATE_SevenParams, MT_Statement,  MF_Functional }),
			(Macro { str_DECLARE_DYNAMIC_MULTICAST_SPARSE_DELEGATE_TwoParams,   MT_Statement,  MF_Functional }),
			(Macro { str_DECLARE_EVENT_ThreeParams,                             MT_Statement,  MF_Functional }),
			(Macro { str_DECLARE_EVENT_TwoParams,                               MT_Statement,  MF_Functional }),
			(Macro { str_DECLARE_FUNCTION,                                      MT_Statement,  MF_Functional }),
			(Macro { str_DECLARE_LOG_CATEGORY_EXTERN,                           MT_Statement,  MF_Functional | MF_Allow_As_Definition }),
			(Macro { str_DECLARE_MULTICAST_DELEGATE_OneParam,                   MT_Statement,  MF_Functional }),
			(Macro { str_DECLARE_MULTICAST_DELEGATE_ThreeParams,                MT_Statement,  MF_Functional }),
			(Macro { str_DECLARE_MULTICAST_DELEGATE_TwoParams,                  MT_Statement,  MF_Functional }),
			(Macro { str_DECLARE_TS_MULTICAST_DELEGATE_OneParam,                MT_Statement,  MF_Functional }),
			(Macro { str_DECLARE_TS_MULTICAST_DELEGATE_TwoParams,               MT_Statement,  MF_Functional }),
			(Macro { str_DECLARE_TS_MULTICAST_DELEGATE_ThreeParams,             MT_Statement,  MF_Functional }),
			(Macro { str_DEFINE_ACTORDESC_TYPE,                                 MT_Statement,  MF_Functional }),
			(Macro { str_DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL,    MT_Statement,  MF_Functional }),
			(Macro { str_ENUM_CLASS_FLAGS,                                      MT_Statement,  MF_Functional }),
			(Macro { str_GENERATED_BODY,                                        MT_Statement,  MF_Functional }),
			(Macro { str_GENERATED_UCLASS_BODY,                                 MT_Statement,  MF_Functional }),
			(Macro { str_GENERATED_USTRUCT_BODY,                                MT_Statement,  MF_Functional }),
			(Macro { str_PRAGMA_DISABLE_DEPRECATION_WARNINGS,                   MT_Statement,  MF_Null | MF_Allow_As_Attribute }),
			(Macro { str_PRAGMA_ENABLE_DEPRECATION_WARNINGS,                    MT_Statement,  MF_Null | MF_Allow_As_Attribute }),
			(Macro { str_PROPERTY_BINDING_IMPLEMENTATION,                       MT_Statement,  MF_Functional }),
			(Macro { str_RESULT_DECL,                                           MT_Expression, MF_Functional }),
			(Macro { str_SLATE_BEGIN_ARGS,                                      MT_Statement,  MF_Functional | MF_Expects_Body }),
			(Macro { str_SLATE_END_ARGS,                                        MT_Statement,  MF_Functional }),
			(Macro { str_TEXT,                                                  MT_Expression, MF_Functional }),
			(Macro { str_UCLASS,                                                MT_Statement,  MF_Functional }),
			(Macro { str_UENUM,                                                 MT_Statement,  MF_Functional }),
			(Macro { str_UFUNCTION,                                             MT_Statement,  MF_Functional }),
			(Macro { str_UMETA,                                                 MT_Expression, MF_Functional }),
			(Macro { str_UPARAM,                                                MT_Expression, MF_Functional }),
			(Macro { str_UPROPERTY,                                             MT_Statement,  MF_Functional }),
			(Macro { str_USTRUCT,                                               MT_Statement,  MF_Functional }),
			(Macro { str_UE_REQUIRES,                                           MT_Expression, MF_Functional }),
			(Macro { str_UE_DEPRECATED,                                         MT_Statement,  MF_Functional | MF_Allow_As_Attribute }),
			(Macro { str_ACTOR_HAS_LABELS,                                      MT_Expression, MF_Null       }),
			(Macro { str_HIDE_ACTOR_TRANSFORM_FUNCTIONS,                        MT_Statement,  MF_Functional }),
			(Macro { str_SCENECOMPONENT_QUAT_TOLERANCE,                         MT_Expression, MF_Null       }),
			(Macro { str_SCENECOMPONENT_ROTATOR_TOLERANCE,                      MT_Expression, MF_Null       }),
			(Macro { str_GAMEPLAYATTRIBUTE_REPNOTIFY,                           MT_Statement,  MF_Functional }),
			(Macro { str_GAMEPLAYATTRIBUTE_PROPERTY_GETTER,                     MT_Statement,  MF_Functional }),
			(Macro { str_GAMEPLAYATTRIBUTE_VALUE_GETTER,                        MT_Statement,  MF_Functional }),
			(Macro { str_GAMEPLAYATTRIBUTE_VALUE_SETTER,                        MT_Statement,  MF_Functional }),
			(Macro { str_GAMEPLAYATTRIBUTE_VALUE_INITTER,                       MT_Statement,  MF_Functional }),
			(Macro { str_LOCTEXT_NAMESPACE,                                     MT_Statement,  MF_Null       })
		));

		// register_macros()

		generate_AttributeSets();
		generate_DevOptionsCache();
		// generate_HostWidgetController();
		// change_SBlueprintActionMenu_Construct();
		// change_EditorContentList();
		
		gen::deinit( & gen_ctx);
	});
}

#undef LOCTEXT_NAMESPACE
