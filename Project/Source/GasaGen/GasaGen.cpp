#define GEN_DEFINE_LIBRARY_CODE_CONSTANTS
#define GEN_ENFORCE_STRONG_CODE_TYPES
#define GEN_EXPOSE_BACKEND
// #define GEN_DEFINE_ATTRIBUTE_TOKENS
#define GEN_IMPLEMENTATION
#include "gen.cpp"
#include "gen.builder.cpp"
#include "gen.scanner.hpp"
using namespace gen;

#include "GasaGenCommon.cpp"
#include "GasaGen_ue_parse_testing.cpp"
#include "GasaGen_UGasaAttributeSet.cpp"

int gen_main()
{
	gen::init();
	log_fmt("Generating code for the Gasa module");

	// Initialize Globals
	umeta_uclass         = code_str( UCLASS() );
	umeta_generated_body = code_str( GENERATED_BODY() );
	gasa_api             = code_str( GASA_API );

	StrC str_GENERATED_BODY                                        = txt("GENERATED_BODY(");
	StrC str_GENERATED_UCLASS_BODY                                 = txt("GENERATED_UCLASS_BODY(");
	StrC str_PROPERTY_BINDING_IMPLEMENTATION                       = txt("PROPERTY_BINDING_IMPLEMENTATION(");
	StrC str_UCLASS                                                = txt("UCLASS(");
	StrC str_UFUNCTION                                             = txt("UFUNCTION(");
	StrC str_UPROPERTY                                             = txt("UPROPERTY(");
	StrC str_DECLARE_LOG_CATEGORY_EXTERN                           = txt("DECLARE_LOG_CATEGORY_EXTERN(");
	StrC str_ENUM_CLASS_FLAGS                                      = txt("ENUM_CLASS_FLAGS(");
	StrC str_DECLARE_CLASS                                         = txt("DECLARE_CLASS(");
	StrC str_DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL    = txt("DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(");
	StrC str_TEXT                                                  = txt("TEXT(");
	StrC str_DECLARE_MULTICAST_DELEGATE_OneParam                   = txt("DECLARE_MULTICAST_DELEGATE_OneParam(");
	StrC str_DECLARE_MULTICAST_DELEGATE_TwoParams                  = txt("DECLARE_MULTICAST_DELEGATE_TwoParams(");
	StrC str_DECLARE_MULTICAST_DELEGATE_ThreeParams                = txt("DECLARE_MULTICAST_DELEGATE_ThreeParams(");
	StrC str_DECLARE_DELEGATE_RetVal_OneParam                      = txt("DECLARE_DELEGATE_RetVal_OneParam(");
	StrC str_DECLARE_FUNCTION                                      = txt("DECLARE_FUNCTION(");
	StrC str_RESULT_DECL                                           = txt("RESULT_DECL");
	StrC str_FORCEINLINE                                           = txt("FORCEINLINE");
	StrC str_UENUM                                                 = txt("UENUM(");
	StrC str_UMETA                                                 = txt("UMETA(");
	StrC str_DECLARE_DYNAMIC_MULTICAST_SPARSE_DELEGATE_FiveParams  = txt("DECLARE_DYNAMIC_MULTICAST_SPARSE_DELEGATE_FiveParams(");
	StrC str_DECLARE_DYNAMIC_MULTICAST_SPARSE_DELEGATE_SevenParams = txt("DECLARE_DYNAMIC_MULTICAST_SPARSE_DELEGATE_SevenParams(");
	StrC str_DECLARE_DYNAMIC_MULTICAST_SPARSE_DELEGATE_NineParams  = txt("DECLARE_DYNAMIC_MULTICAST_SPARSE_DELEGATE_NineParams(");
	StrC str_DECLARE_DYNAMIC_MULTICAST_SPARSE_DELEGATE_FourParams  = txt("DECLARE_DYNAMIC_MULTICAST_SPARSE_DELEGATE_FourParams(");
	StrC str_DECLARE_DELEGATE_SixParams                            = txt("DECLARE_DELEGATE_SixParams(");
	StrC str_DECLARE_EVENT_TwoParams                               = txt("DECLARE_EVENT_TwoParams(");
	StrC str_DECLARE_DELEGATE_RetVal_ThreeParams                   = txt("DECLARE_DELEGATE_RetVal_ThreeParams(");
	StrC str_PRAGMA_DISABLE_DEPRECATION_WARNINGS                   = txt("PRAGMA_DISABLE_DEPRECATION_WARNINGS");
	StrC str_PRAGMA_ENABLE_DEPRECATION_WARNINGS                    = txt("PRAGMA_ENABLE_DEPRECATION_WARNINGS");
	StrC str_DEFINE_ACTORDESC_TYPE                                 = txt("DEFINE_ACTORDESC_TYPE(");
	StrC str_DECLARE_DYNAMIC_MULTICAST_SPARSE_DELEGATE_TwoParams   = txt("DECLARE_DYNAMIC_MULTICAST_SPARSE_DELEGATE_TwoParams(");
	StrC str_DECLARE_DYNAMIC_MULTICAST_SPARSE_DELEGATE_OneParam    = txt("DECLARE_DYNAMIC_MULTICAST_SPARSE_DELEGATE_OneParam(");
	StrC str_UPARAM                                                = txt("UPARAM(");
	StrC str_FORCEINLINE_DEBUGGABLE                                = txt("FORCEINLINE_DEBUGGABLE");
	StrC str_DECLARE_EVENT_ThreeParams                             = txt("DECLARE_EVENT_ThreeParams(");
	StrC str_USTRUCT                                               = txt("USTRUCT(");
	StrC str_GENERATED_USTRUCT_BODY                                = txt("GENERATED_USTRUCT_BODY(");

	PreprocessorDefines.append( get_cached_string(str_GENERATED_BODY));
	PreprocessorDefines.append( get_cached_string(str_GENERATED_UCLASS_BODY));
	PreprocessorDefines.append( get_cached_string(str_PROPERTY_BINDING_IMPLEMENTATION));
	PreprocessorDefines.append( get_cached_string(str_UCLASS));
	PreprocessorDefines.append( get_cached_string(str_UFUNCTION));
	PreprocessorDefines.append( get_cached_string(str_UPROPERTY));
	PreprocessorDefines.append( get_cached_string(str_DECLARE_LOG_CATEGORY_EXTERN));
	PreprocessorDefines.append( get_cached_string(str_ENUM_CLASS_FLAGS));
	PreprocessorDefines.append( get_cached_string(str_DECLARE_CLASS));
	PreprocessorDefines.append( get_cached_string(str_DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL));
	PreprocessorDefines.append( get_cached_string(str_TEXT));
	PreprocessorDefines.append( get_cached_string(str_DECLARE_MULTICAST_DELEGATE_OneParam));
	PreprocessorDefines.append( get_cached_string(str_DECLARE_MULTICAST_DELEGATE_TwoParams));
	PreprocessorDefines.append( get_cached_string(str_DECLARE_MULTICAST_DELEGATE_ThreeParams));
	PreprocessorDefines.append( get_cached_string(str_DECLARE_DELEGATE_RetVal_OneParam));
	PreprocessorDefines.append( get_cached_string(str_DECLARE_FUNCTION));
	PreprocessorDefines.append( get_cached_string(str_RESULT_DECL));
	PreprocessorDefines.append( get_cached_string(str_FORCEINLINE));
	PreprocessorDefines.append( get_cached_string(str_UENUM));
	PreprocessorDefines.append( get_cached_string(str_UMETA));
	PreprocessorDefines.append( get_cached_string(str_DECLARE_DYNAMIC_MULTICAST_SPARSE_DELEGATE_FiveParams));
	PreprocessorDefines.append( get_cached_string(str_DECLARE_DYNAMIC_MULTICAST_SPARSE_DELEGATE_SevenParams));
	PreprocessorDefines.append( get_cached_string(str_DECLARE_DYNAMIC_MULTICAST_SPARSE_DELEGATE_NineParams));
	PreprocessorDefines.append( get_cached_string(str_DECLARE_DYNAMIC_MULTICAST_SPARSE_DELEGATE_FourParams));
	PreprocessorDefines.append( get_cached_string(str_DECLARE_DELEGATE_SixParams));
	PreprocessorDefines.append( get_cached_string(str_DECLARE_EVENT_TwoParams));
	PreprocessorDefines.append( get_cached_string(str_DECLARE_DELEGATE_RetVal_ThreeParams));
	PreprocessorDefines.append( get_cached_string(str_PRAGMA_DISABLE_DEPRECATION_WARNINGS));
	PreprocessorDefines.append( get_cached_string(str_PRAGMA_ENABLE_DEPRECATION_WARNINGS));
	PreprocessorDefines.append( get_cached_string(str_DEFINE_ACTORDESC_TYPE));
	PreprocessorDefines.append( get_cached_string(str_DECLARE_DYNAMIC_MULTICAST_SPARSE_DELEGATE_TwoParams));
	PreprocessorDefines.append( get_cached_string(str_DECLARE_DYNAMIC_MULTICAST_SPARSE_DELEGATE_OneParam));
	PreprocessorDefines.append( get_cached_string(str_UPARAM));
	PreprocessorDefines.append( get_cached_string(str_FORCEINLINE_DEBUGGABLE));
	PreprocessorDefines.append( get_cached_string(str_DECLARE_EVENT_ThreeParams));
	PreprocessorDefines.append( get_cached_string(str_USTRUCT));
	PreprocessorDefines.append( get_cached_string(str_GENERATED_USTRUCT_BODY));

	ue_parse_testing();

	StrC str_gasa_api = txt("GASA_API");

	gen_UGasaAttributeSet();
	return 0;
}
