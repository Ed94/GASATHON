#pragma once

#include "GasaCommon.h"
#include "GasaEffectActor.generated.h"


UCLASS()
class GASA_API AGasaEffectActor : public AActor
{
	GENERATED_BODY()
public:

	UPROPERTY(EditAnywhere, Category = "Applied Effects")
	TSoftClassPtr<UGameplayEffect> InstantEffectClass;
	
	AGasaEffectActor();

	void ApplyEffectToTarget(AActor* Target, TSubclassOf<UGameplayEffect> EffectClass );
};
