#pragma once

#include "GameFramework/Character.h"

#include "GasaCharacter.generated.h"

UCLASS(BlueprintType, Blueprintable)
class GASA_API AGasaCharacter : public ACharacter
{
	GENERATED_BODY()
public:
	
	#pragma region Actor
		void BeginPlay() override;
	#pragma endregion Actor
};
