#pragma once
#include "GameFramework/GameMode.h"

#include "GasaCommon.h"

#include "GasaGameMode.generated.h"

UCLASS(Blueprintable)
class GASA_API AGasaGameMode : public AGameMode
{
	GENERATED_BODY()
public:
};

namespace Gasa
{
	inline
	AGasaGameMode* GetGameMode(UObject* Context)
	{
		UWorld* World = GEngine->GetWorldFromContextObject(Context, EGetWorldErrorMode::LogAndReturnNull);
		if (World == nullptr)
		{
			Log("World is null... are you running in a proper context?", ELogV::Error);
			return nullptr;
		}
		return Cast<AGasaGameMode>(World->GetAuthGameMode());
	}
}
