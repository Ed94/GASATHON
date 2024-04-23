#define GEN_DEFINE_LIBRARY_CODE_CONSTANTS
#define GEN_ENFORCE_STRONG_CODE_TYPES
#define GEN_EXPOSE_BACKEND
// #define GEN_DEFINE_ATTRIBUTE_TOKENS
#define GEN_IMPLEMENTATION
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
	gen::init();
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
	{
		PreprocessorDefines.append( get_cached_string(str_DECLARE_CLASS));
		PreprocessorDefines.append( get_cached_string(str_DECLARE_DELEGATE_RetVal_OneParam));
		PreprocessorDefines.append( get_cached_string(str_DECLARE_DELEGATE_RetVal_ThreeParams));
		PreprocessorDefines.append( get_cached_string(str_DECLARE_DELEGATE_SixParams));
		PreprocessorDefines.append( get_cached_string(str_DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam));
		PreprocessorDefines.append( get_cached_string(str_DECLARE_DYNAMIC_MULTICAST_SPARSE_DELEGATE_FiveParams));
		PreprocessorDefines.append( get_cached_string(str_DECLARE_DYNAMIC_MULTICAST_SPARSE_DELEGATE_FourParams));
		PreprocessorDefines.append( get_cached_string(str_DECLARE_DYNAMIC_MULTICAST_SPARSE_DELEGATE_NineParams));
		PreprocessorDefines.append( get_cached_string(str_DECLARE_DYNAMIC_MULTICAST_SPARSE_DELEGATE_OneParam));
		PreprocessorDefines.append( get_cached_string(str_DECLARE_DYNAMIC_MULTICAST_SPARSE_DELEGATE_SevenParams));
		PreprocessorDefines.append( get_cached_string(str_DECLARE_DYNAMIC_MULTICAST_SPARSE_DELEGATE_TwoParams));
		PreprocessorDefines.append( get_cached_string(str_DECLARE_EVENT_ThreeParams));
		PreprocessorDefines.append( get_cached_string(str_DECLARE_EVENT_TwoParams));
		PreprocessorDefines.append( get_cached_string(str_DECLARE_FUNCTION));
		PreprocessorDefines.append( get_cached_string(str_DECLARE_LOG_CATEGORY_EXTERN));
		PreprocessorDefines.append( get_cached_string(str_DECLARE_MULTICAST_DELEGATE_OneParam));
		PreprocessorDefines.append( get_cached_string(str_DECLARE_MULTICAST_DELEGATE_ThreeParams));
		PreprocessorDefines.append( get_cached_string(str_DECLARE_MULTICAST_DELEGATE_TwoParams));
		PreprocessorDefines.append( get_cached_string(str_DEFINE_ACTORDESC_TYPE));
		PreprocessorDefines.append( get_cached_string(str_DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL));
		PreprocessorDefines.append( get_cached_string(str_ENUM_CLASS_FLAGS));
		PreprocessorDefines.append( get_cached_string(str_FORCEINLINE_DEBUGGABLE));
		// PreprocessorDefines.append( get_cached_string(str_FORCEINLINE));
		PreprocessorDefines.append( get_cached_string(str_GENERATED_BODY));
		PreprocessorDefines.append( get_cached_string(str_GENERATED_UCLASS_BODY));
		PreprocessorDefines.append( get_cached_string(str_GENERATED_USTRUCT_BODY));
		PreprocessorDefines.append( get_cached_string(str_PRAGMA_DISABLE_DEPRECATION_WARNINGS));
		PreprocessorDefines.append( get_cached_string(str_PRAGMA_ENABLE_DEPRECATION_WARNINGS));
		PreprocessorDefines.append( get_cached_string(str_PROPERTY_BINDING_IMPLEMENTATION));
		PreprocessorDefines.append( get_cached_string(str_RESULT_DECL));
		PreprocessorDefines.append( get_cached_string(str_SLATE_BEGIN_ARGS));
		PreprocessorDefines.append( get_cached_string(str_SLATE_END_ARGS));
		PreprocessorDefines.append( get_cached_string(str_TEXT));
		PreprocessorDefines.append( get_cached_string(str_UCLASS));
		PreprocessorDefines.append( get_cached_string(str_UENUM));
		PreprocessorDefines.append( get_cached_string(str_UFUNCTION));
		PreprocessorDefines.append( get_cached_string(str_UMETA));
		PreprocessorDefines.append( get_cached_string(str_UPARAM));
		PreprocessorDefines.append( get_cached_string(str_UPROPERTY));
		PreprocessorDefines.append( get_cached_string(str_USTRUCT));
	}

	gen_UGasaAttributeSet();
	gen_FGasaDevOptionsCache();
	gen_UHostWidgetController();
	// gen_netslime_interfaces();

	// One offs
	if (0)
	{
		ue_parse_testing();
		swap_SBlueprintActionMenu_Construct();
	}
	return 0;
}
