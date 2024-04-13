#pragma once

#include "GameFramework/GameState.h"
#include "GasaCommon.h"

#include "GasaGameState.generated.h"

UCLASS(Blueprintable)
class GASA_API AGasaGameState : public AGameState
{
	GENERATED_BODY()
public:
#pragma region Cog
    // To make sure it doesn't get garbage collected.
    UPROPERTY()
    TObjectPtr<UObject> CogWindowManagerRef;
	
#if ENABLE_COG
	TObjectPtr<UCogWindowManager> CogWindowManager;
#endif // ENABLE_COG
#pragma endregion Cog

	AGasaGameState();
	
#pragma region GameState
	void BeginPlay() override;

	void Tick(float DeltaSeconds) override;
#pragma endregion GameState	
};