#include "PlayerCharacter.h"

#include "AbilitySystemComponent.h"

APlayerCharacter::APlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	bAutoAbilitySystem = false;
}

void APlayerCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	AGasaPlayerState* PS = GetGasaPlayerState();
	// Server setup ability system (character side)
	{
		AbilitySystem = PS->AbilitySystem;
		Attributes    = PS->Attributes;
		AbilitySystem->InitAbilityActorInfo(PS, this);
	}
}

void APlayerCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();
	
	AGasaPlayerState* PS = GetGasaPlayerState();
	// Client setup ability system
	{
		AbilitySystem = PS->AbilitySystem;
		Attributes    = PS->Attributes;
		AbilitySystem->InitAbilityActorInfo(PS, this);
	}
}
