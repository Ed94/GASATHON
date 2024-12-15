// Used in the GasaGen.cpp translation unit
#if GASA_INTELLISENSE_DIRECTIVES
#pragma once
#include "gen.hpp"
// #include "GasaGenCommon.cpp"
using namespace gen;
#endif

// Program assumes its working directory is the project
#define path_root                ""
#define path_project             path_root        "Project/"
#define path_source              path_project     "Source/"
#define path_config              path_source      "Config/"
#define path_module_gasa         path_source      "Gasa/"
#define path_gasa_ability_system path_module_gasa "AbilitySystem/"
#define path_gasa_actors         path_module_gasa "Actors/"
#define path_gasa_characters     path_module_gasa "Characters/"
#define path_gasa_game           path_module_gasa "Game/"
#define path_gasa_ui             path_module_gasa "UI/"

constexpr Str str_DECLARE_CLASS                                         = txt("DECLARE_CLASS");
constexpr Str str_DECLARE_DELEGATE_RetVal_OneParam                      = txt("DECLARE_DELEGATE_RetVal_OneParam");
constexpr Str str_DECLARE_DELEGATE_RetVal_ThreeParams                   = txt("DECLARE_DELEGATE_RetVal_ThreeParams");
constexpr Str str_DECLARE_DELEGATE_SixParams                            = txt("DECLARE_DELEGATE_SixParams");
constexpr Str str_DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam           = txt("DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam");
constexpr Str str_DECLARE_DYNAMIC_MULTICAST_SPARSE_DELEGATE_FiveParams  = txt("DECLARE_DYNAMIC_MULTICAST_SPARSE_DELEGATE_FiveParams");
constexpr Str str_DECLARE_DYNAMIC_MULTICAST_SPARSE_DELEGATE_FourParams  = txt("DECLARE_DYNAMIC_MULTICAST_SPARSE_DELEGATE_FourParams");
constexpr Str str_DECLARE_DYNAMIC_MULTICAST_SPARSE_DELEGATE_NineParams  = txt("DECLARE_DYNAMIC_MULTICAST_SPARSE_DELEGATE_NineParams");
constexpr Str str_DECLARE_DYNAMIC_MULTICAST_SPARSE_DELEGATE_OneParam    = txt("DECLARE_DYNAMIC_MULTICAST_SPARSE_DELEGATE_OneParam");
constexpr Str str_DECLARE_DYNAMIC_MULTICAST_SPARSE_DELEGATE_SevenParams = txt("DECLARE_DYNAMIC_MULTICAST_SPARSE_DELEGATE_SevenParams");
constexpr Str str_DECLARE_DYNAMIC_MULTICAST_SPARSE_DELEGATE_TwoParams   = txt("DECLARE_DYNAMIC_MULTICAST_SPARSE_DELEGATE_TwoParams");
constexpr Str str_DECLARE_EVENT_ThreeParams                             = txt("DECLARE_EVENT_ThreeParams");
constexpr Str str_DECLARE_EVENT_TwoParams                               = txt("DECLARE_EVENT_TwoParams");
constexpr Str str_DECLARE_FUNCTION                                      = txt("DECLARE_FUNCTION");
constexpr Str str_DECLARE_LOG_CATEGORY_EXTERN                           = txt("DECLARE_LOG_CATEGORY_EXTERN");
constexpr Str str_DECLARE_MULTICAST_DELEGATE_OneParam                   = txt("DECLARE_MULTICAST_DELEGATE_OneParam");
constexpr Str str_DECLARE_MULTICAST_DELEGATE_ThreeParams                = txt("DECLARE_MULTICAST_DELEGATE_ThreeParams");
constexpr Str str_DECLARE_MULTICAST_DELEGATE_TwoParams                  = txt("DECLARE_MULTICAST_DELEGATE_TwoParams");
constexpr Str str_DECLARE_TS_MULTICAST_DELEGATE_OneParam                = txt("DECLARE_TS_MULTICAST_DELEGATE_OneParam");
constexpr Str str_DECLARE_TS_MULTICAST_DELEGATE_TwoParams               = txt("DECLARE_TS_MULTICAST_DELEGATE_TwoParams");
constexpr Str str_DECLARE_TS_MULTICAST_DELEGATE_ThreeParams             = txt("DECLARE_TS_MULTICAST_DELEGATE_ThreeParams");
constexpr Str str_DEFINE_ACTORDESC_TYPE                                 = txt("DEFINE_ACTORDESC_TYPE");
constexpr Str str_DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL    = txt("DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL");
constexpr Str str_ENUM_CLASS_FLAGS                                      = txt("ENUM_CLASS_FLAGS");
constexpr Str str_GENERATED_BODY                                        = txt("GENERATED_BODY");
constexpr Str str_GENERATED_UCLASS_BODY                                 = txt("GENERATED_UCLASS_BODY");
constexpr Str str_GENERATED_USTRUCT_BODY                                = txt("GENERATED_USTRUCT_BODY");
constexpr Str str_PRAGMA_DISABLE_DEPRECATION_WARNINGS                   = txt("PRAGMA_DISABLE_DEPRECATION_WARNINGS");
constexpr Str str_PRAGMA_ENABLE_DEPRECATION_WARNINGS                    = txt("PRAGMA_ENABLE_DEPRECATION_WARNINGS");
constexpr Str str_PROPERTY_BINDING_IMPLEMENTATION                       = txt("PROPERTY_BINDING_IMPLEMENTATION");
constexpr Str str_RESULT_DECL                                           = txt("RESULT_DECL");
constexpr Str str_SLATE_BEGIN_ARGS                                      = txt("SLATE_BEGIN_ARGS");
constexpr Str str_SLATE_END_ARGS                                        = txt("SLATE_END_ARGS");
constexpr Str str_TEXT                                                  = txt("TEXT");
constexpr Str str_UCLASS                                                = txt("UCLASS");
constexpr Str str_UENUM                                                 = txt("UENUM");
constexpr Str str_UFUNCTION                                             = txt("UFUNCTION");
constexpr Str str_UMETA                                                 = txt("UMETA");
constexpr Str str_UPARAM                                                = txt("UPARAM");
constexpr Str str_UPROPERTY                                             = txt("UPROPERTY");
constexpr Str str_USTRUCT                                               = txt("USTRUCT");
constexpr Str str_UE_REQUIRES                                           = txt("UE_REQUIRES");
constexpr Str str_UE_DEPRECATED                                         = txt("UE_DEPRECATED");
constexpr Str str_ACTOR_HAS_LABELS                                      = txt("ACTOR_HAS_LABELS");
constexpr Str str_HIDE_ACTOR_TRANSFORM_FUNCTIONS                        = txt("HIDE_ACTOR_TRANSFORM_FUNCTIONS");
constexpr Str str_SCENECOMPONENT_QUAT_TOLERANCE                         = txt("SCENECOMPONENT_QUAT_TOLERANCE");
constexpr Str str_SCENECOMPONENT_ROTATOR_TOLERANCE                      = txt("SCENECOMPONENT_ROTATOR_TOLERANCE");
constexpr Str str_GAMEPLAYATTRIBUTE_REPNOTIFY                           = txt("GAMEPLAYATTRIBUTE_REPNOTIFY");
constexpr Str str_GAMEPLAYATTRIBUTE_PROPERTY_GETTER                     = txt("GAMEPLAYATTRIBUTE_PROPERTY_GETTER");
constexpr Str str_GAMEPLAYATTRIBUTE_VALUE_GETTER                        = txt("GAMEPLAYATTRIBUTE_VALUE_GETTER");
constexpr Str str_GAMEPLAYATTRIBUTE_VALUE_SETTER                        = txt("GAMEPLAYATTRIBUTE_VALUE_SETTER");
constexpr Str str_GAMEPLAYATTRIBUTE_VALUE_INITTER                       = txt("GAMEPLAYATTRIBUTE_VALUE_INITTER");

constexpr Str str_GASA_API = txt("GASA_API");

#pragma region Globals
// These Code objects are created before anything else after gencpp does its initializatioon
global Code UHT_GENERATED_BODY;
global Code UHT_UCLASS;
global Code UHT_UPROPERTY;
global Code UHT_USTRUCT;
global Code UModule_GASA_API;
#pragma endregion Globals

global Context ctx;

inline
CodeBody parse_file( char const* path ) {
	FileContents content = file_read_contents( ctx.Allocator_Temp, file_zero_terminate, path );
	CodeBody     code    = parse_global_body( Str {(char const*)content.data,  content.size });
	return code;
}

// inline
// CodeConstructor find_constructor( StrC parent_name, )

inline
void format_file( char const* path )
{
	// Need to execute clang format on the generated file to get it to match the original.
	#define clang_format      "clang-format "
	#define cf_format_inplace "-i "
	#define cf_style          "-style=file:" "./scripts/.clang-format "
	#define cf_verbose        "-verbose "
	StrBuilder command = StrBuilder::make( ctx.Allocator_Temp, clang_format );
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
