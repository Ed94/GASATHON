#pragma once

#include "GasaCharacter.h"

#include "EnemyCharacter.generated.h"

UCLASS(Blueprintable)
class GASA_API AEnemyCharacter : public AGasaCharacter
{
	GENERATED_BODY()
public:
	AEnemyCharacter();
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Gameplay")
	int32 PlayerLevel;

#pragma region ICombat
	int32 GetPlayerLevel() override;
#pragma endregion ICombat
};
