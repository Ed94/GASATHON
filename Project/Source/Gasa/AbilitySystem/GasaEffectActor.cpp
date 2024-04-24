#include "GasaEffectActor.h"

#include "GasaAbilitySystemComponent_Inlines.h"
#include "GasaContainers.h"
using namespace Gasa;

AGasaEffectActor::AGasaEffectActor()
{
	PrimaryActorTick.bCanEverTick = false;

	RootComponent = CreateDefaultSubobject<USceneComponent>("Root");

	InstantEffectUsage  = EInstantEffectUsagePolicy::DoNotApply;
	DurationEffectUsage = DefaultEffectUsagePolicy;
	InfiniteEffectUsage = DefaultEffectUsagePolicy;

	bDestroyOnEffectRemoval = false;
}

void AGasaEffectActor::ApplyEffectToActor(AActor* Actor, TSubclassOf<UGameplayEffect> EffectClass, bool bRemoveOnEndOverlap)
{
	UGasaAbilitySystemComp* AS = GetAbilitySystem(Actor, true);
	FGameplayEffectContextHandle
	Context = AS->MakeEffectContext();
	Context.AddSourceObject(Actor);

	FGameplayEffectSpecHandle   Spec         = AS->MakeOutgoingSpec( EffectClass, 1.0f, Context );
	FActiveGameplayEffectHandle ActiveEffect = AS->ApplyGameplayEffectSpecToSelf( * Spec.Data );
	if (bRemoveOnEndOverlap)
		ActiveEffectsToRemove.Add(ActiveEffect, AS);
}

void AGasaEffectActor::OnOverlap(AActor* Actor)
{
	UGasaAbilitySystemComp* AS = GetAbilitySystem(Actor, true);
	FGameplayEffectContextHandle
	Context = AS->MakeEffectContext();
	Context.AddSourceObject(Actor);
	
	if (InstantEffectClass && InstantEffectUsage == EInstantEffectUsagePolicy::ApplyOnOverlap)
	{
		FGameplayEffectSpecHandle Spec= AS->MakeOutgoingSpec( InstantEffectClass, 1.0f, Context );
		AS->ApplyGameplayEffectSpecToSelf( * Spec.Data );
	}
	if (DurationEffectClass)
	{
		if (Bitfield_IsSet(DurationEffectUsage, EEffectUsagePolicy::ApplyOnOverlap))
		{
        	FGameplayEffectSpecHandle   Spec         = AS->MakeOutgoingSpec( DurationEffectClass, 1.0f, Context );
			FActiveGameplayEffectHandle ActiveEffect = AS->ApplyGameplayEffectSpecToSelf( * Spec.Data );
			if (Bitfield_IsSet(DurationEffectUsage, (int32)EEffectUsagePolicy::RemoveOnEndOverlap))
				ActiveDuration = ActiveEffect;
		}
		if (ActiveDuration.IsValid() && Bitfield_IsSet(DurationEffectUsage, EEffectUsagePolicy::RemoveOnOverlap))
			AS->RemoveActiveGameplayEffect(ActiveDuration);
	}
	if (InfiniteEffectClass)
	{
		bool bApplyOnOverlap = Bitfield_IsSet(InfiniteEffectUsage, EEffectUsagePolicy::ApplyOnOverlap);
		if (bApplyOnOverlap)
		{
			FGameplayEffectSpecHandle   Spec         = AS->MakeOutgoingSpec( InfiniteEffectClass, 1.0f, Context );
			FActiveGameplayEffectHandle ActiveEffect = AS->ApplyGameplayEffectSpecToSelf( * Spec.Data );
			if (Bitfield_IsSet(InfiniteEffectUsage, (int32)EEffectUsagePolicy::RemoveOnEndOverlap))
				ActiveInfinite = ActiveEffect;
		}
		if (ActiveInfinite.IsValid() && Bitfield_IsSet(InfiniteEffectUsage, EEffectUsagePolicy::RemoveOnOverlap))
		{
			if (ActiveInfinite.IsValid())
				AS->RemoveActiveGameplayEffect(ActiveInfinite);
		}
	}
}

void AGasaEffectActor::OnEndOverlap(AActor* Actor)
{
	UGasaAbilitySystemComp* AS = GetAbilitySystem(Actor, true);
	FGameplayEffectContextHandle
	Context = AS->MakeEffectContext();
	Context.AddSourceObject(Actor);
	
	if (InstantEffectClass && InstantEffectUsage == EInstantEffectUsagePolicy::ApplyOnEndOverlap)
	{
		FGameplayEffectSpecHandle Spec= AS->MakeOutgoingSpec( InstantEffectClass, 1.0f, Context );
		AS->ApplyGameplayEffectSpecToSelf( * Spec.Data );
	}
	if (DurationEffectClass)
	{
		if (Bitfield_IsSet(DurationEffectUsage, EEffectUsagePolicy::ApplyOnEndOverlap))
		{
			FGameplayEffectSpecHandle   Spec         = AS->MakeOutgoingSpec( DurationEffectClass, 1.0f, Context );
			FActiveGameplayEffectHandle ActiveEffect = AS->ApplyGameplayEffectSpecToSelf( * Spec.Data );
			if (Bitfield_IsSet(DurationEffectUsage, (int32)EEffectUsagePolicy::RemoveOnOverlap))
				ActiveDuration = ActiveEffect;
		}
		if (ActiveDuration.IsValid() && Bitfield_IsSet(DurationEffectUsage, (int32)EEffectUsagePolicy::RemoveOnEndOverlap))
			AS->RemoveActiveGameplayEffect(ActiveDuration);
	}
	if (InfiniteEffectClass)
	{
		if (Bitfield_IsSet(InfiniteEffectUsage, EEffectUsagePolicy::ApplyOnEndOverlap))
		{
			FGameplayEffectSpecHandle   Spec         = AS->MakeOutgoingSpec( InfiniteEffectClass, 1.0f, Context );
			FActiveGameplayEffectHandle ActiveEffect = AS->ApplyGameplayEffectSpecToSelf( * Spec.Data );
			if (Bitfield_IsSet(InfiniteEffectUsage, (int32)EEffectUsagePolicy::RemoveOnOverlap))
				ActiveInfinite = ActiveEffect;
		}
		if (ActiveInfinite.IsValid() && Bitfield_IsSet(InfiniteEffectUsage, EEffectUsagePolicy::RemoveOnEndOverlap))
		{
			if (ActiveInfinite.IsValid())
				AS->RemoveActiveGameplayEffect(ActiveInfinite);
		}
	}

	TArray<FActiveGameplayEffectHandle> EffectsRemoved;
	for (ActiveEffectEntry ActiveEffect : ActiveEffectsToRemove)
	{
		if (ActiveEffect.Value != AS)
			continue;
		AS->RemoveActiveGameplayEffect(ActiveEffect.Key, 1);
		EffectsRemoved.Add(ActiveEffect.Key);
	}
	RemoveKeys(ActiveEffectsToRemove, EffectsRemoved);
}
