#pragma once

#include "GasaCommon.h"
#include "Actors/GasaActor.h"
#include "GameFramework/Actor.h"

#include "GasaEffectActor.generated.h"

UCLASS()
class GASA_API AGasaEffectActor : public AGasaActor
{
	GENERATED_BODY()
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay Effects")
	TSoftClassPtr<UGameplayEffect> InstantEffectClass;
	
	AGasaEffectActor();

	UFUNCTION(BlueprintCallable, Category = "Gameplay Effects")
	void ApplyEffectToActor(AActor* Actor, TSubclassOf<UGameplayEffect> EffectClass );
};

