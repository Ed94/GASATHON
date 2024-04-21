// Used in the GasaGen.cpp translation unit
#if GASA_INTELLISENSE_DIRECTIVES
#pragma once
#include "gen.hpp"
#include "GasaGenCommon.cpp"
using namespace gen;
#endif

// Program assumes its working directory is the project
#define path_root                ""
#define path_project             path_root        "Project/"
#define path_source              path_project     "Source/"
#define path_config              path_source      "Config/"
#define path_module_gasa         path_source      "Gasa/"
#define path_gasa_ability_system path_module_gasa "AbilitySystem/"

constexpr StrC str_DECLARE_CLASS                                         = txt("DECLARE_CLASS(");
constexpr StrC str_DECLARE_DELEGATE_RetVal_OneParam                      = txt("DECLARE_DELEGATE_RetVal_OneParam(");
constexpr StrC str_DECLARE_DELEGATE_RetVal_ThreeParams                   = txt("DECLARE_DELEGATE_RetVal_ThreeParams(");
constexpr StrC str_DECLARE_DELEGATE_SixParams                            = txt("DECLARE_DELEGATE_SixParams(");
constexpr StrC str_DECLARE_DYNAMIC_MULTICAST_SPARSE_DELEGATE_FiveParams  = txt("DECLARE_DYNAMIC_MULTICAST_SPARSE_DELEGATE_FiveParams(");
constexpr StrC str_DECLARE_DYNAMIC_MULTICAST_SPARSE_DELEGATE_FourParams  = txt("DECLARE_DYNAMIC_MULTICAST_SPARSE_DELEGATE_FourParams(");
constexpr StrC str_DECLARE_DYNAMIC_MULTICAST_SPARSE_DELEGATE_NineParams  = txt("DECLARE_DYNAMIC_MULTICAST_SPARSE_DELEGATE_NineParams(");
constexpr StrC str_DECLARE_DYNAMIC_MULTICAST_SPARSE_DELEGATE_OneParam    = txt("DECLARE_DYNAMIC_MULTICAST_SPARSE_DELEGATE_OneParam(");
constexpr StrC str_DECLARE_DYNAMIC_MULTICAST_SPARSE_DELEGATE_SevenParams = txt("DECLARE_DYNAMIC_MULTICAST_SPARSE_DELEGATE_SevenParams(");
constexpr StrC str_DECLARE_DYNAMIC_MULTICAST_SPARSE_DELEGATE_TwoParams   = txt("DECLARE_DYNAMIC_MULTICAST_SPARSE_DELEGATE_TwoParams(");
constexpr StrC str_DECLARE_EVENT_ThreeParams                             = txt("DECLARE_EVENT_ThreeParams(");
constexpr StrC str_DECLARE_EVENT_TwoParams                               = txt("DECLARE_EVENT_TwoParams(");
constexpr StrC str_DECLARE_FUNCTION                                      = txt("DECLARE_FUNCTION(");
constexpr StrC str_DECLARE_LOG_CATEGORY_EXTERN                           = txt("DECLARE_LOG_CATEGORY_EXTERN(");
constexpr StrC str_DECLARE_MULTICAST_DELEGATE_OneParam                   = txt("DECLARE_MULTICAST_DELEGATE_OneParam(");
constexpr StrC str_DECLARE_MULTICAST_DELEGATE_ThreeParams                = txt("DECLARE_MULTICAST_DELEGATE_ThreeParams(");
constexpr StrC str_DECLARE_MULTICAST_DELEGATE_TwoParams                  = txt("DECLARE_MULTICAST_DELEGATE_TwoParams(");
constexpr StrC str_DEFINE_ACTORDESC_TYPE                                 = txt("DEFINE_ACTORDESC_TYPE(");
constexpr StrC str_DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL    = txt("DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(");
constexpr StrC str_ENUM_CLASS_FLAGS                                      = txt("ENUM_CLASS_FLAGS(");
// constexpr StrC str_FORCEINLINE                                           = txt("FORCEINLINE");
constexpr StrC str_FORCEINLINE_DEBUGGABLE                                = txt("FORCEINLINE_DEBUGGABLE");
constexpr StrC str_GENERATED_BODY                                        = txt("GENERATED_BODY(");
constexpr StrC str_GENERATED_UCLASS_BODY                                 = txt("GENERATED_UCLASS_BODY(");
constexpr StrC str_GENERATED_USTRUCT_BODY                                = txt("GENERATED_USTRUCT_BODY(");
constexpr StrC str_PRAGMA_DISABLE_DEPRECATION_WARNINGS                   = txt("PRAGMA_DISABLE_DEPRECATION_WARNINGS");
constexpr StrC str_PRAGMA_ENABLE_DEPRECATION_WARNINGS                    = txt("PRAGMA_ENABLE_DEPRECATION_WARNINGS");
constexpr StrC str_PROPERTY_BINDING_IMPLEMENTATION                       = txt("PROPERTY_BINDING_IMPLEMENTATION(");
constexpr StrC str_RESULT_DECL                                           = txt("RESULT_DECL");
constexpr StrC str_SLATE_BEGIN_ARGS                                      = txt("SLATE_BEGIN_ARGS(");
constexpr StrC str_SLATE_END_ARGS                                        = txt("SLATE_END_ARGS(");
constexpr StrC str_TEXT                                                  = txt("TEXT(");
constexpr StrC str_UCLASS                                                = txt("UCLASS(");
constexpr StrC str_UENUM                                                 = txt("UENUM(");
constexpr StrC str_UFUNCTION                                             = txt("UFUNCTION(");
constexpr StrC str_UMETA                                                 = txt("UMETA(");
constexpr StrC str_UPARAM                                                = txt("UPARAM(");
constexpr StrC str_UPROPERTY                                             = txt("UPROPERTY(");
constexpr StrC str_USTRUCT                                               = txt("USTRUCT(");

constexpr StrC str_GASA_API = txt("GASA_API");

#pragma region Globals
// These Code objects are created before anything else after gencpp does its initializatioon
global Code UHT_GENERATED_BODY;
global Code UHT_UCLASS;
global Code UHT_UPROPERTY;
global Code UHT_USTRUCT;
global Code UModule_GASA_API;
#pragma endregion Globals

inline
CodeBody parse_file( char const* path ) {
	FileContents content = file_read_contents( GlobalAllocator, true, path );
	CodeBody     code    = parse_global_body( StrC { content.size, (char const*)content.data });
	return code;
}

inline
void format_file( char const* path )
{
	// Need to execute clang format on the generated file to get it to match the original.
	#define clang_format      "clang-format "
	#define cf_format_inplace "-i "
	#define cf_style          "-style=file:" "./scripts/.clang-format "
	#define cf_verbose        "-verbose "
	String command = String::make( GlobalAllocator, clang_format );
	command.append( cf_format_inplace );
	command.append( cf_style );
	command.append( cf_verbose );
	command.append( path );
		log_fmt("\tRunning clang-format on file:\n");
		system( command );
		log_fmt("\tclang-format finished reformatting.\n");
	#undef cf_cmd
	#undef cf_format_inplace
	#undef cf_style
	#undef cf_verbse
}
