#include "MMC_MaxMana.h"

#include "AbilitySystem/GasaAttributeSet.h"
#include "Interfaces/CombatInterface.h"

UMMC_MaxMana::UMMC_MaxMana()
{
	IntelligenceDef.AttributeToCapture = UGasaAttributeSet::GetVigorAttribute();
	IntelligenceDef.AttributeSource    = EGameplayEffectAttributeCaptureSource::Target;
	IntelligenceDef.bSnapshot          = false;
	
	RelevantAttributesToCapture.Add( IntelligenceDef);
}

float UMMC_MaxMana::CalculateBaseMagnitude_Implementation( FGameplayEffectSpec const& Spec ) const
{
	// Gather tags from source and target
	FGameplayTagContainer const* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	FGameplayTagContainer const* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();

	FAggregatorEvaluateParameters EvaluationParamters;
	EvaluationParamters.SourceTags = SourceTags;
	EvaluationParamters.TargetTags = TargetTags;

	float Intelligence = 0.f;
	GetCapturedAttributeMagnitude(IntelligenceDef, Spec, EvaluationParamters, Intelligence);
	Intelligence = FMath::Max(Intelligence, 0.f);

	ICombat* Combat      = Cast<ICombat>(Spec.GetContext().GetSourceObject()); check(Combat);
	int32    PlayerLevel = Combat->GetPlayerLevel();

	float  Calculation = 50.f + 2.5 * Intelligence + 15.f * PlayerLevel;
	return Calculation;
}
