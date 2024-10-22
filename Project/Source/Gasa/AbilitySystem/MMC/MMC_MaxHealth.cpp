#include "MMC_MaxHealth.h"

#include "AbilitySystem/GasaAttributeSet.h"
#include "Interfaces/CombatInterface.h"

UMMC_MaxHealth::UMMC_MaxHealth()
{
	VigorDef.AttributeToCapture = UGasaAttributeSet::GetVigorAttribute();
	VigorDef.AttributeSource    = EGameplayEffectAttributeCaptureSource::Target;
	VigorDef.bSnapshot          = false;
	
	RelevantAttributesToCapture.Add( VigorDef);
}

float UMMC_MaxHealth::CalculateBaseMagnitude_Implementation( FGameplayEffectSpec const& Spec ) const
{
	// Gather tags from source and target
	FGameplayTagContainer const* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	FGameplayTagContainer const* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();

	FAggregatorEvaluateParameters EvaluationParamters;
	EvaluationParamters.SourceTags = SourceTags;
	EvaluationParamters.TargetTags = TargetTags;

	float Vigor = 0.f;
	GetCapturedAttributeMagnitude(VigorDef, Spec, EvaluationParamters, Vigor);
	Vigor = FMath::Max(Vigor, 0.f);

	ICombat* Combat      = Cast<ICombat>(Spec.GetContext().GetSourceObject());
	int32    PlayerLevel = Combat->GetPlayerLevel();

	float  Calculation = 80.f + 2.5 * Vigor + 10.f * PlayerLevel;
	return Calculation;
}

