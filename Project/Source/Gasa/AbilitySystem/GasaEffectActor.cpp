#include "GasaEffectActor.h"

#include "GasaAbilitySystemComponent_Inlines.h"
using namespace Gasa;

AGasaEffectActor::AGasaEffectActor()
{
	PrimaryActorTick.bCanEverTick = false;

	RootComponent = CreateDefaultSubobject<USceneComponent>("Root");
}

void AGasaEffectActor::ApplyEffectToTarget(AActor* Target, TSubclassOf<UGameplayEffect> EffectClass)
{
	UGasaAbilitySystemComp* AS = GetAbilitySystem(Target, true);

	FGameplayEffectContextHandle
	Context = AS->MakeEffectContext();
	Context.AddSourceObject(Target);
	
	FGameplayEffectSpecHandle Spec = AS->MakeOutgoingSpec( EffectClass, 1.0f, Context );
	AS->ApplyGameplayEffectSpecToSelf( * Spec.Data );
}
