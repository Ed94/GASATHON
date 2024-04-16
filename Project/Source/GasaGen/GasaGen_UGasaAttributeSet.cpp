﻿// Used in the GasaGen.cpp translation unit

void def_attribute_properties            ( CodeBody body, Array<StringCached> properties );
void def_attribute_field_on_reps         ( CodeBody body, Array<StringCached> properties );
void def_attribute_field_property_getters( CodeBody body, StrC class_name, Array<StringCached> properties );
void def_attribute_field_value_getters   ( CodeBody body, Array<StringCached> properties );
void def_attribute_field_value_setters   ( CodeBody body, Array<StringCached> properties );
void def_attribute_field_initers         ( CodeBody body, Array<StringCached> properties );
void impl_attribute_fields               ( CodeBody body, StrC class_name, Array<StringCached> properties );

void gen_UGasaAttributeSet()
{
	CodeType   type_UAttributeSet = def_type( txt("UAttributeSet") );
	CodeComment generation_notice = def_comment(txt("This was generated by GasaGen/GasaGen.cpp"));

	Array<StringCached> attribute_fields = Array<StringCached>::init( GlobalAllocator);
	attribute_fields.append( get_cached_string(txt("Health")));
	attribute_fields.append( get_cached_string(txt("MaxHealth")));
	attribute_fields.append( get_cached_string(txt("Mana")));
	attribute_fields.append( get_cached_string(txt("MaxMana")));

	StrC class_name = txt("UGasaAttributeSet");

	Builder header = Builder::open( path_gasa_ability_system "GasaAttributeSet.h");
	{
		header.print(generation_notice);
		header.print(fmt_newline);
		{
			CodeInclude Include_AttributeSet               = def_include(txt("AttributeSet.h"));
			CodeInclude Include_AbilitySystemComponent     = def_include(txt("AbilitySystemComponent.h"));
			CodeInclude Include_GasaAttributeSet_Generated = def_include(txt("GasaAttributeSet.generated.h"));

			CodeAttributes api_attribute= def_attributes( gasa_api->Name);

			CodeClass GasaAttributeSet = {};
			{
				CodeBody body = def_body( CodeT::Class_Body );
				{
					body.append( umeta_generated_body);
					body.append( fmt_newline);
					body.append( access_public );

					def_attribute_properties( body, attribute_fields);

					body.append(fmt_newline);
					body.append( def_constructor() );

					def_attribute_field_on_reps( body, attribute_fields);

					body.append(fmt_newline);

					body.append( fmt_newline );
					body.append( def_pragma(code( region Getters )));
					def_attribute_field_property_getters( body, class_name, attribute_fields );
					def_attribute_field_value_getters( body, attribute_fields );
					body.append( def_pragma(code( endregion Getters )));
					body.append( fmt_newline );

					body.append( def_pragma(code( region Setters )));
					def_attribute_field_value_setters( body, attribute_fields );
					def_attribute_field_initers( body, attribute_fields );
					body.append( def_pragma(code( endregion Setters )));
					body.append( fmt_newline );

					body.append( def_pragma( txt("region UObject")));
					body.append( parse_function( code(
						void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
					)));
					body.append( def_pragma( txt("endregion UObject")));
				}
				GasaAttributeSet = def_class( class_name, body
					, type_UAttributeSet, AccessSpec::Public
					, api_attribute
				);
			}

			CodeNS ns_gasa = parse_namespace( code(
				namespace Gasa
				{
					inline
					UGasaAttributeSet const* GetAttributeSet( UAbilitySystemComponent* ASC )
					{
						return Cast<UGasaAttributeSet>(ASC->GetAttributeSet( UGasaAttributeSet::StaticClass() ));
					}
				}
			));

			header.print( Include_AttributeSet);
			header.print( Include_AbilitySystemComponent);
			header.print( Include_GasaAttributeSet_Generated);
			header.print( fmt_newline);
			header.print(umeta_uclass);
			header.print(GasaAttributeSet);
			header.print(ns_gasa);
		}
		header.write();
	}

	Builder source = Builder::open( path_gasa_ability_system "GasaAttributeSet.cpp" );
	{
		source.print(generation_notice);
		header.print(fmt_newline);
		source.print( def_include( txt("GasaAttributeSet.h")));
		source.print(fmt_newline);
		source.print( def_include( txt("AbilitySystemComponent.h")));
		source.print( def_include( txt("Net/UnrealNetwork.h")));
		source.print( def_include( txt("Networking/GasaNetLibrary.h")));
		{
			CodeBody body = def_body( CodeT::Global_Body );
			body.append(fmt_newline);

			CodeConstructor constructor_for_UGasaAttributeSet = parse_constructor( code(
				UGasaAttributeSet::UGasaAttributeSet()
				{
					InitHealth( 100.f );
					InitMaxHealth( 100.f );
					InitMana( 50.f );
					InitMaxMana( 50.f );
				}
			));

			body.append(constructor_for_UGasaAttributeSet );
			body.append(fmt_newline);

			impl_attribute_fields( body, class_name, attribute_fields);

			CodeFn GetLifetimeOfReplicatedProps;
			{
				CodeBody field_lifetimes = def_body( CodeT::Function_Body);
				for (StringCached field : attribute_fields)
				{
					field_lifetimes.append( code_fmt( "field", (StrC)field, stringize(
						DOREPLIFETIME_DEFAULT_GAS(UGasaAttributeSet, <field>);
					)));
				}

				GetLifetimeOfReplicatedProps = parse_function( token_fmt( "body", (StrC)(field_lifetimes.to_string()), stringize(
					void UGasaAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
					{
						Super::GetLifetimeReplicatedProps(OutLifetimeProps);
						<body>
					}
				)));
			}
			body.append(GetLifetimeOfReplicatedProps);

			source.print(body);
		}
		source.write();
	}
}

