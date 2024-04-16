void ue_parse_testing()
{
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

#if 0
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

#define path_ActorComponent \
	R"(C:\projects\Unreal\Surgo\UE\Engine\Source\Runtime\Engine\Classes\Components\ActorComponent.h)"

#if 0
	content = file_read_contents( GlobalAllocator, true, path_ActorComponent );
	CodeBody parsed_actor_component = parse_global_body( StrC { content.size, (char const*)content.data });

	for ( Code gcode : parsed_actor_component )
	{
		if ( gcode->Type == CodeT::Class )
		{
			log_fmt("\n\n");
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

#define path_SceneComponent \
	R"(C:\projects\Unreal\Surgo\UE\Engine\Source\Runtime\Engine\Classes\Components\SceneComponent.h)"

#if 0
	content = file_read_contents( GlobalAllocator, true, path_SceneComponent );
	CodeBody parsed_scene_component = parse_global_body( StrC { content.size, (char const*)content.data });

	for ( Code gcode : parsed_scene_component )
	{
		if ( gcode->Type == CodeT::Class )
		{
			log_fmt("\n\n");
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

#define path_AttributeSet \
	R"(C:\projects\Unreal\Surgo\UE\Engine\Plugins\Runtime\GameplayAbilities\Source\GameplayAbilities\Public\AttributeSet.h)"

#if 0
	content = file_read_contents( GlobalAllocator, true, path_AttributeSet );
	CodeBody parsed_attribute_set = parse_global_body( StrC { content.size, (char const*)content.data });

	for ( Code gcode : parsed_attribute_set )
	{
		if ( gcode->Type == CodeT::Class )
		{
			log_fmt("\n\n");
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
}
