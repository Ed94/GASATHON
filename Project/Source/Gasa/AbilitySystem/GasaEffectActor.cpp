#include "GasaEffectActor.h"

#include "GasaAbilitySystemComponent_Inlines.h"
using namespace Gasa;

AGasaEffectActor::AGasaEffectActor()
{
	PrimaryActorTick.bCanEverTick = false;

	RootComponent = CreateDefaultSubobject<USceneComponent>("Root");

	InstantEffectUsage  = DefaultEffectUsagePolicy;
	DurationEffectUsage = DefaultEffectUsagePolicy;
	InfiniteEffectUsage = DefaultEffectUsagePolicy;
}

void AGasaEffectActor::ApplyEffectToActor(AActor* Actor, TSubclassOf<UGameplayEffect> EffectClass)
{
	UGasaAbilitySystemComp* AS = GetAbilitySystem(Actor, true);

	FGameplayEffectContextHandle
	Context = AS->MakeEffectContext();
	Context.AddSourceObject(Actor);

	FGameplayEffectSpecHandle Spec = AS->MakeOutgoingSpec( EffectClass, 1.0f, Context );
	AS->ApplyGameplayEffectSpecToSelf( * Spec.Data );
}

void AGasaEffectActor::OnOverlap(AActor* Actor)
{
	UGasaAbilitySystemComp* AS = GetAbilitySystem(Actor, true);
	FGameplayEffectContextHandle
	Context = AS->MakeEffectContext();
	Context.AddSourceObject(Actor);
	
	if (InstantEffectClass.Get())
	{
		if (Bitfield_IsSet(InstantEffectUsage, (int32)EEffectUsagePolicy::ApplyOnOverlap))
		{
        	FGameplayEffectSpecHandle Spec = AS->MakeOutgoingSpec( InstantEffectClass, 1.0f, Context );
        	AS->ApplyGameplayEffectSpecToSelf( * Spec.Data );	
		}
		if (Bitfield_IsSet(InstantEffectUsage, (int32)EEffectUsagePolicy::RemoveOnOverlap))
		{
        	AS->RemoveActiveGameplayEffectBySourceEffect( InstantEffectClass, AS );
		}
	}
	if (DurationEffectClass.Get())
	{
		if (Bitfield_IsSet(DurationEffectUsage, (int32)EEffectUsagePolicy::ApplyOnOverlap))
		{
        	FGameplayEffectSpecHandle Spec = AS->MakeOutgoingSpec( InstantEffectClass, 1.0f, Context );
        	AS->ApplyGameplayEffectSpecToSelf( * Spec.Data );	
		}
		if (Bitfield_IsSet(InstantEffectUsage, (int32)EEffectUsagePolicy::RemoveOnOverlap))
		{
        	AS->RemoveActiveGameplayEffectBySourceEffect( DurationEffectClass, AS );
		}
	}
	if (InfiniteEffectClass.Get())
	{
		if (Bitfield_IsSet(InfiniteEffectUsage, (int32)EEffectUsagePolicy::ApplyOnOverlap))
		{
        	FGameplayEffectSpecHandle Spec = AS->MakeOutgoingSpec( InstantEffectClass, 1.0f, Context );
        	AS->ApplyGameplayEffectSpecToSelf( * Spec.Data );	
		}
		if (Bitfield_IsSet(InstantEffectUsage, (int32)EEffectUsagePolicy::RemoveOnOverlap))
		{
			AS->RemoveActiveGameplayEffectBySourceEffect( InfiniteEffectClass, AS );
		}
	}
}

void AGasaEffectActor::OnEndOverlap(AActor* Actor)
{
	UGasaAbilitySystemComp* AS = GetAbilitySystem(Actor, true);
	FGameplayEffectContextHandle
	Context = AS->MakeEffectContext();
	Context.AddSourceObject(Actor);
	
	if (InstantEffectClass.Get())
	{
		if (Bitfield_IsSet(InstantEffectUsage, (int32)EEffectUsagePolicy::ApplyOnEndOverlap))
		{
			FGameplayEffectSpecHandle Spec = AS->MakeOutgoingSpec( InstantEffectClass, 1.0f, Context );
			AS->ApplyGameplayEffectSpecToSelf( * Spec.Data );	
		}
		if (Bitfield_IsSet(InstantEffectUsage, (int32)EEffectUsagePolicy::RemoveOnEndOverlap))
		{
			AS->RemoveActiveGameplayEffectBySourceEffect( InstantEffectClass, AS );
		}
	}
	if (DurationEffectClass.Get())
	{
		if (Bitfield_IsSet(DurationEffectUsage, (int32)EEffectUsagePolicy::ApplyOnEndOverlap))
		{
			FGameplayEffectSpecHandle Spec = AS->MakeOutgoingSpec( InstantEffectClass, 1.0f, Context );
			AS->ApplyGameplayEffectSpecToSelf( * Spec.Data );	
		}
		if (Bitfield_IsSet(InstantEffectUsage, (int32)EEffectUsagePolicy::RemoveOnEndOverlap))
		{
			AS->RemoveActiveGameplayEffectBySourceEffect( DurationEffectClass, AS );
		}
	}
	if (InfiniteEffectClass.Get())
	{
		if (Bitfield_IsSet(InfiniteEffectUsage, (int32)EEffectUsagePolicy::ApplyOnEndOverlap))
		{
			FGameplayEffectSpecHandle Spec = AS->MakeOutgoingSpec( InstantEffectClass, 1.0f, Context );
			AS->ApplyGameplayEffectSpecToSelf( * Spec.Data );	
		}
		if (Bitfield_IsSet(InstantEffectUsage, (int32)EEffectUsagePolicy::RemoveOnEndOverlap))
		{
			AS->RemoveActiveGameplayEffectBySourceEffect( InfiniteEffectClass, AS );
		}
	}
}
