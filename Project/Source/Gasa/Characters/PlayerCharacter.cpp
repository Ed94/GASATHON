#include "PlayerCharacter.h"

#include "AbilitySystemComponent.h"
#include "Game/GasaPlayerController.h"
#include "UI/GasaHUD.h"
#include "UI/WidgetController.h"

APlayerCharacter::APlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	bAutoAbilitySystem = false;
}

// TODO(Ed): We need to setup Net Slime...
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

	if (IsLocallyControlled())
	{
		AGasaPlayerController* PC   = GetController<AGasaPlayerController>();
		AGasaHUD*              HUD  = PC->GetHUD<AGasaHUD>();
		FWidgetControllerData  Data = { PC, PS, AbilitySystem, Attributes };
		HUD->InitHostWidget(& Data);
	}
}

// TODO(Ed): We need to setup Net Slime...
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

	if (IsLocallyControlled())
	{
		AGasaPlayerController* PC   = GetController<AGasaPlayerController>();
		AGasaHUD*              HUD  = PC->GetHUD<AGasaHUD>();
		FWidgetControllerData  Data = { PC, PS, AbilitySystem, Attributes };
		HUD->InitHostWidget(& Data);
	}
}
