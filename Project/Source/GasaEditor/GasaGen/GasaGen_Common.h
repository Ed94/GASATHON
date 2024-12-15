#pragma once
UE_DISABLE_OPTIMIZATION
#include "gencpp/gen.hpp"
#include "gencpp/gen.builder.hpp"
UE_ENABLE_OPTIMIZATION
using namespace gen;

// Codegen assumes its working directory is the project
#define path_scripts             "/scripts/"
#define path_project             "/Project/"
#define path_source              "/Source/"
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
constexpr Str str_LOCTEXT_NAMESPACE                                     = txt("LOCTEXT_NAMESPACE");

constexpr Str str_GASA_API = txt("GASA_API");

#pragma region Globals
extern Str Project_Path;
extern Str Root_Path;

// These Code objects are created before anything else after gencpp does its initializatioon
extern Code UHT_GENERATED_BODY;
extern Code UHT_UCLASS;
extern Code UHT_UPROPERTY;
extern Code UHT_USTRUCT;
extern Code UModule_GASA_API;

extern Context gen_ctx;
#pragma endregion Globals

inline
CodeBody parse_file( char const* path ) {
	StrBuilder
	resolved_path = StrBuilder::make(gen_ctx.Allocator_Temp, Project_Path);
	resolved_path.append(path);

	FileContents content = file_read_contents( gen_ctx.Allocator_Temp, true, resolved_path );
	CodeBody     code    = parse_global_body( Str {  (char const*)content.data, content.size });
	return code;
}

// Automatically handles resolving project path
inline
Builder gasa_builder_open(char const* path) {
	StrBuilder
	resolved_path = StrBuilder::make(gen_ctx.Allocator_Temp, Project_Path);
	resolved_path.append(path);
	return Builder::open( resolved_path );
}

// inline
// CodeConstructor find_constructor( StrC parent_name, )

inline
void format_file( char const* path, bool relative_path = true )
{
	StrBuilder
	resolved_path = StrBuilder::make_reserve(gen_ctx.Allocator_Temp, Project_Path.Len);
	if (relative_path)
		resolved_path.append(Project_Path);
	resolved_path.append(path);

	StrBuilder style_arg = StrBuilder::make(gen_ctx.Allocator_Temp, txt("-style=file:"));
	style_arg.append(Root_Path);
	style_arg.append("/scripts/.clang-format ");

	// Need to execute clang format on the generated file to get it to match the original.
	#define clang_format      "clang-format "
	#define cf_format_inplace "-i "
	#define cf_verbose        "-verbose "
	StrBuilder command = StrBuilder::make( gen_ctx.Allocator_Temp, clang_format );
	command.append( cf_format_inplace );
	command.append( cf_verbose );
	command.append( style_arg );
	command.append( resolved_path );
		log_fmt("\tRunning clang-format on file:\n");
		system( command );
		log_fmt("\tclang-format finished reformatting.\n");
	#undef cf_cmd
	#undef cf_format_inplace
	#undef cf_style
	#undef cf_verbse
}

FORCEINLINE
Str to_string( FString ue_string ) { 
	char const* ansi_str = TCHAR_TO_ANSI(*ue_string);
	return StrBuilder::make_length(gen_ctx.Allocator_Temp, ansi_str, ue_string.Len()).to_str();
}

FORCEINLINE
Str to_string( FName ue_fname ) { 
	char const* ansi_str = TCHAR_TO_ANSI(*ue_fname.ToString());
	return StrBuilder::make_length(gen_ctx.Allocator_Temp, ansi_str, ue_fname.GetStringLength()).to_str();
}

FORCEINLINE
FString to_fstring( Str string )
{
	return FString::ConstructFromPtrSize( string.Ptr, string.Len );
}
