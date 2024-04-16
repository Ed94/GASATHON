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
#include "GasaGen_UGasaAttributeSet.cpp"


int gen_main()
{
	gen::init();
	log_fmt("Generating code for the Gasa module");

	// Initialize Globals
	umeta_uclass         = code_str( UCLASS() );
	umeta_generated_body = code_str( GENERATED_BODY() );
	gasa_api             = code_str( GASA_API );

	StrC str_generated_body                                        = txt("GENERATED_BODY(");
	StrC str_generated_uclass_body                                 = txt("GENERATED_UCLASS_BODY(");
	StrC str_property_binding_impl                                 = txt("PROPERTY_BINDING_IMPLEMENTATION");
	StrC str_uclass                                                = txt("UCLASS(");
	StrC str_ufunction                                             = txt("UFUNCTION(");
	StrC str_uproperty                                             = txt("UPROPERTY(");
	StrC str_declare_log_category_extern                           = txt("DECLARE_LOG_CATEGORY_EXTERN(");
	StrC str_enum_class_flags                                      = txt("ENUM_CLASS_FLAGS(");
	StrC str_declare_class                                         = txt("DECLARE_CLASS(");
	StrC str_define_default_object_initializer_constructor_call    = txt("DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(");
	StrC str_macro_text                                            = txt("TEXT(");
	StrC str_declare_multicast_delegate_one_parameter              = txt("DECLARE_MULTICAST_DELEGATE_OneParam(");
	StrC str_declare_multicast_delegate_two_parameter              = txt("DECLARE_MULTICAST_DELEGATE_TwoParams(");
	StrC str_declare_multicast_delegate_three_parameter            = txt("DECLARE_MULTICAST_DELEGATE_ThreeParams(");
	StrC str_declare_delegate_retval_one_param                     = txt("DECLARE_DELEGATE_RetVal_OneParam(");
	StrC str_declare_function                                      = txt("DECLARE_FUNCTION(");
	StrC str_result_decl                                           = txt("RESULT_DECL");
	StrC str_property_binding_implementation                       = txt("PROPERTY_BINDING_IMPLEMENTATION(");
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

	PreprocessorDefines.append( get_cached_string(str_generated_body));
	PreprocessorDefines.append( get_cached_string(str_generated_uclass_body));
	PreprocessorDefines.append( get_cached_string(str_property_binding_impl));
	// PreprocessorDefines.append( get_cached_string(str_ue_deprecated));
	PreprocessorDefines.append( get_cached_string(str_uclass));
	PreprocessorDefines.append( get_cached_string(str_ufunction));
	PreprocessorDefines.append( get_cached_string(str_uproperty));
	// PreprocessorDefines.append( get_cached_string(str_umg_api));
	PreprocessorDefines.append( get_cached_string(str_declare_log_category_extern));
	PreprocessorDefines.append( get_cached_string(str_enum_class_flags));
	PreprocessorDefines.append( get_cached_string(str_declare_class));
	PreprocessorDefines.append( get_cached_string(str_define_default_object_initializer_constructor_call));
	// PreprocessorDefines.append( get_cached_string(str_core_object_api));
	PreprocessorDefines.append( get_cached_string(str_macro_text));
	PreprocessorDefines.append( get_cached_string(str_declare_multicast_delegate_one_parameter));
	PreprocessorDefines.append( get_cached_string(str_declare_multicast_delegate_two_parameter));
	PreprocessorDefines.append( get_cached_string(str_declare_multicast_delegate_three_parameter));
	PreprocessorDefines.append( get_cached_string(str_declare_delegate_retval_one_param));
	PreprocessorDefines.append( get_cached_string(str_declare_function));
	PreprocessorDefines.append( get_cached_string(str_result_decl));
	PreprocessorDefines.append( get_cached_string(str_property_binding_implementation));
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
	// PreprocessorDefines.append( get_cached_string(str_ENGINE_API));
	PreprocessorDefines.append( get_cached_string(str_PRAGMA_DISABLE_DEPRECATION_WARNINGS));
	PreprocessorDefines.append( get_cached_string(str_PRAGMA_ENABLE_DEPRECATION_WARNINGS));
	PreprocessorDefines.append( get_cached_string(str_DEFINE_ACTORDESC_TYPE));
	PreprocessorDefines.append( get_cached_string(str_DECLARE_DYNAMIC_MULTICAST_SPARSE_DELEGATE_TwoParams));
	PreprocessorDefines.append( get_cached_string(str_DECLARE_DYNAMIC_MULTICAST_SPARSE_DELEGATE_OneParam));
	PreprocessorDefines.append( get_cached_string(str_UPARAM));
	PreprocessorDefines.append( get_cached_string(str_FORCEINLINE_DEBUGGABLE));

	FileContents content;

#define path_UProgressBar \
	"C:/projects/Unreal/Surgo/UE/Engine/Source/Runtime/UMG/Public/Components/ProgressBar.h"

#if 0
	content = file_read_contents( GlobalAllocator, true, path_UProgressBar );
	CodeBody parsed_uprogressbar = parse_global_body( StrC { content.size, (char const*)content.data });

	log_fmt("\n\n");
	for ( Code gcode : parsed_uprogressbar )
	{
		if ( gcode->Type == CodeT::Class )
		{
			log_fmt("Class %S - Definitions:\n", gcode->Name);

			if (gcode->Body->Type != CodeT::Class_Body)
				continue;
			for ( Code class_code : gcode->Body->cast<CodeBody>() )
			{
				switch ( class_code->Type )
				{
					case CodeT::Variable:
					case CodeT::Function:
					case CodeT::Function_Fwd:
						if ( class_code->Name )
						{
							log_fmt("%s\n", class_code->Name );
							// log_fmt("%s\n", class_code->to_string() );
						}
					break;
				}
			}
		}
	}
#endif

#define path_UObject \
	R"(C:\projects\Unreal\Surgo\UE\Engine\Source\Runtime\CoreUObject\Public\UObject\Object.h)"

#if 0
	content = file_read_contents( GlobalAllocator, true, path_UObject );
	CodeBody parsed_uobject = parse_global_body( StrC { content.size, (char const*)content.data });

	log_fmt("\n\n");
	for ( Code gcode : parsed_uobject )
	{
		if ( gcode->Type == CodeT::Class )
		{
			log_fmt("Class %S - Definitions:\n", gcode->Name);
			// log_fmt("%s\n", gcode->to_string() );

			if (gcode->Body->Type != CodeT::Class_Body)
				continue;
			for ( Code class_code : gcode->Body->cast<CodeBody>() )
			{
				switch ( class_code->Type )
				{
					case CodeT::Constructor:
					case CodeT::Constructor_Fwd:
					case CodeT::Variable:
					case CodeT::Function:
					case CodeT::Function_Fwd:
						if ( class_code->Name )
						{
							log_fmt("%s\n", class_code->Name );
							// log_fmt("%s\n", class_code->to_string() );
						}
					break;
				}
			}
		}
	}
#endif

#define path_AActor \
	R"(C:\projects\Unreal\Surgo\UE\Engine\Source\Runtime\Engine\Classes\GameFramework\Actor.h)"

#if 1
	content = file_read_contents( GlobalAllocator, true, path_AActor );
	CodeBody parsed_aactor = parse_global_body( StrC { content.size, (char const*)content.data });

	log_fmt("\n\n");
	for ( Code gcode : parsed_aactor )
	{
		if ( gcode->Type == CodeT::Class )
		{
			log_fmt("Class %S - Definitions:\n", gcode->Name);

			if (gcode->Body->Type != CodeT::Class_Body)
				continue;
			for ( Code class_code : gcode->Body->cast<CodeBody>() )
			{
				switch ( class_code->Type )
				{
					case CodeT::Variable:
					case CodeT::Function:
					case CodeT::Function_Fwd:
						if ( class_code->Name )
						{
							log_fmt("%s\n", class_code->Name );
						}
					break;
				}
			}
		}
	}
#endif

	// StrC str_gasa_api = txt("GASA_API");

	gen_UGasaAttributeSet();
	return 0;
}
