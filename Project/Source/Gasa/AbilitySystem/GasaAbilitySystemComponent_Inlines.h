#pragma once
#include "GasaAbilitySystemComponent.h"
#include "AbilitySystemInterface.h"
#include "AbilitySystemGlobals.h"


namespace Gasa
{
	inline
	UGasaAbilitySystemComp* GetAbilitySystem(UObject* Object)
	{
		if (Object->Implements<UAbilitySystemInterface>())
		{
			return Cast<UGasaAbilitySystemComp>( Cast<IAbilitySystemInterface>(Object)->GetAbilitySystemComponent() );
		}
		return nullptr;
	}

	// From: UAbilitySystemGlobals::GetAbilitySystemComponentFromActor
	inline
	UGasaAbilitySystemComp* GetAbilitySystem(AActor* Actor, bool LookForComponent = true)
	{
		if (Actor == nullptr)
			return nullptr;

		const IAbilitySystemInterface* ASI = Cast<IAbilitySystemInterface>(Actor);
		if (ASI)
			return Cast<UGasaAbilitySystemComp>(ASI->GetAbilitySystemComponent());

		if (LookForComponent)
		{
			// Fall back to a component search to better support BP-only actors
			return Cast<UGasaAbilitySystemComp>(Actor->FindComponentByClass<UAbilitySystemComponent>());
		}

		return nullptr;
	}
}
