#define GEN_DEFINE_LIBRARY_CODE_CONSTANTS
#define GEN_ENFORCE_STRONG_CODE_TYPES
#define GEN_EXPOSE_BACKEND
// #define GEN_DEFINE_ATTRIBUTE_TOKENS
#define GEN_IMPLEMENTATION
#include "gen.dep.cpp"
#include "gen.cpp"
#include "gen.builder.cpp"
// #include "gen.scanner.hpp"
using namespace gen;

#ifdef GEN_SYSTEM_WINDOWS
	#include <process.h>
#endif

#include "GasaGenCommon.cpp"
#include "GasaGen_ue_parse_testing.cpp"
#include "GasaGen_UGasaAttributeSet.cpp"
#include "GasaGen_ChangeBPActionMenu.cpp"
#include "GasaGen_DevOptionsCache.cpp"
#include "GasaGen_HostWidgetController.cpp"
#include "GasaGen_NetSlime.cpp"

int gen_main()
{
	ctx = {};
	gen::init(& ctx);
	log_fmt("Generating code for the Gasa module\n");

	// Initialize Globals
	{
		UHT_UCLASS         = code_str( UCLASS() );
		UHT_UPROPERTY      = code_str( UPROPERTY() );
		UHT_USTRUCT        = code_str( USTRUCT() );
		UHT_GENERATED_BODY = code_str( GENERATED_BODY()\n );
		UModule_GASA_API   = code_str( GASA_API );
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
		(Macro { str_SLATE_BEGIN_ARGS,                                      MT_Statement,  MF_Functional }),
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
		(Macro { str_GAMEPLAYATTRIBUTE_VALUE_INITTER,                       MT_Statement,  MF_Functional })
	));

	// gen_UGasaAttributeSet();
	// gen_FGasaDevOptionsCache();
	// gen_UHostWidgetController();
	// gen_netslime_interfaces();

	// One offs
	if (1)
	{
		ue_parse_testing();
		//swap_SBlueprintActionMenu_Construct();
	}
	return 0;
}
