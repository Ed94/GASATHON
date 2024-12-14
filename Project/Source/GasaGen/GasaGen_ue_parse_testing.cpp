// Used in the GasaGen.cpp translation unit
#if GASA_INTELLISENSE_DIRECTIVES
#pragma once
#define GEN_EXPOSE_BACKEND
#include "gen.hpp"
#include "gen.builder.hpp"
#include "GasaGenCommon.cpp"
#endif

void ue_parse_testing()
{
	FileContents content;

#define path_UProgressBar \
	"C:/projects/Unreal/Surgo/UE/Engine/Source/Runtime/UMG/Public/Components/ProgressBar.h"

#if 1
	content = file_read_contents( ctx.Allocator_Temp, true, path_UProgressBar );
	CodeBody parsed_uprogressbar = parse_global_body( Str { (char const*)content.data, content.size });

	log_fmt("\n\n");
	for ( Code gcode : parsed_uprogressbar )
	{
		if ( gcode->Type == CT_Class )
		{
			log_fmt("Class %S - Definitions:\n", gcode->Name);

			if (gcode->Body->Type != CT_Class_Body)
				continue;
			for ( Code class_code : cast(CodeBody, gcode->Body) )
			{
				switch ( class_code->Type )
				{
					case CT_Variable:
					case CT_Function:
					case CT_Function_Fwd:
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

#if 1
	content = file_read_contents( ctx.Allocator_Temp, true, path_UObject );
	CodeBody parsed_uobject = parse_global_body( Str { (char const*)content.data, content.size });

	log_fmt("\n\n");
	for ( Code gcode : parsed_uobject )
	{
		if ( gcode->Type == CT_Class )
		{
			log_fmt("Class %S - Definitions:\n", gcode->Name);
			// log_fmt("%s\n", gcode->to_string() );

			if (gcode->Body->Type != CT_Class_Body)
				continue;
			for ( Code class_code : cast(CodeBody, gcode->Body) )
			{
				switch ( class_code->Type )
				{
					case CT_Constructor:
					case CT_Constructor_Fwd:
					case CT_Variable:
					case CT_Function:
					case CT_Function_Fwd:
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
	content = file_read_contents( ctx.Allocator_Temp, true, path_AActor );
	CodeBody parsed_aactor = parse_global_body( Str { (char const*)content.data, content.size });

	log_fmt("\n\n");
	for ( Code gcode : parsed_aactor )
	{
		if ( gcode->Type == CT_Class )
		{
			log_fmt("Class %S - Definitions:\n", gcode->Name);

			if (gcode->Body->Type != CT_Class_Body)
				continue;
			for ( Code class_code : cast(CodeBody, gcode->Body) )
			{
				switch ( class_code->Type )
				{
					// case CodeT::Variable:
					case CT_Function:
					case CT_Function_Fwd:
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

#define path_ActorComponent \
	R"(C:\projects\Unreal\Surgo\UE\Engine\Source\Runtime\Engine\Classes\Components\ActorComponent.h)"

#if 1
	content = file_read_contents( ctx.Allocator_Temp, true, path_ActorComponent );
	CodeBody parsed_actor_component = parse_global_body( Str { (char const*)content.data, content.size });

	for ( Code gcode : parsed_actor_component )
	{
		if ( gcode->Type == CT_Class )
		{
			log_fmt("\n\n");
			log_fmt("Class %S - Definitions:\n", gcode->Name);

			if (gcode->Body->Type != CT_Class_Body)
				continue;
			for ( Code class_code : cast(CodeBody, gcode->Body) )
			{
				switch ( class_code->Type )
				{
					case CT_Variable:
					case CT_Function:
					case CT_Function_Fwd:
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

#define path_SceneComponent \
	R"(C:\projects\Unreal\Surgo\UE\Engine\Source\Runtime\Engine\Classes\Components\SceneComponent.h)"

#if 1
	content = file_read_contents( ctx.Allocator_Temp, true, path_SceneComponent );
	CodeBody parsed_scene_component = parse_global_body( Str { (char const*)content.data, content.size });

	for ( Code gcode : parsed_scene_component )
	{
		if ( gcode->Type == CT_Class )
		{
			log_fmt("\n\n");
			log_fmt("Class %S - Definitions:\n", gcode->Name);

			if (gcode->Body->Type != CT_Class_Body)
				continue;
			for ( Code class_code : cast(CodeBody, gcode->Body) )
			{
				switch ( class_code->Type )
				{
					case CT_Variable:
					case CT_Function:
					case CT_Function_Fwd:
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

#define path_AttributeSet \
	R"(C:\projects\Unreal\Surgo\UE\Engine\Plugins\Runtime\GameplayAbilities\Source\GameplayAbilities\Public\AttributeSet.h)"

#if 1
	content = file_read_contents( ctx.Allocator_Temp, true, path_AttributeSet );
	CodeBody parsed_attribute_set = parse_global_body( Str { (char const*)content.data, content.size });

	for ( Code gcode : parsed_attribute_set )
	{
		if ( gcode->Type == CT_Class )
		{
			log_fmt("\n\n");
			log_fmt("Class %S - Definitions:\n", gcode->Name);

			if (gcode->Body->Type != CT_Class_Body)
				continue;
			for ( Code class_code : cast(CodeBody, gcode->Body) )
			{
				switch ( class_code->Type )
				{
					case CT_Variable:
					case CT_Function:
					case CT_Function_Fwd:
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
}
