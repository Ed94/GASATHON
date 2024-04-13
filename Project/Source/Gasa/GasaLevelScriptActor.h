#pragma once

#include "Engine/LevelScriptActor.h"

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
	    UWorld* World = GEngine->GetWorldFromContextObjectChecked(Context);
		return Cast<AGasaLevelScriptActor>(World->GetLevelScriptActor(OwnerLevel));
	}
}
