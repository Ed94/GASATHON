#include "GasaEffectActor.h"

#include "GasaAbilitySystemComponent_Inlines.h"
using namespace Gasa;

AGasaEffectActor::AGasaEffectActor()
{
	PrimaryActorTick.bCanEverTick = false;

	RootComponent = CreateDefaultSubobject<USceneComponent>("Root");
}

void AGasaEffectActor::ApplyEffectToActor(AActor* Actor, TSubclassOf<UGameplayEffect> EffectClass)
{
	UGasaAbilitySystemComp* AS = GetAbilitySystem(Actor, true);

	FGameplayEffectContextHandle
	Context = AS->MakeEffectContext();
	Context.AddSourceObject(Actor);
	
	FGameplayEffectSpecHandle Spec = AS->MakeOutgoingSpec( EffectClass, 1.0f, Context );
	if (Spec.IsValid())
		AS->ApplyGameplayEffectSpecToSelf( * Spec.Data );
}
