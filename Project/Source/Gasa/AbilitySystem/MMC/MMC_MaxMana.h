#pragma once

#include "GameplayModMagnitudeCalculation.h"

#include "MMC_MaxMana.generated.h"

UCLASS()
class GASA_API UMMC_MaxMana : public UGameplayModMagnitudeCalculation
{
	GENERATED_BODY()
	
public:

	UMMC_MaxMana();
	
	FGameplayEffectAttributeCaptureDefinition IntelligenceDef;
	
	float CalculateBaseMagnitude_Implementation( FGameplayEffectSpec const& Spec ) const override;
};