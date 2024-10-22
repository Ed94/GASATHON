#pragma once

#include "GasaCharacter.h"

#include "PlayerCharacter.generated.h"

UCLASS(Blueprintable)
class GASA_API APlayerCharacter : public AGasaCharacter
{
	GENERATED_BODY()
public:

	APlayerCharacter();

#pragma region ICombat
	int32 GetPlayerLevel() override;
#pragma endregion ICombat

#pragma region Pawn
	void PossessedBy(AController* NewController) override;
	
	void OnRep_PlayerState() override;
#pragma endregion Pawn
};
