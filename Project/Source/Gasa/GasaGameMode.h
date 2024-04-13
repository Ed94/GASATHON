#pragma once
#include "GameFramework/GameMode.h"

#include "GasaGameMode.generated.h"

UCLASS(Blueprintable)
class GASA_API AGasaGameMode : public AGameMode
{
	GENERATED_BODY()
public:
};

namespace Gasa
{
	FORCEINLINE
	AGasaGameMode* GetGameMode(UObject* Context) {
		return Context->GetWorld()->GetAuthGameMode<AGasaGameMode>();
	}
}