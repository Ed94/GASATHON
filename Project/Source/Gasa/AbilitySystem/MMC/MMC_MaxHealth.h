#pragma once

#include "GameplayModMagnitudeCalculation.h"

#include "MMC_MaxHealth.generated.h"

UCLASS()
class GASA_API UMMC_MaxHealth : public UGameplayModMagnitudeCalculation
{
	GENERATED_BODY()
	
public:

	UMMC_MaxHealth();
	
	FGameplayEffectAttributeCaptureDefinition VigorDef;
	
	float CalculateBaseMagnitude_Implementation( FGameplayEffectSpec const& Spec ) const override;
};
