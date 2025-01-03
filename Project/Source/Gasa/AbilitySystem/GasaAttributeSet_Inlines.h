// Generated by GasaEditor/GasaGen/GasaGen_AttributeSets.cpp
#pragma once

#include "GasaAttributeSet.h"
#include "AbilitySystemComponent.h"

#pragma region Attribute Setters
FORCEINLINE
void UGasaAttributeSet::SetHealth( float NewVal )
{
	UAbilitySystemComponent* AbilityComp = GetOwningAbilitySystemComponent();
	if ( ensure( AbilityComp ) )
	{
		AbilityComp->SetNumericAttributeBase( GetHealthAttribute(), NewVal );
	};
}
FORCEINLINE
void UGasaAttributeSet::SetMana( float NewVal )
{
	UAbilitySystemComponent* AbilityComp = GetOwningAbilitySystemComponent();
	if ( ensure( AbilityComp ) )
	{
		AbilityComp->SetNumericAttributeBase( GetManaAttribute(), NewVal );
	};
}
FORCEINLINE
void UGasaAttributeSet::SetStrength( float NewVal )
{
	UAbilitySystemComponent* AbilityComp = GetOwningAbilitySystemComponent();
	if ( ensure( AbilityComp ) )
	{
		AbilityComp->SetNumericAttributeBase( GetStrengthAttribute(), NewVal );
	};
}
FORCEINLINE
void UGasaAttributeSet::SetIntelligence( float NewVal )
{
	UAbilitySystemComponent* AbilityComp = GetOwningAbilitySystemComponent();
	if ( ensure( AbilityComp ) )
	{
		AbilityComp->SetNumericAttributeBase( GetIntelligenceAttribute(), NewVal );
	};
}
FORCEINLINE
void UGasaAttributeSet::SetResilience( float NewVal )
{
	UAbilitySystemComponent* AbilityComp = GetOwningAbilitySystemComponent();
	if ( ensure( AbilityComp ) )
	{
		AbilityComp->SetNumericAttributeBase( GetResilienceAttribute(), NewVal );
	};
}
FORCEINLINE
void UGasaAttributeSet::SetVigor( float NewVal )
{
	UAbilitySystemComponent* AbilityComp = GetOwningAbilitySystemComponent();
	if ( ensure( AbilityComp ) )
	{
		AbilityComp->SetNumericAttributeBase( GetVigorAttribute(), NewVal );
	};
}
FORCEINLINE
void UGasaAttributeSet::SetMaxHealth( float NewVal )
{
	UAbilitySystemComponent* AbilityComp = GetOwningAbilitySystemComponent();
	if ( ensure( AbilityComp ) )
	{
		AbilityComp->SetNumericAttributeBase( GetMaxHealthAttribute(), NewVal );
	};
}
FORCEINLINE
void UGasaAttributeSet::SetMaxMana( float NewVal )
{
	UAbilitySystemComponent* AbilityComp = GetOwningAbilitySystemComponent();
	if ( ensure( AbilityComp ) )
	{
		AbilityComp->SetNumericAttributeBase( GetMaxManaAttribute(), NewVal );
	};
}
FORCEINLINE
void UGasaAttributeSet::SetArmor( float NewVal )
{
	UAbilitySystemComponent* AbilityComp = GetOwningAbilitySystemComponent();
	if ( ensure( AbilityComp ) )
	{
		AbilityComp->SetNumericAttributeBase( GetArmorAttribute(), NewVal );
	};
}
FORCEINLINE
void UGasaAttributeSet::SetArmorPenentration( float NewVal )
{
	UAbilitySystemComponent* AbilityComp = GetOwningAbilitySystemComponent();
	if ( ensure( AbilityComp ) )
	{
		AbilityComp->SetNumericAttributeBase( GetArmorPenentrationAttribute(), NewVal );
	};
}
FORCEINLINE
void UGasaAttributeSet::SetBlockChance( float NewVal )
{
	UAbilitySystemComponent* AbilityComp = GetOwningAbilitySystemComponent();
	if ( ensure( AbilityComp ) )
	{
		AbilityComp->SetNumericAttributeBase( GetBlockChanceAttribute(), NewVal );
	};
}
FORCEINLINE
void UGasaAttributeSet::SetCriticalHitChance( float NewVal )
{
	UAbilitySystemComponent* AbilityComp = GetOwningAbilitySystemComponent();
	if ( ensure( AbilityComp ) )
	{
		AbilityComp->SetNumericAttributeBase( GetCriticalHitChanceAttribute(), NewVal );
	};
}
FORCEINLINE
void UGasaAttributeSet::SetCriticalHitDamage( float NewVal )
{
	UAbilitySystemComponent* AbilityComp = GetOwningAbilitySystemComponent();
	if ( ensure( AbilityComp ) )
	{
		AbilityComp->SetNumericAttributeBase( GetCriticalHitDamageAttribute(), NewVal );
	};
}
FORCEINLINE
void UGasaAttributeSet::SetCriticalHitResistance( float NewVal )
{
	UAbilitySystemComponent* AbilityComp = GetOwningAbilitySystemComponent();
	if ( ensure( AbilityComp ) )
	{
		AbilityComp->SetNumericAttributeBase( GetCriticalHitResistanceAttribute(), NewVal );
	};
}
FORCEINLINE
void UGasaAttributeSet::SetHealthRegeneration( float NewVal )
{
	UAbilitySystemComponent* AbilityComp = GetOwningAbilitySystemComponent();
	if ( ensure( AbilityComp ) )
	{
		AbilityComp->SetNumericAttributeBase( GetHealthRegenerationAttribute(), NewVal );
	};
}
FORCEINLINE
void UGasaAttributeSet::SetManaRegeneration( float NewVal )
{
	UAbilitySystemComponent* AbilityComp = GetOwningAbilitySystemComponent();
	if ( ensure( AbilityComp ) )
	{
		AbilityComp->SetNumericAttributeBase( GetManaRegenerationAttribute(), NewVal );
	};
}
#pragma endregion Attribute Setters

namespace Gasa
{
	inline UGasaAttributeSet const* GetAttributeSet( UAbilitySystemComponent* ASC )
	{
		return Cast<UGasaAttributeSet>( ASC->GetAttributeSet( UGasaAttributeSet::StaticClass() ) );
	}

}
