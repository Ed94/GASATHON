#pragma once

#include "AbilitySystemComponent.h"
#include "GasaCommon.h"

#include "GasaAbilitySystemComponent.generated.h"


DECLARE_MULTICAST_DELEGATE_OneParam(FEffectAssetTagsSig, FGameplayTagContainer const& /*Tags*/);


UCLASS(BlueprintType)
class GASA_API UGasaAbilitySystemComp : public UAbilitySystemComponent
{
	GENERATED_BODY()
public:

	FEffectAssetTagsSig Event_OnEffectAppliedAssetTags;
	
	void OnAbilityActorInfoSet();

	void EffectApplied(UAbilitySystemComponent* AbilitySystem, FGameplayEffectSpec const& Spec, FActiveGameplayEffectHandle ActiveEffect);

#pragma region AbilitySystemComponent
	void InitAbilityActorInfo(AActor* InOwnerActor, AActor* InAvatarActor) override;
#pragma endregion AbilitySystemComponent
};