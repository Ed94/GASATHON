#if GASA_INTELLISENSE_DIRECTIVES
#pragma once
#define GEN_EXPOSE_BACKEND
#include "gen.hpp"
#include "gen.builder.hpp"
#include "GasaGenCommon.cpp"
#include "GasaGen_UGasaAttributeSet.cpp"
#endif

void gen_UHostWidgetController()
{
	Array<GAS_AttributeEntry> attribute_fields = get_gasa_vital_attribute_fields();

	CodeBody ori_HostWidgetController_header = parse_file(path_gasa_ui "HostWidgetController.h");
	{
		CodeBody header_body = def_body(CT_Global_Body);

		Str       str_UHostWidgetController = txt("UHostWidgetController");
		CodeClass ori_UHostWidgetController = NullCode;

		Code file_code = ori_HostWidgetController_header.begin();
		for ( ; file_code != ori_HostWidgetController_header.end(); ++ file_code )
		{
			if (s32 never_enter = 0; never_enter)
				found: break;

			switch (file_code->Type)
			{
			default:
				header_body.append(file_code);
				continue;

			case CT_Class:
				if ( ! file_code->Name.starts_with(str_UHostWidgetController))
					continue;
				ori_UHostWidgetController = cast(CodeClass, file_code);
				++ file_code;
				goto found;

			case CT_Preprocess_Include:
				header_body.append(file_code);

				if ( file_code->Content.starts_with(txt("HostWidgetController.generated.h")))
				{
					header_body.append(fmt_newline);
					header_body.append(fmt_newline);
				}
			continue;

			case CT_Untyped:
				header_body.append(file_code);

				if (file_code->Content.starts_with( txt("DECLARE_"))
				||	file_code->Content.starts_with( txt("UCLASS"))
				)
					header_body.append(fmt_newline);
			continue;
			}
		}

		CodeBody attribute_events = def_body(CT_Class_Body);
		{
			attribute_events.append( def_comment( txt("Attribute Events are generated by GasaGen/GasaGen_HostWidgetController.cpp")));
			attribute_events.append(fmt_newline);

			for ( s32 id = 0; id < attribute_fields.num(); ++id )
			{
				GAS_AttributeEntry attribute_field = attribute_fields[id];

				attribute_events.append( code_str(
					UPROPERTY(BlueprintAssignable, Category = "Attributes")
				));
				attribute_events.append(fmt_newline);
				attribute_events.append( parse_variable(
					token_fmt( "field", attribute_field.Name, stringize( FAttributeChangedSig Event_On<field>Changed; ))
				));
				attribute_events.append(fmt_newline);
			}

			for ( s32 id = 0; id < attribute_fields.num(); ++id )
			{
				StrCached attribute_field = attribute_fields[id].Name;

				attribute_events.append( parse_function(
					token_fmt( "field", attribute_field, stringize( void <field>Changed(FOnAttributeChangeData const& Data); ))
				));
			}
		}

		CodeClass new_UHostWidgetController = cast(CodeClass, ori_UHostWidgetController.duplicate());
		CodeBody  new_body                  = def_body(CT_Class_Body);
		for (Code	code = ori_UHostWidgetController->Body.begin();
					code != ori_UHostWidgetController->Body.end();
					++ code )
		{
			switch (code->Type)
			{
				default:
					new_body.append(code);
					continue;

				case CT_Preprocess_Pragma:
				{
					local_persist bool found = false;
					if (found)
					{
						new_body.append(code);
						continue;
					}

					CodePragma pragma = cast(CodePragma, code);
					if ( pragma->Content.starts_with(txt("region Attribute Events")) )
					{
						new_body.append(pragma);
						++ code;

						new_body.append(attribute_events);

						while (code->Type != CT_Preprocess_Pragma
							|| ! code->Content.starts_with(txt("endregion Attribute Events"))) 
							++ code;

						new_body.append( code );
						found = true;
					}
				}
				break;

				case CT_Untyped:
					new_body.append(code);

					if (code->Content.starts_with( txt("GENERATED_BODY")))
						new_body.append(fmt_newline);
			}
		}
		new_body.append(fmt_newline);
		new_UHostWidgetController->Body = new_body;
		header_body.append(new_UHostWidgetController);

		for (; file_code != ori_HostWidgetController_header.end(); ++ file_code)
		{
			header_body.append(file_code);
		}

		Builder header = Builder::open(path_gasa_ui "HostWidgetController.h");
		header.print(header_body);
		header.write();
		format_file(path_gasa_ui "HostWidgetController.h");
	}

	CodeBody ori_HostWidgetController_source = parse_file(path_gasa_ui "HostWidgetController.cpp");
	{
		CodeBody source_body = def_body(CT_Global_Body);

		CodeFn BroadcastInitialValues = NullCode;
		{
			CodeBody broadcast_calls = def_body(CT_Function_Body);
			for (GAS_AttributeEntry field : attribute_fields)
			{
				broadcast_calls.append( code_fmt( "field", field.Name,
					stringize( Event_On<field>Changed.Broadcast( GasaAttribs->Get<field>() ); )
				));
			}

			BroadcastInitialValues = parse_function( token_fmt(
				"broadcast_calls",   (Str)broadcast_calls.to_strbuilder(),
				"generation_notice", txt("\n// This function is managed by: GenGasa/GenGasa_HostWidgetController.cpp\n\n"),
			stringize(
				void UHostWidgetController::BroadcastInitialValues()
				{
					<generation_notice>

					UGasaAttributeSet* GasaAttribs = Cast<UGasaAttributeSet>(Data.Attributes);
					if (GasaAttribs)
					{
						<broadcast_calls>
					}

					BindCallbacksToDependencies();
				})
			));
		}

		CodeFn BindCallbacksToDependencies = NullCode;
		{
			CodeBody bindings = def_body(CT_Function_Body);
			bindings.append(fmt_newline);
			bindings.append(fmt_newline);
			for (GAS_AttributeEntry field : attribute_fields)
			{
				bindings.append( code_fmt( "field", field.Name,
				stringize(
					FOnGameplayAttributeValueChange& <field>AttributeChangedDelegate = AbilitySystem->GetGameplayAttributeValueChangeDelegate(GasaAttribs->Get<field>Attribute());
					<field>AttributeChangedDelegate.AddUObject(this, &ThisClass::<field>Changed);
				)));
				bindings.append(fmt_newline);
				bindings.append(fmt_newline);
			}

			BindCallbacksToDependencies = parse_function( token_fmt(
				"generation_notice", txt("\n// This function is managed by: GenGasa/GenGasa_HostWidgetController.cpp\n\n"),
				"bindings",          (Str)bindings.to_strbuilder(),
			stringize(
				void UHostWidgetController::BindCallbacksToDependencies()
				{
					<generation_notice>

					UGasaAbilitySystemComp* AbilitySystem = Cast<UGasaAbilitySystemComp>(Data.AbilitySystem);
					UGasaAttributeSet*      GasaAttribs   = Cast<UGasaAttributeSet>( Data.Attributes );

					<bindings>

					AbilitySystem->Event_OnEffectAppliedAssetTags.AddUObject(this, & UHostWidgetController::OnEffectAppliedAssetTags);
				})
			));
		}

		CodeBody attribute_callbacks = def_body(CT_Global_Body);
		{
			attribute_callbacks.append( def_comment(txt("Attribute Changed Callbacks are generated by GasaGen/GasaGen_HostWidgetController.cpp")));
			attribute_callbacks.append(fmt_newline);

			for ( s32 id = 0; id < attribute_fields.num(); )
			{
				StrCached attribute_field = attribute_fields[id].Name;

				attribute_callbacks.append( parse_function( token_fmt(
					"field", (Str) attribute_field,
				stringize(
					void UHostWidgetController::<field>Changed(FOnAttributeChangeData const& Attribute)
					{
						Event_On<field>Changed.Broadcast(Attribute.NewValue);
					})
				)));

				++ id;
				if ( id < attribute_fields.num() )
				{
					attribute_callbacks.append(fmt_newline);
				}
			}
		}

		for ( Code code = ori_HostWidgetController_source.begin();
			code != ori_HostWidgetController_source.end();
			++ code
		)
		{
			switch (code->Type)
			{
				case CT_Preprocess_Pragma:
				{
					local_persist bool found = false;
					if (found)
					{
						source_body.append(code);
						++ code;
						continue;
					}

					CodePragma pragma = cast(CodePragma, code);
					if ( pragma->Content.starts_with(txt("region Attribute Changed Callbacks")) )
					{
						source_body.append(fmt_newline);
						source_body.append(pragma);
						++ code;

						source_body.append(attribute_callbacks);

						while (code->Type != CT_Preprocess_Pragma
							|| ! code->Content.starts_with(txt("endregion Attribute Changed Callbacks")))
							++ code;

						found = true;
					}
				}
				break;

				case CT_Function:
					CodeFn function_def = cast(CodeFn, code);

					if (	str_are_equal(function_def->Name, BroadcastInitialValues->Name)
						&&	function_def->Params.is_equal(BroadcastInitialValues->Params))
					{
						source_body.append(BroadcastInitialValues);
						log_fmt("Swapped: %S\n", BroadcastInitialValues->Name);
						continue;
					}
					else if (str_are_equal(function_def->Name, BindCallbacksToDependencies->Name)
						&& 	function_def->Params.is_equal(BindCallbacksToDependencies->Params))
					{
						source_body.append(BindCallbacksToDependencies);
						log_fmt("Swapped: %S\n", BindCallbacksToDependencies->Name);
						continue;
					}
				break;
			}

			source_body.append(code);
		}

		Builder source = Builder::open(path_gasa_ui "HostWidgetController.cpp");
		source.print(source_body);
		source.write();
		format_file(path_gasa_ui "HostWidgetController.cpp");
	}
}
