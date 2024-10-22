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

#pragma region ICombat
int32 APlayerCharacter::GetLevel()
{
	return GetPlayerState<AGasaPlayerState>()->Level;
}
#pragma endregion ICombat

#pragma region Pawn
void APlayerCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
}

void APlayerCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();
}
#pragma endregion Pawn
