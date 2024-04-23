#include "GasaPlayerState.h"

#include "AbilitySystem/GasaAbilitySystemComponent.h"
#include "AbilitySystem/GasaAttributeSet.h"

AGasaPlayerState::AGasaPlayerState()
{
	bAutoAbilitySystem = true;
	
	AbilitySystem = CreateDefaultSubobject<UGasaAbilitySystemComp>("Ability System");
	AbilitySystem->SetIsReplicated(true);
	AbilitySystem->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);
	
	Attributes = CreateDefaultSubobject<UGasaAttributeSet>("Attributes");
	
	// Replication
	NetUpdateFrequency = 100.f;
}
