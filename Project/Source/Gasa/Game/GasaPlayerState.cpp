#include "GasaPlayerState.h"

#include "AbilitySystem/GasaAbilitySystemComponent.h"

AGasaPlayerState::AGasaPlayerState()
{
	AbilitySystem = CreateDefaultSubobject<UGasaAbilitySystemComp>("Ability System");
	AbilitySystem->SetIsReplicated(true);
	
	Attributes = CreateDefaultSubobject<UAttributeSet>("Attributes");
	
	// Replication
	NetUpdateFrequency = 100.f;
}