void def_attribute_properties( CodeBody body, Array<StringCached> properties )
{
	for ( StringCached property : properties )
	{
		Code field_uproperty = code_fmt( "property", (StrC)property, stringize(
			UPROPERTY(ReplicatedUsing=Client_OnRep_<property>, EditAnywhere, BlueprintReadWrite, Category="Attributes")
		));

		CodeType type_FGameplayAttributeData = def_type( txt("FGameplayAttributeData"));

		body.append(fmt_newline);
		body.append( field_uproperty );
		body.append(fmt_newline);
		body.append( def_variable( type_FGameplayAttributeData, StrC(property)) );
	}
}

void def_attribute_field_on_reps( CodeBody body, Array<StringCached> properties )
{
	for ( StringCached property : properties )
	{
		Code umeta_UFUNCTION = code_str( UFUNCTION() );

		body.append(fmt_newline);
		body.append( umeta_UFUNCTION );
		body.append(fmt_newline);
		body.append( code_fmt( "property", (StrC)property, stringize(
			void Client_OnRep_<property>(FGameplayAttributeData& Prev<property>);
		)));
	}
}

void def_attribute_field_property_getters( CodeBody body, StrC class_name, Array<StringCached> properties )
{
	for ( String property : properties )
	{
		CodeFn generated_get_attribute = parse_function(
			token_fmt( "class_name", class_name, "property", (StrC)property,
			stringize(
				static FGameplayAttribute Get<property>Attribute()
				{
					static FProperty* Prop = FindFieldChecked<FProperty>(<class_name>::StaticClass(), GET_MEMBER_NAME_CHECKED(<class_name>, <property>));
					return Prop;
				}
			)));
		body.append( generated_get_attribute );
	}
}

void def_attribute_field_value_getters( CodeBody body, Array<StringCached> properties )
{
	for ( String property : properties )
	{
#pragma push_macro(FORCEINLINE)
#undef FORCEINLINE
		body.append( code_fmt( "property", (StrC)property,
		stringize(
			FORCEINLINE float Get<property>() const
			{
				return <property>.GetCurrentValue();
			}
		)));
#pragma pop_macro(FORCEINLINE)
	}
}

void def_attribute_field_value_setters( CodeBody body, Array<StringCached> properties )
{
	for ( String property : properties )
	{
		body.append( code_fmt( "property", (StrC)property,
		stringize(
			FORCEINLINE void Set<property>(float NewVal)
			{
				UAbilitySystemComponent* AbilityComp = GetOwningAbilitySystemComponent();
				if (ensure(AbilityComp))
				{
					AbilityComp->SetNumericAttributeBase(Get<property>Attribute(), NewVal);
				};
			}
		)));
	}
}

void def_attribute_field_initers ( CodeBody body, Array<StringCached> properties )
{
	for ( String property : properties )
	{
		body.append( code_fmt( "property", (StrC)property,
		stringize(
			FORCEINLINE void Init<property>(float NewVal)
			{
				<property>.SetBaseValue(NewVal);
				<property>.SetCurrentValue(NewVal);
			}
		)));
	}
}

void impl_attribute_fields( CodeBody body, StrC class_name, Array<StringCached> properties )
{
	for ( String property : properties )
	{
		body.append(fmt_newline);

		CodeFn field_impl = parse_function( token_fmt( "class_name", class_name, "property", (StrC)property,
		stringize(
			void <class_name>::Client_OnRep_<property>(FGameplayAttributeData& Prev<property>)
			{
				GAMEPLAYATTRIBUTE_REPNOTIFY(<class_name>, <property>, Prev<property>)
			}
		)));

		body.append( field_impl );
	}
}