#pragma once

#include "GasaCharacter.h"

#include "PlayerCharacter.generated.h"

UCLASS(Blueprintable)
class GASA_API APlayerCharacter : public AGasaCharacter
{
	GENERATED_BODY()
public:

	APlayerCharacter();

#pragma region Pawn
	void OnRep_PlayerState() override;
#pragma endregion Pawn
};
