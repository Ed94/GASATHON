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
	
	// TODO(Ed): If hes only using this to bind the EffectApplied to a delegate, then just use the init override instead.
	void OnAbilityActorInfoSet();

	void EffectApplied(UAbilitySystemComponent* AbilitySystem, FGameplayEffectSpec const& Spec, FActiveGameplayEffectHandle ActiveEffect);

#pragma region AbilitySystemComponent
	void InitAbilityActorInfo(AActor* InOwnerActor, AActor* InAvatarActor) override;
#pragma endregion AbilitySystemComponent
};
