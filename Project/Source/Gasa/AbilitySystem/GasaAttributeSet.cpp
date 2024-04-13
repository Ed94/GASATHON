// This was generated by GasaGen/GasaGen.cpp
#include "GasaAttributeSet.h"

#include "AbilitySystemComponent.h"
#include "Net/UnrealNetwork.h"
#include "Networking/GasaNetLibrary.h"

UGasaAttributeSet::UGasaAttributeSet()
{
	InitHealth( 100.f );
	InitMaxHealth( 100.f );
	InitMana( ( 50.f ) );
	InitMaxMana( 50.f );
}

void UGasaAttributeSet::Client_OnRep_Health( FGameplayAttributeData& PrevHealth )
{
	GAMEPLAYATTRIBUTE_REPNOTIFY( UGasaAttributeSet, Health, PrevHealth )
}

void UGasaAttributeSet::Client_OnRep_MaxHealth( FGameplayAttributeData& PrevMaxHealth )
{
	GAMEPLAYATTRIBUTE_REPNOTIFY( UGasaAttributeSet, MaxHealth, PrevMaxHealth )
}

void UGasaAttributeSet::Client_OnRep_Mana( FGameplayAttributeData& PrevMana )
{
	GAMEPLAYATTRIBUTE_REPNOTIFY( UGasaAttributeSet, Mana, PrevMana )
}

void UGasaAttributeSet::Client_OnRep_MaxMana( FGameplayAttributeData& PrevMaxMana )
{
	GAMEPLAYATTRIBUTE_REPNOTIFY( UGasaAttributeSet, MaxMana, PrevMaxMana )
}

void UGasaAttributeSet::GetLifetimeReplicatedProps( TArray< FLifetimeProperty >& OutLifetimeProps ) const
{
	Super::GetLifetimeReplicatedProps( OutLifetimeProps );
	DOREPLIFETIME_DEFAULT_GAS( UGasaAttributeSet, Health );
	DOREPLIFETIME_DEFAULT_GAS( UGasaAttributeSet, MaxHealth );
	DOREPLIFETIME_DEFAULT_GAS( UGasaAttributeSet, Mana );
	DOREPLIFETIME_DEFAULT_GAS( UGasaAttributeSet, MaxMana );
}
