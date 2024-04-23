#include "PlayerCharacter.h"

#include "Networking/GasaNetLibrary_Inlines.h"
#include "AbilitySystemComponent.h"
#include "Game/GasaPlayerController.h"
#include "UI/GasaHUD.h"
#include "UI/WidgetController.h"

APlayerCharacter::APlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	bAutoAbilitySystem = false;
}

void APlayerCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
}

void APlayerCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();
}
