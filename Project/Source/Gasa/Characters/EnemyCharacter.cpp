#include "EnemyCharacter.h"
#include "Networking/GasaNetLibrary_Inlines.h"

AEnemyCharacter::AEnemyCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	bAutoAbilitySystem = true;
	
	PlayerLevel = 1;
}

#pragma region ICombat
int32 AEnemyCharacter::GetPlayerLevel()
{
	return PlayerLevel;
}
#pragma endregion ICombat
