// Generated by GasaGen/GasaGen_UGasaAttributeSet.cpp
#include "GasaAttributeSet.h"
#include "GasaAttributeSet_Inlines.h"
#include "EffectProperties.h"

#include "AbilitySystemComponent.h"
#include "Net/UnrealNetwork.h"
#include "Networking/GasaNetLibrary.h"

UGasaAttributeSet::UGasaAttributeSet()
{
	InitHealth( 100.f );
	InitMaxHealth( 100.f );
	InitMana( 50.f );
	InitMaxMana( 50.f );
}

#pragma region Rep Notifies
void UGasaAttributeSet::Client_OnRep_Health( FGameplayAttributeData& PrevHealth )
{
	// From GAMEPLAYATTRIBUTE_REPNOTIFY
	static FProperty* UGasaAttributeSetProperty = FindFieldChecked<FProperty>( StaticClass(), GET_MEMBER_NAME_CHECKED( UGasaAttributeSet, Health ) );
	GetOwningAbilitySystemComponentChecked()->SetBaseAttributeValueFromReplication( FGameplayAttribute( UGasaAttributeSetProperty ), Health, PrevHealth );
}
void UGasaAttributeSet::Client_OnRep_MaxHealth( FGameplayAttributeData& PrevMaxHealth )
{
	// From GAMEPLAYATTRIBUTE_REPNOTIFY
	static FProperty* UGasaAttributeSetProperty = FindFieldChecked<FProperty>( StaticClass(), GET_MEMBER_NAME_CHECKED( UGasaAttributeSet, MaxHealth ) );
	GetOwningAbilitySystemComponentChecked()->SetBaseAttributeValueFromReplication( FGameplayAttribute( UGasaAttributeSetProperty ), MaxHealth, PrevMaxHealth );
}
void UGasaAttributeSet::Client_OnRep_Mana( FGameplayAttributeData& PrevMana )
{
	// From GAMEPLAYATTRIBUTE_REPNOTIFY
	static FProperty* UGasaAttributeSetProperty = FindFieldChecked<FProperty>( StaticClass(), GET_MEMBER_NAME_CHECKED( UGasaAttributeSet, Mana ) );
	GetOwningAbilitySystemComponentChecked()->SetBaseAttributeValueFromReplication( FGameplayAttribute( UGasaAttributeSetProperty ), Mana, PrevMana );
}
void UGasaAttributeSet::Client_OnRep_MaxMana( FGameplayAttributeData& PrevMaxMana )
{
	// From GAMEPLAYATTRIBUTE_REPNOTIFY
	static FProperty* UGasaAttributeSetProperty = FindFieldChecked<FProperty>( StaticClass(), GET_MEMBER_NAME_CHECKED( UGasaAttributeSet, MaxMana ) );
	GetOwningAbilitySystemComponentChecked()->SetBaseAttributeValueFromReplication( FGameplayAttribute( UGasaAttributeSetProperty ), MaxMana, PrevMaxMana );
}
#pragma endregion Rep Notifies

void UGasaAttributeSet::PostGameplayEffectExecute( FGameplayEffectModCallbackData const& Data )
{
	Super::PostGameplayEffectExecute( Data );
	FEffectProperties Props;
	Props.Populate( Data );
}

void UGasaAttributeSet::PreAttributeChange( FGameplayAttribute const& Attribute, float& NewValue )
{
	Super::PreAttributeChange( Attribute, NewValue );

	if ( Attribute == GetHealthAttribute() )
	{
		NewValue = FMath::Clamp( NewValue, 0, GetMaxHealth() );
	}
	if ( Attribute == GetMaxHealthAttribute() )
	{
		NewValue = FMath::Clamp( NewValue, 0, 99999.000000 );
	}
	if ( Attribute == GetManaAttribute() )
	{
		NewValue = FMath::Clamp( NewValue, 0, GetMaxMana() );
	}
	if ( Attribute == GetMaxManaAttribute() )
	{
		NewValue = FMath::Clamp( NewValue, 0, 99999.000000 );
	}
}

void UGasaAttributeSet::GetLifetimeReplicatedProps( TArray<FLifetimeProperty>& OutLifetimeProps ) const
{
	Super::GetLifetimeReplicatedProps( OutLifetimeProps );

	DOREPLIFETIME_DEFAULT_GAS( UGasaAttributeSet, Health );
	DOREPLIFETIME_DEFAULT_GAS( UGasaAttributeSet, MaxHealth );
	DOREPLIFETIME_DEFAULT_GAS( UGasaAttributeSet, Mana );
	DOREPLIFETIME_DEFAULT_GAS( UGasaAttributeSet, MaxMana );
}
