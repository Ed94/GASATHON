#pragma once

#include "gencpp/gen.hpp"
#include "gencpp/gen.builder.hpp"
using namespace gen;

#undef check

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

constexpr StrC str_DECLARE_CLASS                                         = txt("DECLARE_CLASS(");
constexpr StrC str_DECLARE_DELEGATE_RetVal_OneParam                      = txt("DECLARE_DELEGATE_RetVal_OneParam(");
constexpr StrC str_DECLARE_DELEGATE_RetVal_ThreeParams                   = txt("DECLARE_DELEGATE_RetVal_ThreeParams(");
constexpr StrC str_DECLARE_DELEGATE_SixParams                            = txt("DECLARE_DELEGATE_SixParams(");
constexpr StrC str_DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam           = txt("DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(");
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
constexpr StrC str_DECLARE_TS_MULTICAST_DELEGATE_OneParam                = txt("DECLARE_TS_MULTICAST_DELEGATE_OneParam(");
constexpr StrC str_DECLARE_TS_MULTICAST_DELEGATE_TwoParams               = txt("DECLARE_TS_MULTICAST_DELEGATE_TwoParams(");
constexpr StrC str_DECLARE_TS_MULTICAST_DELEGATE_ThreeParams             = txt("DECLARE_TS_MULTICAST_DELEGATE_ThreeParams(");
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
constexpr StrC str_UE_REQUIRES                                           = txt("UE_REQUIRES(");

#pragma region Globals
extern String Project_Path;
extern String Root_Path;

// These Code objects are created before anything else after gencpp does its initializatioon
extern Code UHT_GENERATED_BODY;
extern Code UHT_UCLASS;
extern Code UHT_UPROPERTY;
extern Code UHT_USTRUCT;
extern Code UModule_GASA_API;
#pragma endregion Globals

inline
CodeBody parse_file( char const* path ) {
	String
	resolved_path = String::make(GlobalAllocator, StrC(Project_Path));
	resolved_path.append(path);

	FileContents content = file_read_contents( GlobalAllocator, true, resolved_path );
	CodeBody     code    = parse_global_body( StrC { content.size, (char const*)content.data });
	return code;
}

// Automatically handles resolving project path
inline
Builder builder_open(char const* path) {
	String
	resolved_path = String::make(GlobalAllocator, StrC(Project_Path));
	resolved_path.append(path);
	return Builder::open( resolved_path );
}

// inline
// CodeConstructor find_constructor( StrC parent_name, )

inline
void format_file( char const* path )
{
	String
	resolved_path = String::make(GlobalAllocator, StrC(Project_Path));
	resolved_path.append(path);

	String clang_format_path = String::make(GlobalAllocator, StrC(Root_Path));
	clang_format_path.append("/scripts/.clang-format");

	// Need to execute clang format on the generated file to get it to match the original.
	#define clang_format      "clang-format "
	#define cf_format_inplace "-i "
	#define cf_verbose        "-verbose "
	String command = String::make( GlobalAllocator, clang_format );
	command.append( cf_format_inplace );
	command.append_fmt("-style=file:%S ", *StrC(clang_format_path));
	command.append( cf_verbose );
	command.append( resolved_path );
		log_fmt("\tRunning clang-format on file:\n");
		system( command );
		log_fmt("\tclang-format finished reformatting.\n");


	FString command_fstr = FString( command.Data, command.length());
	UE_LOG(LogTemp, Log, TEXT("clang format command: %s"), *command_fstr );
	#undef cf_cmd
	#undef cf_format_inplace
	#undef cf_style
	#undef cf_verbse
}
