#pragma once

#include "GameplayEffectTypes.h"
#include "GasaCommon.h"

#include "EffectProperties.generated.h"

USTRUCT()
struct GASA_API FEffectProperties
{
	GENERATED_BODY()

	FGameplayEffectContextHandle Context;

	UPROPERTY(VisibleAnywhere)
	UAbilitySystemComponent* SourceAbilitySystem;
	
	UPROPERTY(VisibleAnywhere)
	AActor* SourceAvatar;

	UPROPERTY(VisibleAnywhere)
	AController* SourceController;
	
	UPROPERTY(VisibleAnywhere)
	UAbilitySystemComponent* TargetAbilitySystem;
	
	UPROPERTY(VisibleAnywhere)
	AActor* TargetAvatar;

	UPROPERTY(VisibleAnywhere)
	APlayerController* TargetController;

	void Populate(FGameplayEffectModCallbackData const& Data);
};
