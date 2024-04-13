#pragma once

#include "Engine/LevelScriptActor.h"

#include "GasaCommon.h"

#include "GasaLevelScriptActor.generated.h"

UCLASS(Blueprintable)
class GASA_API AGasaLevelScriptActor : public ALevelScriptActor
{
    GENERATED_BODY()
public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Post Process")
    TObjectPtr<APostProcessVolume> GlobalPPV;

#pragma region Actor
    void BeginPlay() override;
#pragma region endActor
};

namespace Gasa
{
	inline
    AGasaLevelScriptActor* GetLevelActor(UObject* Context, ULevel* OwnerLevel = nullptr) {
		UWorld* World = GEngine->GetWorldFromContextObject(Context, EGetWorldErrorMode::LogAndReturnNull);
		if (World == nullptr)
		{
			Log("World is null... are you running in a proper context?", ELogV::Error);
			return nullptr;
		}
		return Cast<AGasaLevelScriptActor>(World->GetLevelScriptActor(OwnerLevel));
	}
}
