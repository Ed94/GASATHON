#include "GasaAbilitySystemComponent.h"

#include "Engine/Engine.h"

void UGasaAbilitySystemComp::OnAbilityActorInfoSet()
{
}

void UGasaAbilitySystemComp::EffectApplied(UAbilitySystemComponent* AbilitySystem, FGameplayEffectSpec const& Spec,
	FActiveGameplayEffectHandle ActiveEffect)
{
	GEngine->AddOnScreenDebugMessage(1, 8.f, FColor::Yellow, FString("Effect applied"));
}

void UGasaAbilitySystemComp::InitAbilityActorInfo(AActor* InOwnerActor, AActor* InAvatarActor)
{
	Super::InitAbilityActorInfo(InOwnerActor, InAvatarActor);

	OnGameplayEffectAppliedDelegateToSelf.AddUObject(this, & ThisClass::EffectApplied);
}
