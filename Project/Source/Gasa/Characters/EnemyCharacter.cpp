#include "EnemyCharacter.h"
#include "Networking/GasaNetLibrary_Inlines.h"

AEnemyCharacter::AEnemyCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	bAutoAbilitySystem = true;
}
