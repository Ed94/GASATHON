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

	Array(StrCached)& PreprocessorDefines = ctx.PreprocessorDefines;

	// Initialize Globals
	{
		UHT_UCLASS         = code_str( UCLASS() );
		UHT_UPROPERTY      = code_str( UPROPERTY() );
		UHT_USTRUCT        = code_str( USTRUCT() );
		UHT_GENERATED_BODY = code_str( GENERATED_BODY()\n );
		UModule_GASA_API   = code_str( GASA_API );
	}

	// Populate Defines
	{
		PreprocessorDefines.append( cache_str(str_DECLARE_CLASS));
		PreprocessorDefines.append( cache_str(str_DECLARE_DELEGATE_RetVal_OneParam));
		PreprocessorDefines.append( cache_str(str_DECLARE_DELEGATE_RetVal_ThreeParams));
		PreprocessorDefines.append( cache_str(str_DECLARE_DELEGATE_SixParams));
		PreprocessorDefines.append( cache_str(str_DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam));
		PreprocessorDefines.append( cache_str(str_DECLARE_DYNAMIC_MULTICAST_SPARSE_DELEGATE_FiveParams));
		PreprocessorDefines.append( cache_str(str_DECLARE_DYNAMIC_MULTICAST_SPARSE_DELEGATE_FourParams));
		PreprocessorDefines.append( cache_str(str_DECLARE_DYNAMIC_MULTICAST_SPARSE_DELEGATE_NineParams));
		PreprocessorDefines.append( cache_str(str_DECLARE_DYNAMIC_MULTICAST_SPARSE_DELEGATE_OneParam));
		PreprocessorDefines.append( cache_str(str_DECLARE_DYNAMIC_MULTICAST_SPARSE_DELEGATE_SevenParams));
		PreprocessorDefines.append( cache_str(str_DECLARE_DYNAMIC_MULTICAST_SPARSE_DELEGATE_TwoParams));
		PreprocessorDefines.append( cache_str(str_DECLARE_EVENT_ThreeParams));
		PreprocessorDefines.append( cache_str(str_DECLARE_EVENT_TwoParams));
		PreprocessorDefines.append( cache_str(str_DECLARE_FUNCTION));
		PreprocessorDefines.append( cache_str(str_DECLARE_LOG_CATEGORY_EXTERN));
		PreprocessorDefines.append( cache_str(str_DECLARE_MULTICAST_DELEGATE_OneParam));
		PreprocessorDefines.append( cache_str(str_DECLARE_MULTICAST_DELEGATE_ThreeParams));
		PreprocessorDefines.append( cache_str(str_DECLARE_MULTICAST_DELEGATE_TwoParams));
		PreprocessorDefines.append( cache_str(str_DECLARE_TS_MULTICAST_DELEGATE_OneParam));
		PreprocessorDefines.append( cache_str(str_DECLARE_TS_MULTICAST_DELEGATE_TwoParams));
		PreprocessorDefines.append( cache_str(str_DECLARE_TS_MULTICAST_DELEGATE_ThreeParams));
		PreprocessorDefines.append( cache_str(str_DEFINE_ACTORDESC_TYPE));
		PreprocessorDefines.append( cache_str(str_DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL));
		PreprocessorDefines.append( cache_str(str_ENUM_CLASS_FLAGS));
		PreprocessorDefines.append( cache_str(str_FORCEINLINE_DEBUGGABLE));
		// PreprocessorDefines.append( get_cached_string(str_FORCEINLINE));
		PreprocessorDefines.append( cache_str(str_GENERATED_BODY));
		PreprocessorDefines.append( cache_str(str_GENERATED_UCLASS_BODY));
		PreprocessorDefines.append( cache_str(str_GENERATED_USTRUCT_BODY));
		PreprocessorDefines.append( cache_str(str_PRAGMA_DISABLE_DEPRECATION_WARNINGS));
		PreprocessorDefines.append( cache_str(str_PRAGMA_ENABLE_DEPRECATION_WARNINGS));
		PreprocessorDefines.append( cache_str(str_PROPERTY_BINDING_IMPLEMENTATION));
		PreprocessorDefines.append( cache_str(str_RESULT_DECL));
		PreprocessorDefines.append( cache_str(str_SLATE_BEGIN_ARGS));
		PreprocessorDefines.append( cache_str(str_SLATE_END_ARGS));
		PreprocessorDefines.append( cache_str(str_TEXT));
		PreprocessorDefines.append( cache_str(str_UCLASS));
		PreprocessorDefines.append( cache_str(str_UENUM));
		PreprocessorDefines.append( cache_str(str_UFUNCTION));
		PreprocessorDefines.append( cache_str(str_UMETA));
		PreprocessorDefines.append( cache_str(str_UPARAM));
		PreprocessorDefines.append( cache_str(str_UPROPERTY));
		PreprocessorDefines.append( cache_str(str_USTRUCT));
		PreprocessorDefines.append( cache_str(str_UE_REQUIRES));
	}

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
